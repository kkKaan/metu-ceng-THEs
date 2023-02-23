#include "the5.h"

void DFS(Room* cur, vector<int>& visited, vector<int>& path, int& found) 
{
    // add the current room to the path and mark it as visited.
    path.push_back(cur->id);
    visited[cur->id] = 1;

    // if the treasure is found, return.
    if (cur->content == '*') 
    {
        found = 1;
        return;
    }

    // recursively search the neighbors of the current room.
    for (int i = 0; i < cur->neighbors.size() && !found; i++) 
    {
        if (!visited[cur->neighbors[i]->id]) 
        {
            DFS(cur->neighbors[i], visited, path, found);
            path.push_back(cur->id);
        }
    }
}

vector<int> maze_trace(vector<Room*> maze) 
{
    vector<int> path;
    int found = 0;

    // visited info array
    vector<int> visited(maze.size());

    for(int a = 0; a < maze.size(); a++)
    {
        visited[a] = 0;
    }

    // start the search from the first room in the maze
    DFS(maze[0], visited, path, found);

    // return the path of rooms visited
    return path;
}