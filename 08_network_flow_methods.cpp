#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

/* Topic 8: Network Flow Methods (Ford-Fulkerson Algorithm)
   Strategy: Incrementally find augmenting paths through a residual graph 
   and bottleneck capacity constraints until no more paths exist from source to sink.
*/
#define VERTICES 6 // Standard 6-node network graph matrix pipeline

class NetworkFlowEngine {
private:
    // Breadth-First Search helper tracking if an augmenting path exists from source to sink
    bool searchAugmentingPath(int residualGraph[VERTICES][VERTICES], int source, int sink, int parentTrack[]) {
        bool visited[VERTICES] = {false};
        std::queue<int> pathQueue;

        pathQueue.push(source);
        visited[source] = true;
        parentTrack[source] = -1;

        while (!pathQueue.empty()) {
            int current = pathQueue.front();
            pathQueue.pop();

            for (int next = 0; next < VERTICES; next++) {
                // If node is unvisited and residual flow capacity remains positive
                if (!visited[next] && residualGraph[current][next] > 0) {
                    if (next == sink) {
                        parentTrack[next] = current;
                        return true; // Path to destination target verified
                    }
                    pathQueue.push(next);
                    parentTrack[next] = current;
                    visited[next] = true;
                }
            }
        }
        return false;
    }

public:
    int calculateMaxFlow(int capacityGraph[VERTICES][VERTICES], int source, int sink) {
        int u, v;
        int residualGraph[VERTICES][VERTICES];

        // Initialize residual graph with the original capacity layout metrics
        for (u = 0; u < VERTICES; u++) {
            for (v = 0; v < VERTICES; v++) {
                residualGraph[u][v] = capacityGraph[u][v];
            }
        }

        int parentTrack[VERTICES];
        int maxFlowAccumulator = 0;

        // Augment the flow as long as a pathway pipeline exists from source to sink
        while (searchAugmentingPath(residualGraph, source, sink, parentTrack)) {
            int pathBottleneckCapacity = INT_MAX;
            
            // Step 1: Track back path to extract the absolute maximum bottleneck value
            for (v = sink; v != source; v = parentTrack[v]) {
                u = parentTrack[v];
                pathBottleneckCapacity = std::min(pathBottleneckCapacity, residualGraph[u][v]);
            }

            // Step 2: Update residual capacities of the forward and reverse edges
            for (v = sink; v != source; v = parentTrack[v]) {
                u = parentTrack[v];
                residualGraph[u][v] -= pathBottleneckCapacity;
                residualGraph[v][u] += pathBottleneckCapacity;
            }

            maxFlowAccumulator += pathBottleneckCapacity;
        }

        return maxFlowAccumulator;
    }
};

int main() {
    NetworkFlowEngine engine;
    
    // Adjacency matrix configuration representing capacity pathways between 6 nodes
    int capacityGraph[VERTICES][VERTICES] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    std::cout << "--- 8. Network Flow Systems (Ford-Fulkerson Optimization) ---\n";
    int totalMaxFlow = engine.calculateMaxFlow(capacityGraph, 0, 5); // From node 0 to node 5
    std::cout << "Maximum calculated capacity pipeline throughput flow matches: " << totalMaxFlow << "\n";

    return 0;
}
