// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "the6.h"

#define MAX_WEIGHT 1000
#define MIN_WEIGHT 5

Pipeline* createPipeline(int v1, int v2, int cost_of_consumption, int id) {
    Pipeline* p = new Pipeline;
	p->id = id;
	p->end1 = v1;
	p->end2 = v2;
	p->cost_of_consumption = cost_of_consumption;
	return p;
}

void randomGraph(vector<Pipeline*>& pipelines, int size) {
    
    int numOfVerts = size;
    int degree = numOfVerts/5;	
    int numOfEdges = (degree * numOfVerts) / 3;
    numOfEdges = rand() % numOfEdges;
    numOfEdges = numOfEdges < numOfVerts ? numOfVerts : numOfEdges;
    	
	
	// generate edges
	vector<int> current_degrees;
	for (int i = 0; i < numOfVerts; i++) {
	    current_degrees.push_back(0);
	    pipelines.push_back(createPipeline(i, i, rand() % MAX_WEIGHT + MIN_WEIGHT, pipelines.size()));
	}
	
	for (int i = 0; i < numOfEdges; ) {
	    int v1 = rand() % numOfVerts;
	    int v2 = rand() % numOfVerts;
	    
	    if (current_degrees[v1] == degree || current_degrees[v2] == degree)
	        continue;
	            
	    current_degrees[v1]++;
	    current_degrees[v2]++;
	    
	    pipelines.push_back(createPipeline(v1, v2, rand() % MAX_WEIGHT + MIN_WEIGHT, pipelines.size()));
	    i++;
	}
	
	bool make_connected = rand() % 2;
	
	if (make_connected) {
    	// define components
    	vector<vector<int>> components; // disconnected subgraphs
    	for (int i = 0; i < numOfVerts; i++) {
    	    vector<int> component;
    	    component.push_back(i);
    	    component.push_back(i);
    	    components.push_back(component);
    	}
	
    	for (int i = 0; i < numOfEdges ; i++) {
    	    int v1 = pipelines[i+numOfVerts]->end1;
    	    int v2 = pipelines[i+numOfVerts]->end2;
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

	        pipelines.push_back(createPipeline(v1, v2, rand() % MAX_WEIGHT + MIN_WEIGHT, pipelines.size()));
	    
	        for (int c = 1; c < components[c2].size(); c++)
	            components[c1].push_back(components[c2][c]);
	    }
	}
    
}

void copyGraph(vector<Pipeline*>& pipelines, vector<Pipeline*>& pipelines_copy) {
    
    for (int i = 0; i < pipelines_copy.size(); i++) {
        if (pipelines_copy[i])
            delete pipelines_copy[i];
        pipelines_copy[i] = NULL;
    }
    pipelines_copy.clear();
    
    for (int i = 0; i < pipelines.size(); i++) {
        Pipeline* p = createPipeline(pipelines[i]->end1, pipelines[i]->end2, pipelines[i]->cost_of_consumption, pipelines[i]->id);
        pipelines_copy.push_back(p);
    }
    
}

void manualGraph(vector<Pipeline*>& pipelines, int& size) {
    
    // EXAMPLE-1
    
    // size = 6;
    // pipelines.push_back(createPipeline(0, 0, 90, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 1, 30, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 5, 20, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 1, 20, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 2, 75, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 3, 55, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 2, 60, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 3, 80, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 3, 40, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 4, 45, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 4, 65, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 5, 90, pipelines.size()));
    // pipelines.push_back(createPipeline(5, 5, 15, pipelines.size()));
    
    
    // EXAMPLE-2

    // size = 7;
    // pipelines.push_back(createPipeline(0, 1, 2, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 2, 4, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 3, 1, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 0, 5, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 3, 3, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 4, 10, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 1, 6, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 3, 2, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 5, 5, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 2, 6, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 4, 7, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 5, 8, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 6, 4, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 3, 7, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 6, 6, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 4, 4, pipelines.size()));
    // pipelines.push_back(createPipeline(5, 6, 1, pipelines.size()));
    // pipelines.push_back(createPipeline(5, 5, 4, pipelines.size()));
    // pipelines.push_back(createPipeline(6, 6, 10, pipelines.size()));

    
    // EXAMPLE-3

    // size = 13;
    // pipelines.push_back(createPipeline(0, 0, 210, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 1, 100, pipelines.size()));
    // pipelines.push_back(createPipeline(0, 2, 250, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 1, 160, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 4, 280, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 4, 450, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 5, 180, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 8, 200, pipelines.size()));
    // pipelines.push_back(createPipeline(1, 9, 200, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 2, 110, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 3, 140, pipelines.size()));
    // pipelines.push_back(createPipeline(2, 4, 330, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 3, 210, pipelines.size()));
    // pipelines.push_back(createPipeline(3, 4, 320, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 4, 350, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 5, 340, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 10, 100, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 11, 470, pipelines.size()));
    // pipelines.push_back(createPipeline(4, 12, 310, pipelines.size()));  
    // pipelines.push_back(createPipeline(5, 5, 280, pipelines.size()));
    // pipelines.push_back(createPipeline(5, 6, 260, pipelines.size()));
    // pipelines.push_back(createPipeline(5, 7, 220, pipelines.size()));
    // pipelines.push_back(createPipeline(6, 6, 320, pipelines.size()));
    // pipelines.push_back(createPipeline(6, 7, 180, pipelines.size()));
    // pipelines.push_back(createPipeline(7, 7, 320, pipelines.size()));
    // pipelines.push_back(createPipeline(8, 8, 260, pipelines.size()));
    // pipelines.push_back(createPipeline(8, 9, 300, pipelines.size()));  
    // pipelines.push_back(createPipeline(9, 9, 400, pipelines.size()));
    // pipelines.push_back(createPipeline(10, 10, 440, pipelines.size()));
    // pipelines.push_back(createPipeline(10, 11, 290, pipelines.size()));
    // pipelines.push_back(createPipeline(11, 11, 290, pipelines.size()));
    // pipelines.push_back(createPipeline(11, 12, 270, pipelines.size()));
    // pipelines.push_back(createPipeline(12, 12, 300, pipelines.size())); 
    
    
    // EXAMPLE-4

    size = 15;
    pipelines.push_back(createPipeline(0, 0, 18, pipelines.size()));
    pipelines.push_back(createPipeline(0, 4, 36, pipelines.size()));
    pipelines.push_back(createPipeline(0, 5, 27, pipelines.size()));
    pipelines.push_back(createPipeline(0, 7, 10, pipelines.size()));
    pipelines.push_back(createPipeline(0, 11, 23, pipelines.size()));
    pipelines.push_back(createPipeline(1, 1, 26, pipelines.size()));
    pipelines.push_back(createPipeline(1, 8, 20, pipelines.size()));
    pipelines.push_back(createPipeline(2, 2, 18, pipelines.size()));
    pipelines.push_back(createPipeline(2, 5, 21, pipelines.size()));
    pipelines.push_back(createPipeline(2, 13, 10, pipelines.size()));
    pipelines.push_back(createPipeline(2, 14, 17, pipelines.size()));
    pipelines.push_back(createPipeline(3, 3, 25, pipelines.size()));
    pipelines.push_back(createPipeline(3, 13, 22, pipelines.size()));
    pipelines.push_back(createPipeline(3, 14, 35, pipelines.size()));
    pipelines.push_back(createPipeline(4, 4, 36, pipelines.size()));
    pipelines.push_back(createPipeline(5, 5, 10, pipelines.size()));
    pipelines.push_back(createPipeline(5, 8, 31, pipelines.size()));
    pipelines.push_back(createPipeline(6, 6, 12, pipelines.size()));
    pipelines.push_back(createPipeline(6, 9, 27, pipelines.size()));  
    pipelines.push_back(createPipeline(6, 11, 15, pipelines.size()));
    pipelines.push_back(createPipeline(7, 7, 16, pipelines.size()));
    pipelines.push_back(createPipeline(7, 11, 18, pipelines.size()));
    pipelines.push_back(createPipeline(8, 8, 15, pipelines.size()));
    pipelines.push_back(createPipeline(8, 10, 30, pipelines.size()));
    pipelines.push_back(createPipeline(8, 12, 23, pipelines.size()));
    pipelines.push_back(createPipeline(8, 13, 24, pipelines.size()));
    pipelines.push_back(createPipeline(9, 9, 22, pipelines.size()));
    pipelines.push_back(createPipeline(10, 10, 30, pipelines.size()));  
    pipelines.push_back(createPipeline(10, 13, 27, pipelines.size()));
    pipelines.push_back(createPipeline(11, 11, 32, pipelines.size()));
    pipelines.push_back(createPipeline(12, 12, 28, pipelines.size()));
    pipelines.push_back(createPipeline(13, 13, 25, pipelines.size()));
    pipelines.push_back(createPipeline(13, 14, 25, pipelines.size()));
    pipelines.push_back(createPipeline(14, 14, 40, pipelines.size())); 

    
}

void printGraphInLine(vector<Pipeline*> pipelines){
	
	std::cout << "{\n";
	for(int i = 0; i < pipelines.size(); i++){
	    std::cout << " PIPELINE " << i << "," << std::endl;
	    std::cout << "     between: " << pipelines[i]->end1 << " and " << pipelines[i]->end2 << "," << std::endl;
	    std::cout << "     cost of consumption: " << pipelines[i]->cost_of_consumption << std::endl;
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
    std::cout << std::endl;
    
}



void test(){
    clock_t begin, end;
    double duration;
    
    int size = 15;
    vector<Pipeline*> pipelines, pipelines_copy;
	// randomGraph(pipelines, size);
    manualGraph(pipelines, size);
    copyGraph(pipelines, pipelines_copy);
    int num_of_pipelines = pipelines.size();

    std::cout << "Given Pipelines: "<< std::endl;
	printGraphInLine(pipelines);

    std::cout << "\nNumber of Buildings: \n" << size << std::endl;

    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    // PART-I    
    vector<int> pipelined_structure = plan_min_cost_pipeline_usage(pipelines, size);
    
    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = (1000.0 * ((double) end - begin)) / CLOCKS_PER_SEC;
    std::cout << "Duration for PART-I: " << duration << " miliseconds." << std::endl;
	
	std::cout << "\nPART-I: Builded Pipelined Structure of the Algorithm: " << std::endl;
    printVectorInLine(pipelined_structure);

    // PART-II
    Pipeline* new_pipeline = createPipeline(rand() % size, rand() % size, rand() % MAX_WEIGHT + MIN_WEIGHT, num_of_pipelines);
    vector<Pipeline*> part1_solution;
    for (int i = 0; i < pipelined_structure.size(); i++)
        part1_solution.push_back(pipelines_copy[pipelined_structure[i]]);
    
    
    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;
    
    vector<int> updated_pipelined_structure = optimize_plan(part1_solution, new_pipeline);
    
    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = (1000.0 * ((double) end - begin)) / CLOCKS_PER_SEC;
    std::cout << "Duration for PART-II: " << duration << " miliseconds." << std::endl;
       
    std::cout << "\nPART-II: Updated pipelined structure of the Algorithm: " << std::endl;
	printVectorInLine(updated_pipelined_structure);

    std::cout << "---------------------------------------------------";
    std::cout << "\n" << std::endl;

}

int main()
{
    srand(time(0));
    test();
    return 0;
}
