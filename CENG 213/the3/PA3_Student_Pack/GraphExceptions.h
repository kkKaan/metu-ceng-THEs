#ifndef __GRAPH_EXCEPTIONS_H__
#define __GRAPH_EXCEPTIONS_H__

#include <stdexcept>

// Exception Implementations
//  DO NOT TOUCH THIS FILE
struct DuplicateVertexNameException : public std::runtime_error
{
    // Constructor
    DuplicateVertexNameException()
        : std::runtime_error("Duplicate vertex name on graph")
    {}
};

struct VertexNotFoundException : public std::runtime_error
{
    // Constructor
    VertexNotFoundException()
        : std::runtime_error("Vertex Not Found")
    {}
};

struct TooManyEdgeOnVertexExecption : public std::runtime_error
{
    // Constructor
    TooManyEdgeOnVertexExecption()
        : std::runtime_error("Edge count on vertex exceeds the maximum limit")
    {}
};

#endif // __GRAPH_EXCEPTIONS_H__