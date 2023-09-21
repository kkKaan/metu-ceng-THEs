# Graph and HashTable Implementations, Maps Application

This repository contains C++ implementations of a Graph class and a HashTable class.

## Graph Implementation (Graph.cpp)

The `Graph` class represents a graph data structure. Key features of the implementation include:

- **Vertex Management**: You can create vertices using `InsertVertex` and connect them with edges using `ConnectVertices`.

- **Shortest Path**: The class provides a method `ShortestPath` to find the shortest path between two vertices.

- **Edge Management**: You can modify edges' weights using `ModifyEdge` and mask/unmask edges using `MaskEdges`, `UnMaskEdges`, `MaskVertexEdges`, and `UnMaskVertexEdges`.

- **Graph Information**: You can retrieve information about the graph, such as the total vertex and edge count.

## HashTable Implementation (HashTable.cpp)

The `KeyedHashTable` class is a generic hash table implementation that maps keys to arrays of integers. Key features of the implementation include:

- **Hashing**: The `Hash` method calculates a hash value for keys.

- **Dynamic Sizing**: The table dynamically resizes when it reaches a threshold.

- **Data Management**: You can insert data using `Insert`, find data using `Find`, remove data using `Remove`, and clear the table using `ClearTable`.

- **Printing**: The `Print` method displays the contents of the hash table.

Explore the source code for detailed information about each class and its methods.

For usage examples and more details, refer to the source code files `Graph.cpp` and `HashTable.cpp`.

If you have any questions or need further assistance, feel free to reach out.
