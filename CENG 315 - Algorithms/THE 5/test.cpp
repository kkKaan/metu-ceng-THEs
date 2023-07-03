// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "the5.h"


void randomGraph(vector<Room*>& maze, int size) {
    
    int numOfVerts = size;
    int degree = 4;	
    int numOfEdges = (degree * numOfVerts) / 3;
    numOfEdges = rand() % numOfEdges;
    numOfEdges = numOfEdges < numOfVerts ? numOfVerts : numOfEdges;
    	
    // generate rooms	
	for (int i = 0; i < numOfVerts; i++)
	{
	    Room* room = new Room;
	    room->id = i;
	    room->content = '-';
	    maze.push_back(room);
	}
	
	
	int r = rand() % numOfVerts;
	maze[r]->content = '*';
	
	// generate edges
	vector<vector<int>> edges;
	
	for (int i = 0; i < numOfEdges; ) {
	    int v1 = rand() % numOfVerts;
	    int v2 = rand() % numOfVerts;
	    
	    if (v1 == v2)
	        continue;
	   
	    else {
	        bool retry = false;
	        for (int j = 0; j < edges.size(); j++) {
	            if ((edges[j][0] == v1 && edges[j][1] == v2) || (edges[j][0] == v2 && edges[j][1] == v1)) {
	                retry = true;
	                break;
	            }
	        }
	        
	        if (retry)
	            continue;
	        if (maze[v1]->neighbors.size() == degree || maze[v2]->neighbors.size() == degree)
	            continue;
	        
	        vector<int> edge;
	        edge.push_back(v1);
	        edge.push_back(v2);
	        edges.push_back(edge);
	        maze[v1]->neighbors.push_back(maze[v2]);
	        maze[v2]->neighbors.push_back(maze[v1]);
	        i++;
	    }     
	}
	
	// define components
	vector<vector<int>> components; // disconnected subgraphs
	for (int i = 0; i < numOfVerts; i++) {
	    vector<int> component;
	    component.push_back(i);
	    component.push_back(i);
	    components.push_back(component);
	}
	
	for (int i = 0; i < numOfEdges ; i++) {
	    int v1 = edges[i][0];
	    int v2 = edges[i][1];
	    if (components[v1][0] == components[v2][0])
	        continue;
	    else {
	        int c1 = components[v1][0];
	        int c2 = components[v2][0];
	            
	        for (int c = 1; c < components[c2].size(); c++) {
	            components[c1].push_back(components[c2][c]);
	            components[components[c2][c]][0] = c1;
	        }
	    }
	}
	
	vector<int> component_ids;
	for (int i = 0; i < numOfVerts; i++) {
        if (components[i][0] == i)
            component_ids.push_back(i);
	}
	
	// make connected
	for (int i = 1; i < component_ids.size(); i++) {
	    int c1 = component_ids[0];
	    int c2 = component_ids[i];
	    
	    int ind1 = rand() % (components[c1].size()-1) + 1;
	    int ind2 = rand() % (components[c2].size()-1) + 1;
	    
	    int v1 = components[c1][ind1];
	    int v2 = components[c2][ind2];
	    
	    maze[v1]->neighbors.push_back(maze[v2]);
	    maze[v2]->neighbors.push_back(maze[v1]);
	    
	    for (int c = 1; c < components[c2].size(); c++)
	        components[c1].push_back(components[c2][c]);
	}
    
}


void manualGraph(vector<Room*>& maze, int size)
{
    for (int i = 0; i < size; i++)
	{
	    Room* room = new Room;
	    room->id = i;
	    room->content = '-';
	    maze.push_back(room);
	}
	
	// Do not forget to change the size at the beginning of the test()
	
	// EXAMPLE-1
	/*
	maze[4]->content = '*';
	
	maze[0]->neighbors.push_back(maze[3]);
	maze[0]->neighbors.push_back(maze[9]);
	maze[1]->neighbors.push_back(maze[6]);
	maze[1]->neighbors.push_back(maze[9]);
	maze[2]->neighbors.push_back(maze[6]);
	maze[3]->neighbors.push_back(maze[0]);
	maze[3]->neighbors.push_back(maze[5]);
	maze[4]->neighbors.push_back(maze[9]);
	maze[5]->neighbors.push_back(maze[3]);
	maze[6]->neighbors.push_back(maze[1]);
	maze[6]->neighbors.push_back(maze[2]);
	maze[7]->neighbors.push_back(maze[8]);
	maze[7]->neighbors.push_back(maze[9]);
	maze[8]->neighbors.push_back(maze[7]);
	maze[9]->neighbors.push_back(maze[0]);
	maze[9]->neighbors.push_back(maze[1]);
	maze[9]->neighbors.push_back(maze[4]);
	maze[9]->neighbors.push_back(maze[7]);
	*/
	
	// EXAMPLE-2
	/*
	maze[4]->content = '*';
	
	maze[0]->neighbors.push_back(maze[3]);
	maze[0]->neighbors.push_back(maze[9]);
	maze[1]->neighbors.push_back(maze[6]);
	maze[1]->neighbors.push_back(maze[9]);
	maze[2]->neighbors.push_back(maze[6]);
	maze[2]->neighbors.push_back(maze[8]);
	maze[3]->neighbors.push_back(maze[0]);
	maze[3]->neighbors.push_back(maze[5]);
	maze[3]->neighbors.push_back(maze[6]);
	maze[4]->neighbors.push_back(maze[9]);
	maze[5]->neighbors.push_back(maze[3]);
	maze[6]->neighbors.push_back(maze[1]);
	maze[6]->neighbors.push_back(maze[2]);
	maze[6]->neighbors.push_back(maze[3]);
	maze[7]->neighbors.push_back(maze[8]);
	maze[7]->neighbors.push_back(maze[9]);
	maze[8]->neighbors.push_back(maze[2]);
	maze[8]->neighbors.push_back(maze[7]);
	maze[9]->neighbors.push_back(maze[0]);
	maze[9]->neighbors.push_back(maze[1]);
	maze[9]->neighbors.push_back(maze[4]);
	maze[9]->neighbors.push_back(maze[7]);
	*/
	
	// EXAMPLE-3
	/*
	maze[7]->content = '*';
	
	maze[0]->neighbors.push_back(maze[2]);
	maze[1]->neighbors.push_back(maze[8]);
	maze[1]->neighbors.push_back(maze[5]);
	maze[1]->neighbors.push_back(maze[3]);
	maze[2]->neighbors.push_back(maze[6]);
	maze[2]->neighbors.push_back(maze[4]);
	maze[2]->neighbors.push_back(maze[0]);
	maze[3]->neighbors.push_back(maze[1]);
	maze[3]->neighbors.push_back(maze[7]);
	maze[3]->neighbors.push_back(maze[6]);
	maze[4]->neighbors.push_back(maze[2]);
	maze[5]->neighbors.push_back(maze[1]);
	maze[6]->neighbors.push_back(maze[8]);
	maze[6]->neighbors.push_back(maze[3]);
	maze[6]->neighbors.push_back(maze[2]);
	maze[7]->neighbors.push_back(maze[3]);
	maze[8]->neighbors.push_back(maze[1]);
	maze[8]->neighbors.push_back(maze[6]);
	*/
	
	// EXAMPLE-4
	maze[14]->content = '*';
	
	maze[0]->neighbors.push_back(maze[7]);
	maze[0]->neighbors.push_back(maze[4]);
	maze[0]->neighbors.push_back(maze[11]);
	maze[0]->neighbors.push_back(maze[5]);
	maze[1]->neighbors.push_back(maze[8]);
	maze[2]->neighbors.push_back(maze[13]);
	maze[2]->neighbors.push_back(maze[5]);
	maze[2]->neighbors.push_back(maze[14]);
	maze[3]->neighbors.push_back(maze[14]);
	maze[3]->neighbors.push_back(maze[13]);
	maze[4]->neighbors.push_back(maze[0]);
	maze[5]->neighbors.push_back(maze[0]);
	maze[5]->neighbors.push_back(maze[8]);
	maze[5]->neighbors.push_back(maze[2]);
	maze[6]->neighbors.push_back(maze[9]);
	maze[6]->neighbors.push_back(maze[11]);
	maze[7]->neighbors.push_back(maze[11]);
	maze[7]->neighbors.push_back(maze[0]);
	maze[8]->neighbors.push_back(maze[10]);
	maze[8]->neighbors.push_back(maze[5]);
	maze[8]->neighbors.push_back(maze[1]);
	maze[8]->neighbors.push_back(maze[12]);
	maze[8]->neighbors.push_back(maze[13]);
	maze[9]->neighbors.push_back(maze[6]);
	maze[10]->neighbors.push_back(maze[8]);
	maze[10]->neighbors.push_back(maze[13]);
	maze[11]->neighbors.push_back(maze[0]);
	maze[11]->neighbors.push_back(maze[6]);
	maze[11]->neighbors.push_back(maze[7]);
	maze[12]->neighbors.push_back(maze[8]);
	maze[13]->neighbors.push_back(maze[8]);
	maze[13]->neighbors.push_back(maze[2]);
	maze[13]->neighbors.push_back(maze[3]);
	maze[13]->neighbors.push_back(maze[14]);
	maze[13]->neighbors.push_back(maze[10]);
	maze[14]->neighbors.push_back(maze[3]);
	maze[14]->neighbors.push_back(maze[2]);
	maze[14]->neighbors.push_back(maze[13]);
	
}


void printGraphInLine(vector<Room*> maze){
	
	std::cout << "{\n";
	for(int i = 0; i < maze.size(); i++){
	    std::cout << " ROOM " << i << "," << std::endl;
	    std::cout << "     content: '" << maze[i]->content << "'," << std::endl;
	    std::cout << "     neighbors: ";
	    for (int j = 0; j < maze[i]->neighbors.size(); j++) {
		    std::cout << maze[i]->neighbors[j]->id;
		    if (j == maze[i]->neighbors.size() - 1)
			    std::cout << std::endl;
		    else
			    std::cout << ", ";
	    }
	}
	std::cout << "}" << std::endl;

}

void printVectorInLine(vector<int> output) {
    
    for(int i = 0; i < output.size(); i++) {
        std::cout << output[i];
        if (i == output.size() - 1)
            continue;
        else
            std::cout << ", ";
    }
    std::cout << endl;
    
}



void test(){
    clock_t begin, end;
    double duration;
    
    int size = 15;
    vector<int> path;
    vector<Room*> maze;
	//randomGraph(maze, size);
    manualGraph(maze, size);

    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    path = maze_trace(maze);

    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Given maze: "<< std::endl;
	printGraphInLine(maze);
    
	std::cout << "\nNumber of Rooms: \n" << size << std::endl;
	
	std::cout << "\nMaze Trace: " << std::endl;
    std::cout << "\nReturned path :";
    printVectorInLine(path);

    std::cout << "---------------------------------------------------";
    std::cout << "\n" << std::endl;

}

int main()
{
    srand(time(0));
    test();
    return 0;
}
