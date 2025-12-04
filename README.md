# Dinic's Maximum Flow Algorithm

A C++ implementation of Dinic's algorithm for computing maximum flow in a flow network, solving the max-flow/min-cut problem efficiently.

## Overview

This project implements Dinic's algorithm, which finds the maximum flow from a source vertex to a sink vertex in a directed weighted graph (flow network). The algorithm uses BFS to construct level graphs and DFS to find blocking flows, achieving better time complexity than Ford-Fulkerson for many practical cases.

## Algorithm Description

**Dinic's Algorithm** operates in phases:
1. **BFS Phase**: Build a level graph showing shortest distances from source
2. **DFS Phase**: Find blocking flows along paths in the level graph
3. **Repeat**: Continue until no augmenting path exists

**Time Complexity**: O(V² × E) where V is vertices and E is edges

## Features

- **Maximum Flow Computation**: Find maximum flow from source to sink
- **Residual Graph Management**: Automatically maintains forward and backward edges
- **Level Graph Construction**: BFS-based layered network for efficient path finding
- **Blocking Flow**: DFS-based augmentation with bottleneck detection
- **Edge Cases Handled**: Disconnected graphs, zero capacity, source equals sink

## Applications

Dinic's algorithm solves:
- **Maximum Flow Problems**: Network capacity optimization
- **Bipartite Matching**: Maximum matching in bipartite graphs
- **Min-Cut Problems**: Network reliability and connectivity
- **Network Design**: Resource allocation and routing

## Usage Example
```cpp
#include "dinic.hpp"
#include <vector>

using namespace std;

// Helper function to add directed edge
void addEdge(vector<vector<int>>& graph, int u, int v, int capacity) {
    graph[u][v] = capacity;
}

int main() {
    int vertices = 6;
    
    // Create adjacency matrix (capacity matrix)
    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
    
    // Add edges (from, to, capacity)
    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 2, 13);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 1, 4);
    addEdge(graph, 2, 4, 14);
    addEdge(graph, 3, 2, 9);
    addEdge(graph, 3, 5, 20);
    addEdge(graph, 4, 3, 7);
    addEdge(graph, 4, 5, 4);
    
    int source = 0;
    int sink = 5;
    
    // Compute maximum flow
    int maxFlow = dinic_algorithm(vertices, graph, source, sink);
    
    cout << "Maximum flow: " << maxFlow << endl;  // Output: 23
    
    return 0;
}
```

## Graph Representation

Uses **adjacency matrix** representation:
- `graph[u][v]` = capacity of edge from vertex u to vertex v
- `graph[u][v] = 0` means no edge exists
- Matrix size: V × V where V is number of vertices

## Implementation Details

### Core Functions

**`dinic_algorithm(vertices, graph, source, sink)`**
- Main function computing maximum flow
- Returns integer representing maximum flow value

**`bfs(vertices, level, graph, source, sink)`**
- Constructs level graph using breadth-first search
- Returns true if sink is reachable from source
- Updates level array with distances from source

**`dfs(vertices, level, residualGraph, current, sink, flow)`**
- Finds blocking flow using depth-first search
- Augments flow along valid paths in level graph
- Updates residual capacities (forward/backward edges)
- Returns bottleneck flow value

### Key Concepts

**Level Graph**: Assigns levels to vertices based on shortest distance from source
**Blocking Flow**: Maximum flow that can be pushed in current level graph
**Residual Graph**: Maintains remaining capacities after flow augmentation

## Test Coverage

Comprehensive test suite includes:

**Basic Tests**:
- Small graphs with known solutions
- Various source/sink configurations

**Edge Cases**:
- Source equals sink (flow = 0)
- Disconnected graphs (no path)
- Single edge graphs
- Zero capacity edges
- Self-loops (ignored)

**Advanced Tests**:
- Multiple phases with back edges
- Bipartite matching problems
- Residual edge utilization
- Min-cut property verification
- Parallel edges (summed capacity)
- Large capacity values (near INT_MAX)

## Requirements

- C++11 or later
- Google Test framework for running tests
- Standard library: `<vector>`, `<queue>`, `<climits>`

## Limitations

- Uses adjacency matrix: O(V²) space complexity
- Best for dense graphs; adjacency list better for sparse graphs
- Integer capacities only (can be extended to floating point)

## Performance Notes

- Efficient for unit capacity networks: O(E × √V)
- Well-suited for bipartite matching problems
- Multiple phases handle complex flow redistribution
- Better than Ford-Fulkerson on dense networks

