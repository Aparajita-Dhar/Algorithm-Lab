#include <iostream>
#include <vector>
#include <algorithm>

/* Topic 2: Greedy Method (Fractional Knapsack Problem)
   Strategy: Make the locally optimal choice at each stage with the hope of finding a globally optimal solution.
*/
struct Item {
    int value;
    int weight;
};

class GreedyOptimizer {
private:
    // Comparator function to sort items by their value per unit weight ratio
    static bool compareItems(Item a, Item b) {
        double ratioA = (double)a.value / a.weight;
        double ratioB = (double)b.value / b.weight;
        return ratioA > ratioB;
    }

public:
    double getMaximumProfit(int capacity, std::vector<Item>& items) {
        // Sort items by value/weight ratio in descending order
        std::sort(items.begin(), items.end(), compareItems);

        double totalProfit = 0.0;
        int currentWeight = 0;

        for (const auto& item : items) {
            // If adding the whole item doesn't exceed capacity, take it entirely
            if (currentWeight + item.weight <= capacity) {
                currentWeight += item.weight;
                totalProfit += item.value;
            } else {
                // Take the fractional component of the remaining capacity
                int remainingCapacity = capacity - currentWeight;
                totalProfit += item.value * ((double)remainingCapacity / item.weight);
                break; // Knapsack is completely full
            }
        }
        return totalProfit;
    }
};

int main() {
    GreedyOptimizer optimizer;
    int knapsackCapacity = 50;
    std::vector<Item> inventory = {{60, 10}, {100, 20}, {120, 30}};

    std::cout << "--- 2. Greedy Paradigm (Fractional Knapsack) ---\n";
    double maxProfit = optimizer.getMaximumProfit(knapsackCapacity, inventory);
    std::cout << "Maximum achievable profit for capacity " << knapsackCapacity << " is: $" << maxProfit << "\n";

    return 0;
}
