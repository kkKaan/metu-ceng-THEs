#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <poll.h>
#include <math.h>

#include "logging.h"
#include "message.h"

// bidirectional pipe
#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

typedef struct
{
    int x;
    int y;
    int durability;
} Obstacle;

typedef struct
{
    pid_t pid;             
    int x;
    int y;
    int totalArgCount;
    char **argv;
    int pipe_fd;
    int is_alive;
    int is_informed;

} Bomber;

typedef struct
{
    int x;
    int y;
    int time_left;
    int range;
    int bomber_id;
    pid_t pid;             // Process ID of the bomb
    int pipe_fd;           // Pipe file descriptor for communication with the bomb
} Bomb;

typedef struct
{
    int width;
    int height;
    int num_obstacles;
    int num_bombs;
    int num_bombers;
    int num_alive_bombers;

    Obstacle **obstacles;
    Bomber **bombers;
    Bomb **bombs;
    int **maze;

    pid_t winnerPid;
} Maze;

// initialize maze
Maze* MazeInit(int w, int h, int num_obstacles, int num_bombs, int num_bombers)
{
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    maze->width = w;
    maze->height = h;
    maze->num_obstacles = num_obstacles;
    maze->num_bombs = num_bombs;
    maze->num_bombers = num_bombers;
    maze->num_alive_bombers = num_bombers;

    maze->maze = (int**)malloc(sizeof(int*) * h);
    for (int i = 0; i < h; ++i)
    {
        maze->maze[i] = (int*)malloc(sizeof(int) * w);
        for (int j = 0; j < w; ++j)
        {
            maze->maze[i][j] = 0;
        }
    }

    maze->obstacles = (Obstacle**)malloc(sizeof(Obstacle*) * num_obstacles);
    maze->bombs = (Bomb**)malloc(sizeof(Bomb*) * h * w); 
    maze->bombers = (Bomber**)malloc(sizeof(Bomber*) * num_bombers);

    for(int i = 0; i < num_obstacles; ++i)
    {
        maze->obstacles[i] = NULL;
    }

    for(int i = 0; i < h * w; ++i)
    {
        maze->bombs[i] = NULL;
    }

    for(int i = 0; i < num_bombers; ++i)
    {
        maze->bombers[i] = NULL;
    }

    maze->winnerPid = 0;

    return maze;
}

// destructor for maze
void MazeFree(Maze* maze)
{
    if (maze == NULL) return;

    // Free maze grid
    for (int i = 0; i < maze->height; ++i)
    {
        free(maze->maze[i]);
    }
    free(maze->maze);

    // Free obstacles
    for (int i = 0; i < maze->num_obstacles; ++i)
    {
        if(maze->obstacles[i])
        {
            free(maze->obstacles[i]);
        }
    }
    free(maze->obstacles);

    // Free bombs
    for (int i = 0; i < maze->num_bombs; ++i)
    {
        if(maze->bombs[i])
        {
            free(maze->bombs[i]);
        }
    }
    free(maze->bombs);

    // Free bombers
    for (int i = 0; i < maze->num_bombers; ++i)
    {
        if(maze->bombers[i])
        {
            free(maze->bombers[i]);
        }
    }
    free(maze->bombers);
    
    free(maze);
}

// check if the given position is valid, 0 -> empty, 1 -> obstacle, 2 -> bomber, 3 -> bomb, 5 -> a bomb and a bomber
int MazeIsValidPosition(Maze* maze, int x, int y)
{
    if (x < 0 || x >= maze->width || y < 0 || y >= maze->height || maze->maze[y][x] == 1 || maze->maze[y][x] == 2 || maze->maze[y][x] == 5)
    {
        return 0;
    }
    return 1;
}

// damage an obstacle, if durability is 0, remove it from the maze
void ObstacleDamage(Maze* maze, Obstacle* obstacle)
{
    if (obstacle->durability > 0)
    {
        obstacle->durability--;
        if (obstacle->durability == 0)
        {
            maze->maze[obstacle->y][obstacle->x] = 0;
            maze->num_obstacles--;
            free(obstacle);

            // remove obstacle from the maze's obstacle list
            for (int i = 0; i < maze->num_obstacles; ++i)
            {
                if (maze->obstacles[i] == obstacle)
                {
                    maze->obstacles[i] = maze->obstacles[maze->num_obstacles - 1];
                    maze->obstacles[maze->num_obstacles - 1] = NULL;
                    break;
                }
            }
        }
    }
}

Bomber *find_bomber_at_position(Maze *maze, int xx, int yy)
{
    for (int i = 0; i < maze->num_bombers; ++i)
    {
        if (maze->bombers[i] && maze->bombers[i]->x == xx && maze->bombers[i]->y == yy && maze->bombers[i]->is_alive)
        {
            return maze->bombers[i];
        }
    }
    return NULL;
}

Obstacle *find_obstacle_at_position(Maze *maze, int xx, int yy)
{
    for (int i = 0; i < maze->num_obstacles; ++i)
    {
        if (maze->obstacles[i] && maze->obstacles[i]->x == xx && maze->obstacles[i]->y == yy)
        {
            return maze->obstacles[i];
        }
    }
    return NULL;
}

void takeInputs(Maze** maze_ptr, Bomber*** bomber_data_ptr, int* num_bombers_ptr)
{
    int width, height, num_obstacles, num_bombers;
    scanf(" %d %d %d %d \n", &width, &height, &num_obstacles, &num_bombers);

    Maze *maze = MazeInit(width, height, num_obstacles, 0, num_bombers);

    // read obstacles
    for (int i = 0; i < num_obstacles; ++i)
    {
        int x, y, durability;
        scanf(" %d %d %d \n", &x, &y, &durability);

        Obstacle *obstacle = (Obstacle *)malloc(sizeof(Obstacle));
        obstacle->x = x;
        obstacle->y = y;
        obstacle->durability = durability;

        maze->obstacles[i] = obstacle;
        maze->maze[y][x] = 1;
    }

    *bomber_data_ptr = (Bomber **)malloc(num_bombers * sizeof(Bomber *));

    // read bombers
    for (int i = 0; i < num_bombers; ++i)
    {
        int x, y, totalArgCount;
        scanf(" %d %d %d \n", &x, &y, &totalArgCount);

        Bomber *bomber = (Bomber *)malloc(sizeof(Bomber));
        bomber->x = x;
        bomber->y = y;
        bomber->totalArgCount = totalArgCount;
        bomber->argv = (char **)malloc(sizeof(char *) * (totalArgCount + 1));
        bomber->is_alive = 1;
        bomber->is_informed = 0;

        for (int j = 0; j < totalArgCount; ++j)
        {
            bomber->argv[j] = (char *)malloc(1024);
            scanf(" %s", bomber->argv[j]);
        }
        bomber->argv[totalArgCount] = NULL;

        maze->bombers[i] = bomber;
        maze->maze[y][x] = 2;
        (*bomber_data_ptr)[i] = bomber;

        // set the pipe_fd field for the bomber to -1 initially
        // this will be updated later in the spawnBomberProcesses function
        bomber->pipe_fd = -1;
    }

    *num_bombers_ptr = num_bombers;
    *maze_ptr = maze;
}

void spawnBomberProcesses(Bomber **bombers, int num_bombers)
{
    for (int i = 0; i < num_bombers; ++i)
    {
        int pipe_fds[2];
        PIPE(pipe_fds);
        pid_t pid = fork();

        if (pid == 0)
        { 
            // child process
            close(pipe_fds[1]);
            dup2(pipe_fds[0], STDIN_FILENO);
            dup2(pipe_fds[0], STDOUT_FILENO);
            execv(bombers[i]->argv[0], bombers[i]->argv);
            perror("execv");
            exit(1);
        }
        else
        { 
            // parent process
            close(pipe_fds[0]);
            bombers[i]->pid = pid;

            // update the pipe_fd field for the bomber
            bombers[i]->pipe_fd = pipe_fds[1];
        }
    }
}

void handle_bomber_start(Maze *maze, int bomber_fd, int bomber_index)
{
    Bomber *bomber = maze->bombers[bomber_index];

    // create the BOMBER_LOCATION message
    struct outgoing_message om;
    om.type = BOMBER_LOCATION;
    om.data.new_position.x = bomber->x;
    om.data.new_position.y = bomber->y;

    // send the BOMBER_LOCATION message to the bomber
    write(bomber_fd, &om, sizeof(om));

    // print the message
    omp on;
    on.pid = bomber->pid;
    on.m = &om;
    print_output(NULL, &on, NULL, NULL);
}

void handle_bomber_see(Maze *maze, int bomber_fd, int bomber_index)
{
    Bomber *bomber = maze->bombers[bomber_index];

    // check if the bomber calling this function has already won
    if(maze->winnerPid == bomber->pid)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber win message
        struct outgoing_message om;
        om.type = BOMBER_WIN;
        write(bomber_fd, &om, sizeof(om));

        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);
        return;
    }

    // check if the bomber calling this function has already died
    if(bomber->is_alive == 0)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber die message
        struct outgoing_message om;
        om.type = BOMBER_DIE;
        write(bomber_fd, &om, sizeof(om));

        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);
        return;
    }

    int max_vision_distance = 3;
    struct object_data objects[50];
    int object_count = 0;

    // check current position, only a bomb can be here
    if(maze->maze[bomber->y][bomber->x] == 5)
    {
        objects[object_count].type = BOMB;
        objects[object_count].position.x = bomber->x;
        objects[object_count].position.y = bomber->y;
        object_count++;
    }

    // check positive x axis
    for (int i = 1; i <= max_vision_distance; ++i)
    {
        int x = bomber->x + i;
        int y = bomber->y;

        if (x < 0 || x >= maze->width)
        {
            continue;
        }

        if (maze->maze[y][x] == 1)
        {
            // obstacle
            objects[object_count].type = OBSTACLE;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
            break;
        }
        else if (maze->maze[y][x] == 2)
        {
            // bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 3)
        {
            // bomb
            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 5)
        {
            // both bomb and bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;

            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
    }

    // check negative x axis
    for (int i = -1; i >= -max_vision_distance; --i)
    {
        int x = bomber->x + i;
        int y = bomber->y;

        if (x < 0 || x >= maze->width)
        {
            continue;
        }

        if (maze->maze[y][x] == 1)
        {
            // obstacle
            objects[object_count].type = OBSTACLE;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
            break;
        }
        else if (maze->maze[y][x] == 2)
        {
            // bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 3)
        {
            // bomb
            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 5)
        {
            // both bomb and bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;

            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
    }

    // check positive y axis
    for (int i = 1; i <= max_vision_distance; ++i)
    {
        int x = bomber->x;
        int y = bomber->y + i;

        if (y < 0 || y >= maze->height)
        {
            continue;
        }

        if (maze->maze[y][x] == 1)
        {
            // obstacle
            objects[object_count].type = OBSTACLE;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
            break;
        }
        else if (maze->maze[y][x] == 2)
        {
            // bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 3)
        {
            // bomb
            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 5)
        {
            // both bomb and bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;

            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
    }

    // check negative y axis
    for (int i = -1; i >= -max_vision_distance; --i)
    {
        int x = bomber->x;
        int y = bomber->y + i;

        if (y < 0 || y >= maze->height)
        {
            continue;
        }

        if (maze->maze[y][x] == 1)
        {
            // obstacle
            objects[object_count].type = OBSTACLE;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
            break;
        }
        else if (maze->maze[y][x] == 2)
        {
            // bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 3)
        {
            // bomb
            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
        else if (maze->maze[y][x] == 5)
        {
            // both bomb and bomber
            objects[object_count].type = BOMBER;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;

            objects[object_count].type = BOMB;
            objects[object_count].position.x = x;
            objects[object_count].position.y = y;
            object_count++;
        }
    }
    
    // create the BOMBER_VISION message
    struct outgoing_message om;
    om.type = BOMBER_VISION;
    om.data.object_count = object_count;

    // send the BOMBER_VISION message to the bomber
    write(bomber_fd, &om, sizeof(om));

    // send the object_data structures to the bomber
    for (int i = 0; i < object_count; ++i)
    {
        write(bomber_fd, &objects[i], sizeof(struct object_data));
    }

    // print the message
    omp on;
    on.pid = bomber->pid;
    on.m = &om;
    print_output(NULL, &on, NULL, objects);
}

void handle_bomber_move(Maze *maze, int bomber_fd, int bomber_index, int target_x, int target_y)
{
    Bomber *bomber = maze->bombers[bomber_index];

    // check if the bomber calling this function has already won
    if(maze->winnerPid == bomber->pid)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber win message
        struct outgoing_message om;
        om.type = BOMBER_WIN;

        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);

        write(bomber_fd, &om, sizeof(om)); // if the message is sent before printing, it will not print the message
        return;
    }

    // check if the bomber calling this function has already died
    if(bomber->is_alive == 0)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber die message
        struct outgoing_message om;
        om.type = BOMBER_DIE;
        write(bomber_fd, &om, sizeof(om));
        
        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);
        return;
    }

    int dx = abs(target_x - bomber->x);
    int dy = abs(target_y - bomber->y);

    // check if the target position is valid and the move is a single step in a horizontal or vertical direction
    if (MazeIsValidPosition(maze, target_x, target_y) && ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)))
    {
        // update the maze
        maze->maze[bomber->y][bomber->x] -= 2;
        maze->maze[target_y][target_x] += 2;

        // update the bomber's position
        maze->bombers[bomber_index]->x = target_x;
        maze->bombers[bomber_index]->y = target_y; 
    }
    else
    {
        // if the move is not valid, keep the bomber's position unchanged
        target_x = bomber->x;
        target_y = bomber->y;
    }

    // create the BOMBER_LOCATION message
    struct outgoing_message om;
    om.type = BOMBER_LOCATION;
    om.data.new_position.x = target_x;
    om.data.new_position.y = target_y;
    write(bomber_fd, &om, sizeof(om)); // send the BOMBER_LOCATION message to the bomber

    // print the message
    omp on;
    on.pid = bomber->pid;
    on.m = &om;
    print_output(NULL, &on, NULL, NULL);
}

void handle_bomber_plant(Maze *maze, int bomber_fd, int bomber_index, long interval, unsigned int distance)
{
    Bomber *bomber = maze->bombers[bomber_index];

    // check if the bomber calling this function has already won
    if(maze->winnerPid == bomber->pid)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber win message
        struct outgoing_message om;
        om.type = BOMBER_WIN;
        write(bomber_fd, &om, sizeof(om));

        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);
        return;
    }

    // check if the bomber calling this function has already died
    if(bomber->is_alive == 0)
    {
        bomber->is_informed = 1; // mark bomber as informed

        // send bomber die message
        struct outgoing_message om;
        om.type = BOMBER_DIE;
        write(bomber_fd, &om, sizeof(om));

        // print the message
        omp on;
        on.pid = bomber->pid;
        on.m = &om;
        print_output(NULL, &on, NULL, NULL);

        if(maze->winnerPid != 0) // check if there is a winner
        {
            struct outgoing_message om;
            om.type = BOMBER_WIN;

            omp on;
            on.pid = maze->winnerPid;
            on.m = &om;
            print_output(NULL, &on, NULL, NULL); // print the BOMBER_WIN message

            int i = 0;
            while(maze->bombers[i]->pid != maze->winnerPid) ++i; // find the winner's index
            maze->bombers[i]->is_informed = 1; // mark winner as informed
            write(maze->bombers[i]->pipe_fd, &om, sizeof(om)); // send the BOMBER_WIN message to the winner
        } 
        return;
    }

    int bomb_x = bomber->x;
    int bomb_y = bomber->y;
    int plant_success = 0;

    // check if there is no bomb at the bomber's location
    if (maze->maze[bomb_y][bomb_x] != 3 && maze->maze[bomb_y][bomb_x] != 5)
    {
        // create and initialize the Bomb struct
        Bomb *bomb = (Bomb *)malloc(sizeof(Bomb));
        bomb->x = bomb_x;
        bomb->y = bomb_y;
        bomb->time_left = interval;
        bomb->range = distance;
        bomb->bomber_id = bomber_index;

        // create the bomb process and set up the pipe
        int pipe_fd[2];
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t bomb_pid = fork();

        if (bomb_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (bomb_pid == 0) // child process (bomb)
        {
            close(pipe_fd[0]); // close unused read end

            // prepare arguments for the bomb executable
            char interval_str[12];
            snprintf(interval_str, sizeof(interval_str), "%ld", interval);
            char *bomb_argv[] = {"./bomb", interval_str, NULL};

            // redirect stdout to the pipe
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);

            // execute the bomb executable
            execvp("./bomb", bomb_argv);

            // if execvp fails, print error and exit
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else // parent process
        {
            close(pipe_fd[1]); // close unused write end
            bomb->pid = bomb_pid;
            bomb->pipe_fd = pipe_fd[0];

            // add the bomb to the maze
            maze->maze[bomb_y][bomb_x] += 3;
            maze->bombs[maze->num_bombs] = bomb;
            maze->num_bombs++;

            plant_success = 1;
        }
    }

    // create the BOMBER_PLANT_RESULT message
    struct outgoing_message om;
    om.type = BOMBER_PLANT_RESULT;
    om.data.planted = plant_success;
    write(bomber_fd, &om, sizeof(om)); // send the BOMBER_PLANT_RESULT message to the bomber

    // print the message
    omp on;
    on.pid = bomber->pid;
    on.m = &om;
    print_output(NULL, &on, NULL, NULL);
}

void handle_bomb_explode(Maze *maze, Bomb *bomb)
{
    pid_t affected_bombers[maze->num_bombers]; // array in case all bombers are affected
    int bomber_distances[maze->num_bombers]; // distances of affected bombers to determine the winner, the order is important
    int num_affected_bombers = 0;
    int max_distance = 0;

    // check if there is a winner already
    if(maze->winnerPid)
    {
        return;
    }

    // check the range of the bomb
    // check itself
    if(maze->maze[bomb->y][bomb->x] == 5)
    {
        Bomber *bomber = find_bomber_at_position(maze, bomb->x, bomb->y);
        affected_bombers[num_affected_bombers] = bomber->pid;
        bomber_distances[num_affected_bombers] = 0;
        num_affected_bombers++;
        bomber->is_alive = 0;
        maze->maze[bomb->y][bomb->x] -= 2; // maze bomber list is not updated here
    }

    // positive x axis
    for (int i = 1; i <= bomb->range; i++)
    {
        if(bomb->x + i >= maze->width) break;

        // check the right side
        if (maze->maze[bomb->y][bomb->x + i] == 2 || maze->maze[bomb->y][bomb->x + i] == 5)
        {
            Bomber *bomber = find_bomber_at_position(maze, bomb->x + i, bomb->y);
            affected_bombers[num_affected_bombers] = bomber->pid;
            bomber_distances[num_affected_bombers] = i;
            num_affected_bombers++;
            bomber->is_alive = 0;
            maze->maze[bomb->y][bomb->x + i] -= 2;

            max_distance = i < max_distance ? max_distance : i;
        }
        else if (maze->maze[bomb->y][bomb->x + i] == 1)
        {
            Obstacle *obstacle = find_obstacle_at_position(maze, bomb->x + i, bomb->y);
            ObstacleDamage(maze, obstacle);
            break;
        }
        
    }

    // negative x axis
    for (int i = 1; i <= bomb->range; i++)
    {
        if(bomb->x - i < 0) break;

        // check the left side
        if (maze->maze[bomb->y][bomb->x - i] == 2 || maze->maze[bomb->y][bomb->x - i] == 5)
        {
            Bomber *bomber = find_bomber_at_position(maze, bomb->x - i, bomb->y);
            affected_bombers[num_affected_bombers] = bomber->pid;
            bomber_distances[num_affected_bombers] = i;
            num_affected_bombers++;
            bomber->is_alive = 0;
            maze->maze[bomb->y][bomb->x - i] -= 2;

            max_distance = i < max_distance ? max_distance : i;
        }
        else if (maze->maze[bomb->y][bomb->x - i] == 1)
        {
            Obstacle *obstacle = find_obstacle_at_position(maze, bomb->x - i, bomb->y);
            ObstacleDamage(maze, obstacle);
            break;
        }
    }

    // positive y axis
    for (int i = 1; i <= bomb->range; i++)
    {
        if(bomb->y + i >= maze->height) break;

        // check the top side
        if (maze->maze[bomb->y + i][bomb->x] == 2 || maze->maze[bomb->y + i][bomb->x] == 5)
        {           
            Bomber *bomber = find_bomber_at_position(maze, bomb->x, bomb->y + i);
            affected_bombers[num_affected_bombers] = bomber->pid;
            bomber_distances[num_affected_bombers] = i;
            num_affected_bombers++;
            bomber->is_alive = 0;
            maze->maze[bomb->y + i][bomb->x] -= 2;

            max_distance = i < max_distance ? max_distance : i;
        }
        else if (maze->maze[bomb->y + i][bomb->x] == 1)
        {
            Obstacle *obstacle = find_obstacle_at_position(maze, bomb->x, bomb->y + i);
            ObstacleDamage(maze, obstacle);
            break;
        }
    }

    // negative y axis
    for (int i = 1; i <= bomb->range; i++)
    {
        if(bomb->y - i < 0) break;

        // check the bottom side
        if (maze->maze[bomb->y - i][bomb->x] == 2 || maze->maze[bomb->y - i][bomb->x] == 5)
        {
            Bomber *bomber = find_bomber_at_position(maze, bomb->x, bomb->y - i);
            affected_bombers[num_affected_bombers] = bomber->pid;
            bomber_distances[num_affected_bombers] = i;
            num_affected_bombers++;
            bomber->is_alive = 0;
            maze->maze[bomb->y - i][bomb->x] -= 2;

            max_distance = i < max_distance ? max_distance : i;
        }
        else if (maze->maze[bomb->y - i][bomb->x] == 1)
        {
            Obstacle *obstacle = find_obstacle_at_position(maze, bomb->x, bomb->y - i);
            ObstacleDamage(maze, obstacle);
            break;
        }
    }

    // remove the bomb
    maze->maze[bomb->y][bomb->x] -= 3;
    // maze->num_bombs--; // maze bomb list is not updated

    // count the number of alive bombers
    int alive_bombers = 0;
    for (int i = 0; i < maze->num_bombers; i++)
    {
        if (maze->bombers[i]->is_alive == 1)
        {
            alive_bombers++;
        }
    }

    maze->num_alive_bombers = alive_bombers;

    // if there is only one bomber alive, end the game
    if (maze->num_alive_bombers == 1)
    {
        for (int i = 0; i < maze->num_bombers; i++)
        {
            if (maze->bombers[i]->is_alive == 1)
            {
                maze->winnerPid =  maze->bombers[i]->pid;
            }
        }
    }
    else if (maze->num_alive_bombers == 0)
    {
        // if there is no bomber alive, end the game
        // check max distance and distances array

        for(int i = 0; i < num_affected_bombers; i++)
        {
            if(bomber_distances[i] == max_distance)
            {
                maze->winnerPid =  affected_bombers[i];
            }
        }
    }
}

int main()
{
    Maze *maze = NULL;
    Bomber **bombers = NULL;
    int num_bombers = 0;
    int all_informed = 0;

    // read the input information about the game from standard input
    takeInputs(&maze, &bombers, &num_bombers);

    // fork the bomber processes, create pipes, and redirect standard input and output
    spawnBomberProcesses(bombers, num_bombers);

    // set up pollfd structures for bombs and bombers
    struct pollfd *bomb_fds = (struct pollfd *)calloc(maze->num_bombs, sizeof(struct pollfd));
    struct pollfd *bomber_fds = (struct pollfd *)calloc(num_bombers, sizeof(struct pollfd));

    for (int i = 0; i < num_bombers; ++i)
    {
        bomber_fds[i].fd = bombers[i]->pipe_fd;
        bomber_fds[i].events = POLLIN;
    }

    // main game loop
    while (maze->num_alive_bombers > 1 || !all_informed)
    {
        int active_bombs = 0;
        for (int i = 0; i < maze->num_bombs; ++i)
        {
            if (maze->bombs[i]->pid > 0)
            {
                bomb_fds[i].fd = maze->bombs[i]->pipe_fd;
                bomb_fds[i].events = POLLIN;
                active_bombs++;
            }
            else
            {
                bomb_fds[i].fd = -1;
                bomb_fds[i].events = 0;
            }
        }

        int ready_bombs = poll(bomb_fds, maze->num_bombs, 1); // poll with a timeout of 1ms
        if (ready_bombs > 0)
        {
            // handle input from bomb pipes here
            for (int i = 0; i < maze->num_bombs; ++i)
            {
                if (bomb_fds[i].revents & POLLIN)
                {
                    struct incoming_message im;
                    read(bomb_fds[i].fd, &im, sizeof(im));

                    switch (im.type)
                    {
                        case BOMB_EXPLODE:
                            if(maze->winnerPid == 0)
                            {
                                // find the bomb object for the current file descriptor
                                Bomb *exploding_bomb = NULL;
                                for (int j = 0; j < maze->num_bombs; ++j)
                                {
                                    if (maze->bombs[j]->pipe_fd == bomb_fds[i].fd)
                                    {
                                        exploding_bomb = maze->bombs[j];
                                        break;
                                    }
                                }
                                // call handle_bomb_explode with the found bomb object
                                if (exploding_bomb != NULL)
                                {
                                    imp in;
                                    in.pid = exploding_bomb->pid;
                                    in.m = &im;
                                    print_output(&in, NULL, NULL, NULL);
                                    
                                    handle_bomb_explode(maze, exploding_bomb);

                                    // reap the bomb process
                                    waitpid(exploding_bomb->pid, NULL, 0);
                                    exploding_bomb->pid = 0;
                                }
                            }
                            break;
                        default:
                            // unexpected message type from a bomb, you can handle it as an error or ignore it
                            break;
                    }
                }
            }
        }

        int ready_bombers = poll(bomber_fds, num_bombers, 1); // poll with a timeout of 1ms
        if (ready_bombers > 0)
        {
            // handle input from bomber pipes here
            for (int i = 0; i < num_bombers; ++i)
            {
                if (bomber_fds[i].revents & POLLIN)
                {
                    struct incoming_message im;
                    read(bomber_fds[i].fd, &im, sizeof(im));

                    imp in;
                    in.pid = bombers[i]->pid;
                    in.m = &im;

                    // find the bomber
                    Bomber *bomber = NULL;
                    for (int j = 0; j < num_bombers; ++j)
                    {
                        if (bombers[j]->pipe_fd == bomber_fds[i].fd)
                        {
                            bomber = bombers[j];
                            break;
                        }
                    }

                    switch (im.type)
                    {
                        case BOMBER_START:
                            print_output(&in, NULL, NULL, NULL);  
                            handle_bomber_start(maze, bomber_fds[i].fd, i);                         
                            break;
                        case BOMBER_SEE:
                            if(!bomber->is_informed) 
                            {
                                print_output(&in, NULL, NULL, NULL); 
                                handle_bomber_see(maze, bomber_fds[i].fd, i);
                            }                   
                            break;
                        case BOMBER_MOVE: 
                            if(!bomber->is_informed) 
                            {
                                print_output(&in, NULL, NULL, NULL);               
                                handle_bomber_move(maze, bomber_fds[i].fd, i, im.data.target_position.x, im.data.target_position.y);
                            }
                            break;
                        case BOMBER_PLANT:
                            if(!bomber->is_informed)
                            {
                                print_output(&in, NULL, NULL, NULL);                    
                                handle_bomber_plant(maze, bomber_fds[i].fd, i, im.data.bomb_info.interval, im.data.bomb_info.radius);                                  
                            }               
                            break;
                        default:
                            // unexpected message type from a bomber, you can handle it as an error or ignore it
                            break;
                    }
                }
            }

            // reap bomber processes
            for (int i = 0; i < maze->num_bombers; i++)
            {
                if (maze->bombers[i]->is_informed == 1)
                {
                    waitpid(maze->bombers[i]->pid, NULL, 0);
                }
            }

            // check if everyone is informed
            all_informed = 1;
            for (int i = 0; i < num_bombers; ++i)
            {
                if (bombers[i]->is_informed == 0)
                {
                    all_informed = 0;
                    break;
                }
            }
        }
        usleep(1000); // sleep for 1ms
    }

    // wait for all bombs to explode
    int bombs = 0;
    for (int i = 0; i < maze->num_bombs; ++i)
    {
        if (maze->bombs[i]->pid > 0)
        {
            bombs++;
        }
    }

    // reap the winner bomber process
    for (int i = 0; i < maze->num_bombers; i++)
    {
        if (maze->bombers[i]->is_alive == 1)
        {
            waitpid(maze->bombers[i]->pid, NULL, 0);
        }
    }
    return 0;
}
