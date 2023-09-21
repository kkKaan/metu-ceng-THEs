# Graph and HashTable Implementations, Maps Application

This repository contains C++ implementations of a Graph class, a HashTable class and an application using these classes.

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

## METUMaps Implementation (METUMaps.cpp)

The `METUMaps` class is designed for journey planning. It provides functionality to plan and manage journeys between locations on the map. Key features of the implementation include:

- **Journey Management**: You can start a journey, set a starting location, set a destination, and update your location during the journey.

- **Caching Routes**: The class caches routes for faster access when calculating routes between locations.

- **Error Handling**: It includes error handling for cases like attempting to change destinations during a journey or starting a journey without valid locations.

- **Display Information**: The class provides information about the current journey, including the current location and estimated time left.

Explore the source code files (`Graph.cpp`, `HashTable.cpp`, and `METUMaps.cpp`) for detailed information about each class and its methods.

For usage examples and more details, refer to the source code.

If you have any questions or need further assistance, feel free to reach out.
