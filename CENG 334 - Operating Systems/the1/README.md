# Bomberman Game Project

## Overview
This is a C program for a simple text-based Bomberman game. The game consists of a maze, where multiple players (bombers) can move, plant bombs, and attempt to eliminate each other. The last remaining player wins the game. For a detailed information check the PDF.

## Code Structure
- `bgame.c`: Contains the main game loop and logic.
- `bomb`: Executable for bomb explosions.
- Other C files (not included in this code snippet) should contain specific functions used in the main game loop.

## Game Mechanics
### Bombers
- Initiative: Each bomber has its initiative, which determines the order in which they send messages to the controller.
- Movement: Bombers can move one step at a time in either the horizontal (x) or vertical (y) axis within the maze.
- Obstacle Vision: Bombers can "see" their surroundings up to three steps away in all directions except their own location. Obstacles can block their vision along specific directions.
- Bomb Planting: Bombers can plant bombs at their current location. Bomb placement is successful only if no other bomb exists at that location.
- Coordinates: Bombers initially do not know their coordinates and send a "Start" message to the controller upon starting the game.
- Death: Bombers can die from explosions, including their bombs. When a bomber dies, it cannot send further messages.

### Bombs
- Explode: Bombs explode after a certain duration, with some random variation for unpredictability. The explosion follows a cross pattern, extending a certain distance in four directions: -x, +x, -y, +y. The explosion can be blocked by obstacles and affects any bomber within its range.
- Obstacle Interaction: When an explosion encounters an obstacle, it loses one point of durability. If the obstacle's durability reaches zero, it is removed from the maze.
- Player Elimination: If the explosion reaches a bomber, the bomber dies. Bombers can be eliminated by their own bomb explosions.

## Communication
The communication between the controller and game entities (bombers and bombs) is carried out via bidirectional pipes, which allow data to flow in both directions. These pipes are created using the socketpair() function, ensuring that data written to one end can be read from the other.

## Controller Logic
The controller manages an arbitrary number of bombers and bombs. It creates and reads requests from multiple file descriptors, ensuring that it does not block on any socket. To achieve this, it can use system calls like select() or poll() to check if there is data to be read on a particular socket.

1- Select/Poll on Bomb Sockets: Check for data on the socket file descriptors of bombs. For all file descriptors that are ready (have data), read the bomb's request and serve it.

2- Select/Poll on Bomber Sockets: Check for data on the socket file descriptors of active bombers. For all file descriptors that are ready (have data), read the bomber's request and serve it.

3- Sleep for 1 Millisecond: To prevent CPU hogging, pause briefly between iterations.

4- Wait for Bombs to Finish: Continue to process messages until there is only one active bomber left or until all bombers are informed about the game's outcome. Wait for any remaining bombs to explode and finish the game.
