#include <iostream>  
#include <climits>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

vector<int> maze_trace(vector<Room*> maze);