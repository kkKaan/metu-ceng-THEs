
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string>
#include <vector>

// Compile time constants
#define MAX_EDGE_PER_VERTEX 8
#define INVALID_INDEX -1
// Large number can be use to set initial weights.
// Weights of the edges are guaranteed to not exceed this value
#define LARGE_NUMBER 0x7FFFFFFF

struct GraphVertex
{
    int             edgeIds[MAX_EDGE_PER_VERTEX];   // Adjacency List
    int             edgeCount;                      // Current edge count
    std::string     name;                           // Name of the vertex
};

struct GraphEdge
{
    int     weight;     // Weight of the edge (used on shortest path)
    bool    masked;     // Whether this edge is masked or not
    int     vertexId0;  // Information about which two vertices this edge
    int     vertexId1;  // connects.
};

// Simple string pair that is used on some functions in the graph
struct StringPair
{
    std::string s0;
    std::string s1;

    StringPair(const std::string s0, const std::string s1)
    { this->s0 = s0; this->s1 = s1;}
};

// This struct can be used on priority queue
struct DistanceVertexIdPair
{
    int vId;
    int currentWeight;

    // Constructor
    DistanceVertexIdPair(int vId, int currentWeight)
    {
        this->vId = vId;
        this->currentWeight = currentWeight;
    }

    // This is implemented for "priority_queue"
    // priority queue uses this to determine which pair is "smaller"
    // than another pair
    bool operator< (const DistanceVertexIdPair& p) const
    {
        // This is not a bug
        // "std::priority_queue" is a MAX heap (by default)
        // we need a MIN heap for shortest path algorithm
        // "std::priority_queue" uses operator< for comparison.
        // So we return "greater" value on "operator<"
        //
        // (There is a better way to set this but it is complicated
        //  thus; we invert the operator here.)
        return currentWeight > p.currentWeight;

        // If you are not curious about the correct implementation
        // skip reading this comment
        //
        // "correct" way to use priority_queue is to change its third
        // template parameter from std::less to std::greater
        // which will make the priority_queue to use "operator>".
        //
        // Then define as such:
        // std::priority_queue<..., std::vector<...>, std::greater>> my_pq;
        // second template parameter defines the underlying data structure
        // of the priority_queue.
    }
};


// A Graph implementation using adjacency list per vertex
// Instead of using a linked list we use two "std::vectors"
// and on vertices and edges we hold index (throughout the
// implementation these are called ids) of these arrays.
class Graph
{
    private:
        std::vector<GraphVertex>    vertexList;
        std::vector<GraphEdge>      edgeList;

        // Friend class that will access your private members etc.
        // This will be used for testing. Do not remove/edit these
        // statements.
        friend class                PA3_GRH_TEST_CASE;
        friend class                PA3_MAPS_TEST_CASE;

        int findVertex(const std::string& vertexName) const;
        GraphEdge *checkEdge(GraphVertex *vertex, int fromId, int toId);
        int edgeIndex(int fromId, int toId);

    protected:
    public:
        // Constructors & Destructor
        // Creates an empty graph
                    Graph();

        // Creates a graph from file
        //
        // This is already implemented.
        // Note that it may throw
        // "DuplicateVertexNameException" and/or "TooManyEdgeOnVertexExecption"
        // If the file contains duplicate names or have too many edges on a vertex
                    Graph(const std::string& filePath);

        // Notice that we did not implement the rule of 3.
        // Since the std::vector properly implements (deep copy)
        // on its own copy constructors.. etc.; it is safe to use
        // default implementations of these operator/constructors/destructor

        // ================================================ //
        //                  Insert Methods                  //
        // ================================================ //
        // Insert a vertex to the graph
        // Throws "DuplicateVertexNameException" if two or more same named
        // vertices exists
        void        InsertVertex(const std::string& vertexName);

        // Connect two already available vertices (insert an edge)
        //
        // Returns true if insertion successful
        // Returns false if there is already an edge between two
        // these vertices
        //
        // Throws "VertexNotFoundException" if either named vertex
        // does not exist in the graph
        // Throws "TooManyEdgeOnVertexExecption" if either vertex already
        // has MAX_EDGE_PER_VERTEX amount of edge.
        bool        ConnectVertices(const std::string& fromVertexName,
                                    const std::string& toVertexName,
                                    int weight);

        // ================================================ //
        //                  Shortest Path                   //
        // ================================================ //
        // Finds the shortest path between to node "from" and "to"
        // Returns true if a path exists, and false if a path cannot be found
        // between two such vertices.
        //
        // Returns the chain of vertices in the "orderedVertexIdList" variable
        bool        ShortestPath(std::vector<int>& orderedVertexIdList,
                                 const std::string& from,
                                 const std::string& to) const;
        // Finds the N shortest path between two vertices
        // Notice that it returns vector of vectors
        // each vector elements contains a shortest path.
        // Please refer to the assignment text for the details.
        //
        // Returns the found path count (should be equivalent to orderedVerrtexCount.size())
        int         MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                                       const std::string& from,
                                       const std::string& to,
                                       int numberOfShortestPaths);
        // ================================================ //
        //                 Mask Functions                   //
        // ================================================ //
        // Mask functions mask the particular edge(s) in the graph
        // These edges are not used on the calculations of
        // "PrintAll" and "ShortestPath" algorithms
        //
        // These functions does NOT alter the behavior of any other function
        // (i.e "ConnectVertices" function still return false even if the edge between those
        // two vertices are masked)
        //
        // There is no error when user tries to mask/unmask an already
        // mask/unmasked edge or tries to mask/unmask an unavailable edge
        //
        // Mask/Unmask the edges with the given two vertices
        void            MaskEdges(const std::vector<StringPair>& vertexNames);
        void            UnMaskEdges(const std::vector<StringPair>& vertexNames);
        // Unmask all edges
        void            UnMaskAllEdges();
        // Mask/Unmask ALL the edges coming in/out of a particular vertex
        void            MaskVertexEdges(const std::string& name);
        void            UnMaskVertexEdges(const std::string& name);

        // ================================================ //
        //              Modify Edge Functions               //
        // ================================================ //
        // Modifies the weight of the edge between two vertices
        // Throws "VertexNotFoundException" if vertex names/ids are invalid
        // Fails silently if there are no edge between these two vertices
        void            ModifyEdge(const std::string& vName0,
                                   const std::string& vName1,
                                   float newWeight);
        void            ModifyEdge(int vId0, int vId1,
                                   float newWeight);
        // ================================================ //
        //                 Print Functions                  //
        // ================================================ //
        // Prints the entire graph as vertex list
        // For each vertex it prints its adjacency list
        void            PrintAll() const;
        // Prints the Path in the vector
        // This is a dummy function, it just converts the vertexId to vertex
        // name and puts the edge arrow (and edge weight) between vertices.
        // It does not check if an edge exists between adjacent vertices on the list
        // If no edge exists it prints "-##->" between the vertices
        void            PrintPath(const std::vector<int>& orderedVertexIdList,
                                  bool sameLine = false) const;
        // ================================================ //
        //              Miscellaneous Functions             //
        // ================================================ //
        int             TotalVertexCount() const;
        int             TotalEdgeCount() const;
        // Returns the name of the vertex that is defined by vertexId.
        std::string     VertexName(int vertexId) const;
        // Accumulates the edge weights in between vertices
        // in the vector
        int             TotalWeightInBetween(std::vector<int>& orderedVertexIdList);
};

#endif //__GRAPH_H__