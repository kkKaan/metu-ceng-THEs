#include "the7.h"

// Implement your solution after this line

// dijkstra shortest path algorithm

void createAdjList(std::vector<Road> roads, std::vector<std::vector<std::pair<int, int>>> &adj) 
{
    for (Road road : roads) 
    {
        adj[road.buildings.first].push_back({road.buildings.second, road.time});
        adj[road.buildings.second].push_back({road.buildings.first, road.time});
    }
}

void dijkstra(int size, std::vector<Road> roads, int start, int dest, std::vector<int> &path, int &cost)
{
    std::vector<std::vector<std::pair<int, int>>> adj(size);
    createAdjList(roads, adj);

    std::vector<int> dist(size, INT_MAX);
    std::vector<int> visited(size, 0);
    std::vector<int> parent(size, -1);
    std::queue<std::pair<int,int>> q;

    q.push({start, 0});
    dist[start] = 0;
    parent[start] = start;

    while (!q.empty())
    {
        std::pair<int,int> u = q.front();
        q.pop();
        visited[u.first] = 1;

        for (auto &v : adj[u.first])
        {
            if (dist[u.first] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u.first] + v.second;
                q.push({v.first, dist[v.first]});
                parent[v.first] = u.first;
            }
        }
    }

    // save path
    int curr = dest;

    std::vector<int> temp;
    while (curr != start)
    {
        temp.push_back(curr);
        curr = parent[curr];
    }
    temp.push_back(start);
    
    // reverse the path
    if(path.size())
    {
        if(path[path.size() - 1] != temp[temp.size() - 1]) path.push_back(temp[temp.size() - 1]);
    }
    else path.push_back(temp[temp.size() - 1]);
    
    for (int i = temp.size() - 2; i >= 0; --i)
    {
        path.push_back(temp[i]);
    }

    cost += dist[dest];
}

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) 
{
    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());

    std::vector<int> path0;
    std::vector<int> finalPath;
    int cost0 = 0;
    int finalCost = 0;

    dijkstra(n, roads, s, d, path0, cost0);

    if(cost0 > l)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    }
    else
    {
        std::cout << "YES ";

        int costX = 0;
        int costY = 0;
        int costXY = 0;
        int costYX = 0;
        int minXY = 0;

        std::vector<int> pathX;
        std::vector<int> pathY;
        std::vector<int> pathXY;
        std::vector<int> pathYX;

        // first go x then go dest
        dijkstra(n, roads, s, x, pathX, costX);
        dijkstra(n, roads, x, d, pathX, costX);

        // first go y then go dest
        dijkstra(n, roads, s, y, pathY, costY);
        dijkstra(n, roads, y, d, pathY, costY);

        // first go x then go y then go dest
        dijkstra(n, roads, s, x, pathXY, costXY);
        dijkstra(n, roads, x, y, pathXY, costXY);
        dijkstra(n, roads, y, d, pathXY, costXY);

        // first go y then go x then go dest
        dijkstra(n, roads, s, y, pathYX, costYX);
        dijkstra(n, roads, y, x, pathYX, costYX);
        dijkstra(n, roads, x, d, pathYX, costYX);

        if(costXY <= l || costYX <= l)
        {
            minXY = std::min(costXY, costYX);
            finalPath = (costXY <= costYX) ? pathXY : pathYX;
            finalCost = minXY;

            std::cout << "BOTH " << finalCost << "MINUTES" << std::endl;
            if(printPath)
            {
                PrintRange(finalPath.begin(), finalPath.end());
                std::cout << std::endl;
            }
        }
        else if(costX <= l || costY <= l)
        {
            minXY = std::min(costX, costY);
            finalCost = minXY;
            if(costX <= costY)
            {
                finalPath = pathX;
                std::cout << "PRINTER " << finalCost << "MINUTES" << std::endl;
            }
            else
            {
                finalPath = pathY;
                std::cout << "DORM " << finalCost << "MINUTES" << std::endl;
            }

            if(printPath)
            {
                PrintRange(finalPath.begin(), finalPath.end());
                std::cout << std::endl;
            }
        }
        else
        {
            finalPath = path0;
            finalCost = cost0;
            std::cout << "DIRECTLY " << finalCost << "MINUTES" << std::endl;
            
            if(printPath)
            {
                PrintRange(finalPath.begin(), finalPath.end());
                std::cout << std::endl;
            }
        }
    }  
}