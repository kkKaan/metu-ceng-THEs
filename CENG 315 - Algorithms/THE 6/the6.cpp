#include "the6.h" 

/* 
    in the6.h "struct Pipeline" is defined as below:
    
    struct Pipeline {
        int id;                     // pipeline id
        int end1;                   // id of the building-1
        int end2;                   // id of the building-2
        int cost_of_consumption;    // amount/cost of consumption for pipeline
    };

*/

struct Edge 
{
    int pid; // pipeline id
    int to; // destination node
    int cost; // cost of the edge
};

vector<vector<Edge>> createMinSpanAdjList(vector<Pipeline*> pipelines, vector<int> min_spanning_tree, int num_of_buildings)
{
    // create an adjacency list to represent the graph
    vector<vector<Edge>> adj_list(num_of_buildings);

    for (int pid : min_spanning_tree)
    {
        // add the edge with the given pipeline id to the adjacency list
        adj_list[pipelines[pid]->end1].push_back({pid, pipelines[pid]->end2, pipelines[pid]->cost_of_consumption});
        adj_list[pipelines[pid]->end2].push_back({pid, pipelines[pid]->end1, pipelines[pid]->cost_of_consumption});
    }
    return adj_list;
}

bool hasPath(int from, int to, vector<vector<Edge>>& adj_list)
{
    queue<int> q;
    // mark the starting node as visited
    vector<bool> visited(adj_list.size(), false);
    visited[from] = true;
    q.push(from);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        // check if this is the destination node
        if (curr == to)
        {
            return true;
        }

        // iterate through the edges of the current node
        for (Edge& e : adj_list[curr])
        {
            // check if the destination node has been visited
            if (!visited[e.to])
            {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }

    // if the queue is empty and we haven't found the destination node, then there is no path
    return false;
}

vector<int> plan_min_cost_pipeline_usage(vector<Pipeline*> pipelines, int num_of_buildings) 
{
    // create an adjacency list to represent the graph
    vector<vector<Edge>> adj_list(num_of_buildings);

    for (Pipeline* p : pipelines) 
    {
        // add an edge to the adjacency list
        adj_list[p->end1].push_back({p->id, p->end2, p->cost_of_consumption});
        if(p->end1 != p->end2) adj_list[p->end2].push_back({p->id, p->end1, p->cost_of_consumption});
    }

    vector<int> min_spanning_tree;
    vector<int> visitedP(pipelines.size(), 0);
    vector<int> hasHeat(num_of_buildings, 0);

    for (int i = 0; i < num_of_buildings; i++)
    {
        int min_cost = INT_MAX;
        int min_edge = -1;
        vector<vector<Edge>> min_span_adj_list = createMinSpanAdjList(pipelines, min_spanning_tree, num_of_buildings);

        for (int j = 0; j < pipelines.size(); j++)
        {
            vector<int> visitedB(num_of_buildings, 0);
            if (pipelines[j]->cost_of_consumption < min_cost && !visitedP[pipelines[j]->id] && (!hasPath(pipelines[j]->end1, pipelines[j]->end2, min_span_adj_list) || pipelines[j]->end1 == pipelines[j]->end2) && (!(hasHeat[pipelines[j]->end1] && hasHeat[pipelines[j]->end2])))
            {
                min_cost = pipelines[j]->cost_of_consumption;
                min_edge = pipelines[j]->id;
            }
        }

        if (min_edge != -1)
        {
            visitedP[min_edge] = 1;
            if(pipelines[min_edge]->end1 == pipelines[min_edge]->end2)
            {
                hasHeat[pipelines[min_edge]->end1] = 1;
            }
            else if(hasHeat[pipelines[min_edge]->end1] || hasHeat[pipelines[min_edge]->end2])
            {
                hasHeat[pipelines[min_edge]->end2] = 1;
                hasHeat[pipelines[min_edge]->end1] = 1;
            }

            min_spanning_tree.push_back(min_edge);

            if(hasHeat[pipelines[min_edge]->end1] || hasHeat[pipelines[min_edge]->end2])
            {
                vector<vector<Edge>> min_span_adj_list = createMinSpanAdjList(pipelines, min_spanning_tree, num_of_buildings);
                for(int a = 0; a < num_of_buildings; a++)
                {
                    if(hasPath(pipelines[min_edge]->end1, a, min_span_adj_list))
                    {
                        hasHeat[a] = 1;
                    }

                    if(hasPath(pipelines[min_edge]->end2, a, min_span_adj_list))
                    {
                        hasHeat[a] = 1;
                    }
                }
            }
        }
    }
    return min_spanning_tree;
}

///////////////////////////////////////////// This part is from solutions, slightly modified to make it more readable /////////////////////////////////////////////

// This tries to find the loop between the nodes <first> and <final> with DFS.
vector<int> findLoopByDFS(int first, int final, vector<vector<int>>& efficient_adj_matrix)
{
    // if there occurs some way connecting first to final, then it means there occurs a lop
    // in that case, do not add the edge between first and final.
    
    vector<int> parents(efficient_adj_matrix.size());
    vector<bool> visited(efficient_adj_matrix.size());

    for (int i = 0; i < efficient_adj_matrix.size(); i++)
    {
        visited[i] = false;
        parents[i] = -1;
    }
    
    stack<int> stack; // holds the nodes to be visited
    stack.push(first);
    
    while(!stack.empty())
    {
        int next = stack.top();
        stack.pop();
        
        if (visited[next]) continue;

        visited[next] = true;
        vector<int> neighbors = efficient_adj_matrix[next];
        
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i] == final)
            { 
                // we found the loop
                // just to satisfy linearity, find the size of the loop

                int path_size = 2;
                int node_ind = next;

                while (node_ind != first)
                {
                    node_ind = parents[node_ind];
                    path_size++;
                }
                
                // now allocate a vector of that much size 
                vector<int> path(path_size);
                path[0] = final;
                path[1] = next;
                int path_ind = 2;
                node_ind = next;

                while (node_ind != first)
                {
                    node_ind = parents[node_ind];
                    path[path_ind++] = node_ind;
                }
                return path;
            }
            
            if (visited[neighbors[i]]) continue;
                
            parents[neighbors[i]] = next;
            stack.push(neighbors[i]);
        }
    }

    // no loop
    vector<int> empty_result;
    return empty_result;
}

vector<int> optimize_plan(vector<Pipeline*> current_solution, Pipeline* new_pipeline)
{
    int num_of_buildings = current_solution.size();    
    if (new_pipeline->end1 == new_pipeline->end2) new_pipeline->end2 = num_of_buildings;  // temporarily make node id num_of_buildings
        
    // Construct adjecency matrix
    vector<vector<int>> efficient_adj_matrix(num_of_buildings+1);
    vector<vector<int>> costs(num_of_buildings+1);  // holds corresponding costs
    
    for (int i = 0; i <= num_of_buildings; i++) 
    {
        vector<int> neighbors;
        efficient_adj_matrix[i] = neighbors;
        vector<int> edge_costs;
        costs[i] = edge_costs;    
    }
    
    // initialize adj and costs matrix
    for (int i = 0; i < current_solution.size(); i++)
    {
        if (current_solution[i]->end1 == current_solution[i]->end2) current_solution[i]->end2 = num_of_buildings;
            
        efficient_adj_matrix[current_solution[i]->end1].push_back(current_solution[i]->end2);
        costs[current_solution[i]->end1].push_back(current_solution[i]->cost_of_consumption);
        
        efficient_adj_matrix[current_solution[i]->end2].push_back(current_solution[i]->end1);
        costs[current_solution[i]->end2].push_back(current_solution[i]->cost_of_consumption);
    }
    
    // initialize the new solution to the old version for now
    vector<int> new_solution(num_of_buildings);
    for (int i = 0;  i < current_solution.size(); i++) new_solution[i] = current_solution[i]->id;
        
    // find the loop
    vector<int> loop = findLoopByDFS(new_pipeline->end1, new_pipeline->end2, efficient_adj_matrix);
    int max_weight_owner = -1;
    int max_weight_of_loop = -1;
    for (int i = 1; i < loop.size(); i++)
    {
        // wee will remove the max-weight-edge from the ring(loop)
        
        int node1_ind = loop[i-1];
        int node2_ind = loop[i];
        int current_cost;

        for (int j = 0; j < efficient_adj_matrix[node1_ind].size(); j++)
        {
            if (efficient_adj_matrix[node1_ind][j] == node2_ind) 
            {
                current_cost = costs[node1_ind][j];
                break;
            }
        }
            
        // detect the maximum-costly edge in the graph
        if (max_weight_of_loop < current_cost)
        {
            max_weight_of_loop = current_cost;
            max_weight_owner = i;
        }
    }
    
    // if the new pipeline has lower weight, then replace with the max-weight-pipeline
    if (new_pipeline->cost_of_consumption < max_weight_of_loop)
    {
        int node1_ind = loop[max_weight_owner-1];
        int node2_ind = loop[max_weight_owner];
        
        //find the edge between node1_ind and node2_ind
        for (int i = 0; i < current_solution.size(); i++)
        {
            if (current_solution[i]->end1 == node1_ind && current_solution[i]->end2 == node2_ind ||
                current_solution[i]->end1 == node2_ind && current_solution[i]->end2 == node1_ind)
            { 
                new_solution[i] = new_pipeline->id;
                break;    
            }
        }
    }
    return new_solution;
}