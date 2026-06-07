#include <iostream>
#include <vector>
#include <queue>
#include <climits>

/* Topic 5: Branch and Bound Method (Job Assignment Problem)
   Strategy: Generates a state space tree and calculates lower bounds of cost at 
   each active node to prune away sub-optimal paths from search consideration.
*/
#define N 4 // 4 Workers, 4 Jobs

struct Node {
    Node* parent;
    int pathCost;
    int boundCost;
    int workerID;
    int jobID;
    bool assignedJobs[N];
};

// Comparator matrix utility to sort the priority queue
struct compareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->boundCost > rhs->boundCost;
    }
};

class BranchAndBoundEngine {
private:
    // Helper function to allocate a new state space tree node
    Node* createNewNode(int worker, int job, const bool assigned[], Node* parent) {
        Node* node = new Node;
        node->parent = parent;
        node->workerID = worker;
        node->jobID = job;
        node->pathCost = 0;
        
        for (int i = 0; i < N; i++) {
            node->assignedJobs[i] = assigned[i];
        }
        if (job != -1) {
            node->assignedJobs[job] = true;
        }
        return node;
    }

    // Calculates the lowest cost bound estimate for a given node path
    int calculateCostBound(int costMatrix[N][N], int worker, const bool assigned[]) {
        int bound = 0;
        bool availableJobs[N];
        for (int i = 0; i < N; i++) availableJobs[i] = !assigned[i];

        // Find the minimum element in unassigned rows
        for (int i = worker + 1; i < N; i++) {
            int minCost = INT_MAX;
            for (int j = 0; j < N; j++) {
                if (availableJobs[j] && costMatrix[i][j] < minCost) {
                    minCost = costMatrix[i][j];
                }
            }
            if (minCost != INT_MAX) bound += minCost;
        }
        return bound;
    }

public:
    int findOptimalAssignment(int costMatrix[N][N]) {
        // Priority queue to store live nodes of search space tree
        std::priority_queue<Node*, std::vector<Node*>, compareNodes> pq;

        bool assigned[N] = {false};
        Node* root = createNewNode(-1, -1, assigned, nullptr);
        root->pathCost = 0;
        root->boundCost = calculateCostBound(costMatrix, -1, assigned);

        pq.push(root);

        while (!pq.empty()) {
            Node* minNode = pq.top();
            pq.pop();

            int nextWorker = minNode->workerID + 1;

            // If all workers are assigned, return total calculated path cost
            if (nextWorker == N) {
                int totalCost = minNode->pathCost;
                // Cleanup logic safely
                delete minNode;
                while(!pq.empty()) { delete pq.top(); pq.pop(); }
                return totalCost;
            }

            // Try all jobs for the current worker
            for (int j = 0; j < N; j++) {
                if (!minNode->assignedJobs[j]) {
                    Node* child = createNewNode(nextWorker, j, minNode->assignedJobs, minNode);
                    child->pathCost = minNode->pathCost + costMatrix[nextWorker][j];
                    child->boundCost = child->pathCost + calculateCostBound(costMatrix, nextWorker, child->assignedJobs);

                    pq.push(child);
                }
            }
        }
        return INT_MAX;
    }
};

int main() {
    BranchAndBoundEngine engine;
    
    // Cost matrix: Rows represent workers, columns represent job processing costs
    int costMatrix[N][N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    std::cout << "--- 5. Branch & Bound Paradigm (Job Assignment) ---\n";
    int minimumCost = engine.findOptimalAssignment(costMatrix);
    std::cout << "Optimal minimized allocation cost bounds match: " << minimumCost << "\n";

    return 0;
}
