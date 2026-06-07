#include <iostream>
#include <vector>
#include <algorithm>

/* Topic 3: Dynamic Programming Method (0/1 Knapsack)
   Strategy: Break down the problem into overlapping subproblems, solve them once, 
   and store their solutions in a table (memoization/tabulation) to avoid duplicate calculations.
*/
class DynamicProgrammingEngine {
public:
    int solve01Knapsack(int capacity, const std::vector<int>& weights, const std::vector<int>& values, int n) {
        // Create a 2D matrix layout where table[i][w] represents max value for 'i' items and capacity 'w'
        std::vector<std::vector<int>> dpTable(n + 1, std::vector<int>(capacity + 1, 0));

        // Build the table in a bottom-up manner
        for (int i = 1; i <= n; i++) {
            for (int w = 1; w <= capacity; w++) {
                if (weights[i - 1] <= w) {
                    // Maximum of including the item vs excluding the item
                    dpTable[i][w] = std::max(values[i - 1] + dpTable[i - 1][w - weights[i - 1]], dpTable[i - 1][w]);
                } else {
                    // Item cannot fit; exclude it
                    dpTable[i][w] = dpTable[i - 1][w];
                }
            }
        }
        return dpTable[n][capacity]; // Return the optimal choice matrix coordinate
    }
};

int main() {
    DynamicProgrammingEngine engine;
    int capacity = 50;
    std::vector<int> values = {60, 100, 120};
    std::vector<int> weights = {10, 20, 30};
    int n = values.size();

    std::cout << "--- 3. Dynamic Programming Paradigm (0/1 Knapsack) ---\n";
    int optimalValue = engine.solve01Knapsack(capacity, weights, values, n);
    std::cout << "Globally optimal knapsack value matches: " << optimalValue << "\n";

    return 0;
}
