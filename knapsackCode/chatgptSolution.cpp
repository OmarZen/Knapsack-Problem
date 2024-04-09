#include <iostream>
#include <vector>

// Structure to represent items
struct Item {
    int weight;
    int value;
};

// Function to solve the knapsack problem using dynamic programming
int knapsackDP(int knapsackSize, const std::vector<Item>& items) {
    int numItems = items.size();
    std::vector<std::vector<int>> dp(numItems + 1, std::vector<int>(knapsackSize + 1, 0));

    for (int i = 1; i <= numItems; ++i) {
        for (int w = 0; w <= knapsackSize; ++w) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }

    return dp[numItems][knapsackSize];
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;

    for (int test = 1; test <= numTestCases; ++test) {
        int knapsackSize, numItems;
        std::cin >> knapsackSize >> numItems;

        std::vector<Item> items(numItems);
        for (int i = 0; i < numItems; ++i) {
            std::cin >> items[i].weight >> items[i].value;
        }

        int maxTotalValue = knapsackDP(knapsackSize, items);

        // Output the results
        std::cout << "Test Case " << test << ":\n";
        std::cout << "Number of selected items: " << numItems << "\n";
        std::cout << "Total value: " << maxTotalValue << "\n";
        std::cout << "Total weight: " << knapsackSize << "\n";
        std::cout << "Selected items:\n";
        for (int i = 0; i < numItems; ++i) {
            std::cout << "Weight: " << items[i].weight << ", Value: " << items[i].value << "\n";
        }
    }

    return 0;
}
