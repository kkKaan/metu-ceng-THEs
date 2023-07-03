#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

int Graph::findVertex(const std::string& vertexName) const
{
    for(int i = 0; i < vertexList.size(); ++i)
    {
        if(vertexList[i].name == vertexName){return i;}
    }
    return -1;
}

GraphEdge *Graph::checkEdge(GraphVertex *vertex, int fromId, int toId)
{
    for(int x = 0; x < MAX_EDGE_PER_VERTEX ; ++x)
    {
        if((vertex->edgeIds)[x] == -1){continue;}

        if( (edgeList[(vertex->edgeIds)[x]].vertexId0 == fromId && edgeList[(vertex->edgeIds)[x]].vertexId1 == toId) || 
            (edgeList[(vertex->edgeIds)[x]].vertexId0 == toId && edgeList[(vertex->edgeIds)[x]].vertexId1 == fromId) ) {return &(edgeList[(vertex->edgeIds)[x]]);}
    }
    return NULL;
}

int Graph::edgeIndex(int fromId, int toId)
{
    GraphVertex v = vertexList[fromId];

    for(int a = 0; a < MAX_EDGE_PER_VERTEX; ++a)
    {
        if((v.edgeIds)[a] == -1){continue;}
        
        if( ( ((edgeList[v.edgeIds[a]].vertexId0 == fromId)) && ((edgeList[v.edgeIds[a]].vertexId1 == toId)) ) || 
            ( ((edgeList[v.edgeIds[a]].vertexId0 == toId)) && ((edgeList[v.edgeIds[a]].vertexId1 == fromId)) ) )
        {
            return v.edgeIds[a];
        }
    }
    return -3;
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // TODO

    GraphVertex v; 
    v.edgeCount = 0;
    v.name = vertexName;
    
    for(int a = 0; a < MAX_EDGE_PER_VERTEX; ++a)
    {
        (v.edgeIds)[a] = -1;
    }

    for(int i = 0; i < vertexList.size(); ++i)
    {
        if(vertexList[i].name == vertexName)
        {
            throw DuplicateVertexNameException();
        }
    }
    vertexList.push_back(v);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    // TODO

    if(fromVertexName == toVertexName){return false;}

    GraphVertex* from = NULL, *to = NULL;
    int fromId, toId;

    for(int i = 0; i < vertexList.size(); ++i)
    {
        if(vertexList[i].name == fromVertexName){from = &(vertexList[i]); fromId = i;}
        else if(vertexList[i].name == toVertexName){to = &(vertexList[i]); toId = i;}
    }

    if(from && to)
    {
        if(from->edgeCount == MAX_EDGE_PER_VERTEX || to->edgeCount == MAX_EDGE_PER_VERTEX){throw TooManyEdgeOnVertexExecption();} 
        if(checkEdge(from, fromId, toId)){return false;}
        
        GraphEdge newEdge = {weight, false, fromId, toId};
        int newEdgeId = edgeList.size();
        edgeList.push_back(newEdge);
        
        from->edgeIds[from->edgeCount] = newEdgeId;
        ++(from->edgeCount);
        
        to->edgeIds[to->edgeCount] = newEdgeId;
        ++(to->edgeCount);
        
        return true;
    }
    throw VertexNotFoundException();
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    // TODO

    int fromId = findVertex(from), toId = findVertex(to);
    if(fromId < 0 || toId < 0){throw VertexNotFoundException();}
    else if(fromId == toId){orderedVertexIdList.push_back(fromId); return true;}

    GraphVertex fromV = vertexList[fromId];
    GraphVertex toV = vertexList[toId];
    
    std::priority_queue<DistanceVertexIdPair> heap;
    std::vector<DistanceVertexIdPair> pairs;
    std::vector<int> parents;
    std::vector<bool> isVisited;

    for(int a = 0; a < vertexList.size(); ++a)
    {
        if(a == fromId){DistanceVertexIdPair p(a, 0); pairs.push_back(p); parents.push_back(-2);}
        else{DistanceVertexIdPair p(a, LARGE_NUMBER); pairs.push_back(p); parents.push_back(-1);} 
        isVisited.push_back(false);
    }

    heap.push(pairs[fromId]);

    while(!heap.empty())
    {
        DistanceVertexIdPair currentP = heap.top();
        heap.pop();
        
        for(int i = 0; i < MAX_EDGE_PER_VERTEX; ++i)
        {
            if((vertexList[currentP.vId]).edgeIds[i] == -1){continue;}
            GraphEdge currentE = edgeList[vertexList[currentP.vId].edgeIds[i]];
            
            if(currentE.masked){continue;}
            else
            {
                if(currentE.vertexId0 == currentP.vId)
                {
                    if(isVisited[currentE.vertexId1]){continue;}
                    else
                    {
                        if(currentP.currentWeight + currentE.weight >= pairs[currentE.vertexId1].currentWeight){continue;}
                        else
                        {
                            pairs[currentE.vertexId1].currentWeight = currentP.currentWeight + currentE.weight;
                            parents[currentE.vertexId1] = currentP.vId;
                            if(currentE.vertexId1 == toId){continue;}
                            else{heap.push(pairs[currentE.vertexId1]);}
                        }
                    } 
                }
                else
                {
                    if(isVisited[currentE.vertexId0]){continue;}
                    else
                    {
                        if(currentP.currentWeight + currentE.weight >= pairs[currentE.vertexId0].currentWeight){continue;}
                        else
                        {
                            pairs[currentE.vertexId0].currentWeight = currentP.currentWeight + currentE.weight;
                            parents[currentE.vertexId0] = currentP.vId;
                            if(currentE.vertexId0 == toId){continue;}
                            else{heap.push(pairs[currentE.vertexId0]);}
                        }
                    }
                }
            }
        }
        isVisited[currentP.vId] = true;
    }

    if(parents[toId] == -1){return false;}
    else
    {
        int index = toId;
        std::vector<int> arr;
        
        while(index != -2)
        {
            arr.push_back(index);
            index = parents[index];
        }
        
        for(int x = arr.size()-1; x>=0; --x)
        {
            orderedVertexIdList.push_back(arr[x]);
        }
        return true;
    }
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
    int fromId = findVertex(from), toId = findVertex(to);
    if(fromId < 0 || toId < 0){throw VertexNotFoundException();}
    else if(fromId == toId){return 0;}

    UnMaskAllEdges();
    std::vector<int> tmpOrdered;

    while(orderedVertexIdList.size() != numberOfShortestPaths)
    {
        ShortestPath(tmpOrdered, from, to);
        if(!(tmpOrdered.size())){break;}
        
        int maxEdgeIndex = -3;
        int currentEdgeIndex = -3;
        
        for(int a = 0; a < tmpOrdered.size() - 1; ++a)
        {
            currentEdgeIndex = edgeIndex(tmpOrdered[a], tmpOrdered[a+1]);
            if(maxEdgeIndex == -3){maxEdgeIndex = currentEdgeIndex;}
            else
            {
                if(edgeList[currentEdgeIndex].weight > edgeList[maxEdgeIndex].weight)
                {
                    maxEdgeIndex = currentEdgeIndex;
                }
            }
        }
        edgeList[maxEdgeIndex].masked = true;
        orderedVertexIdList.push_back(tmpOrdered);
        tmpOrdered.clear();
    }
    UnMaskAllEdges();
    return orderedVertexIdList.size();
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO

    for(int a = 0; a < vertexNames.size(); ++a)
    {
        int id0 = findVertex(vertexNames[a].s0);
        int id1 = findVertex(vertexNames[a].s1);
        
        if(id0 < 0 || id1 < 0){throw VertexNotFoundException();}
        
        GraphVertex *v0 = &(vertexList[id0]);
        if(checkEdge(v0, id0, id1)){checkEdge(v0, id0, id1)->masked = true;}
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO

    for(int a = 0; a < vertexNames.size(); ++a)
    {
        int id0 = findVertex(vertexNames[a].s0);
        int id1 = findVertex(vertexNames[a].s1);
        
        if(id0 < 0 || id1 < 0){throw VertexNotFoundException();}
        
        GraphVertex *v0 = &(vertexList[id0]);
        if(checkEdge(v0, id0, id1)){checkEdge(v0, id0, id1)->masked = false;}
    }
}

void Graph::UnMaskAllEdges()
{
    // TODO

    for(int a = 0; a < edgeList.size(); ++a)
    {
        (edgeList[a]).masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO

    int k = findVertex(name);

    if(k < 0){throw VertexNotFoundException();}
    else
    {
        for(int a = 0; a < vertexList[k].edgeCount; ++a)
        {
            edgeList[(vertexList[k]).edgeIds[a]].masked = true;
        }
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO

    int k = findVertex(name);

    if(k < 0){throw VertexNotFoundException();}
    else
    {
        for(int a = 0; a < vertexList[k].edgeCount; ++a)
        {
            edgeList[(vertexList[k]).edgeIds[a]].masked = false;
        }
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    // TODO

    GraphVertex *from = NULL, *to = NULL;
    int fromId, toId;

    for(int i = 0; i < vertexList.size(); ++i)
    {
        if(vertexList[i].name == vName0){from = &(vertexList[i]); fromId = i;}
        else if(vertexList[i].name == vName1){to = &(vertexList[i]); toId = i;}
    }

    if(from && to)
    {
        if(checkEdge(from, fromId, toId)){checkEdge(from, fromId, toId)->weight = newWeight;}
    }
    else{throw VertexNotFoundException();}
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    // TODO

    if(vId0 < 0 || vId0 >= vertexList.size() || vId1 < 0 || vId1 >= vertexList.size()){return;}
    else
    {
        if(checkEdge(&(vertexList[vId0]), vId0, vId1)){checkEdge(&(vertexList[vId0]), vId0, vId1)->weight = newWeight;}
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const 
{
    // TODO
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    // TODO
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO

    if(vertexId >= vertexList.size() || vertexId < 0){return "";}
    return (vertexList[vertexId]).name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO

    if(!(orderedVertexIdList.size())){return -1;}
    
    int sum = 0;
    for(int a = 0; a < orderedVertexIdList.size() -1; ++a)
    {
        int edgeId = edgeIndex(orderedVertexIdList[a], orderedVertexIdList[a+1]);
        sum += edgeList[edgeId].weight;
    }
    return sum;
}