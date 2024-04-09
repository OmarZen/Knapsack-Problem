// C++ implementation to print all
// the possible solutions of the
// Knapsack problem
// About the problem:
// The knapsack problem is a very well-known optimization problem.
// Given a knapsack that can carry weights up to a certain amount, and a number of items; each item has a weight and a value, we want to select the items to carry in the knapsack in order to maximize the total value.
// What you are required to do:
// Write a genetic algorithm to solve the knapsack problem.
//A solved example is provided in lab 1: and this the example:
//( Exercise:
//How can we use the GA to solve the “Knapsack Problem”?
//Given:
//- A knapsack that can carry weights up to W
//- N items; each item (xi) has a weight (wi) and a value (vi)
//Objective:
//- Select the items to carry in the knapsack in order to maximize the total value.
//(max. ∑N xi . vi)
//i=1
//Constraints:
//- The selected items must fit inside the knapsack.
//- The entire item is either selected or not.
//(∑N xi . wi <= W and xi = 0 or 1)
//i=1
//Sol.:
//We can represent a solution (the items selected) as a chromosome containing N bits; each
//        bit (i) corresponds to item (i) where 1 means that the item is selected and 0 means that it
//        is not selected.
//Assume W = 10, N = 5 and we are given a list of pairs containing each items weight and
//value: [(5,4), (4,4), (2,1), (2,7), (4,6)]
//Step 1: Let’s say we started with following randomly initialized chromosomes:
//Note: To make sure your mapping works, you can easily decode these genotypes into
//phenotypes. For example:
//C1: C1[0]=0 -> item 1 is not selected, C1[1]=1 -> item 2 is selected, C1[2]=1 -> item 3 is
//        selected, C1[3]=0 -> item 4 is not selected and C1[4]=1 -> item 5 is selected.
//Step 2: Let’s evaluate the fitness of each chromosome using the objective function:
//Step 3: Let’s select the parents! First, we need to calculate the cumulative fitness function:
//Note: Another option is to normalize the fitness first by dividing it over the total fitness
//        sum to make itrange between 0 and 1 (representing the probability of selection) and then
//        calculate the cumulative probabilities.
//Second, generate a random number (r1) between 0 and 24:
//If 0 <= r < 11, choose C1
//        If 11 <= r < 19, choose C2
//        If 19 <= r < 20, choose C3
//        If 20 <= r < 24, choose C4
//        Assume r1 = 2.32, therefore C1 is the first parent selected. Generate a random number (r2)
//between 0 and 24 and assume r2 = 16, so select C2 as the second parent.
//Step 4: Let’s perform crossover between C1 and C2:
//First, generate a random integer (Xc) between 1 and len(C)-1 to be the crossover point.
//Second, generate a random number (rc) between 0 and 1:
//If rc <= Pc, perform crossover at Xc.
//If rc > Pc, no crossover. (O1 = C1 and O2 = C2)
//Assume Xc= 2, rc = 0.5 and Pc= 0.6, so this means that we will perform crossover as follows:
//Step 5: Let’s perform mutation on the offspring:
//Iterate over each bit in each offspring chromosome and:
//▪ Generate a random number (r) between 0 and 1.
//▪ If r <= Pm, flip that bit.
//Question: What will happen if we never performed mutation?
//Step 6: Replace the current generation with the new offspring using any of the
//replacement strategies explained earlier, go to step 2 and repeat the process
//)
// What the input looks like:
//    You’ll be given an input file with the following format:
//    • First line: Number of test cases (must be at least 1)
//    For each test case:
//    • Size of the knapsack
//    • Number of items
//    For each item:
//    • Weight and value separated by space
// Example:
// 2
// 10
// 3
// 4 4
// 6 6
// 5 3
// 15
// 5
// 12 4
// 1 2
// 4 10
// 1 1
// 2 2
// Important remarks to help you solve the problem:
//    1. Use a binary, one-dimensional chromosome.
//    2. The population size and initialization method you use are up to you.
//    You can actually try different population sizes to see how this will affect your results.
//    The maximum number of generations is also up to you.
//    3. Think about how you will handle infeasible solutions.
//    Infeasible solutions are solutions that violate the constraints of the problem; therefore, they are not allowed.
//    4. Use rank selection and one-point crossover.
//    Choose the methods of mutation and replacement that you find appropriate.
//    5. The output should consist of the test case index, the number of selected items, the total value, the total weight and the weight and value of each selected item.

#include <bits/stdc++.h>
using namespace std;

void knapsack(int knapSize, vector<int> wt, vector<int> val, int itnum) {
    int dp[itnum + 1][knapSize + 1];
    for (int i = 0; i <= itnum; i++) {
        for (int j = 0; j <= knapSize; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (wt[i - 1] <= j) {
                dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int res = dp[itnum][knapSize];
    cout << "Total Value: " << res << endl;
    cout << "Total Weight: " << knapSize - res << endl;
    int w = knapSize;
    for (int i = itnum; i > 0 && res > 0; i--) {
        int numOfSelectedItems = 0;
        if (res == dp[i - 1][w]) {
            continue;
        } else {
            cout << wt[i - 1] << " " << val[i - 1] << endl;
            res = res - val[i - 1];
            w = w - wt[i - 1];
        }
        numOfSelectedItems++;
        cout << numOfSelectedItems << " " << res << " " << w << endl;
    }

}

int main() {
    int testCases;
    cin >> testCases;
    while (testCases--) {
        int knapsackSize;
        cin >> knapsackSize;
        int itemNumber;
        cin >> itemNumber;
        vector<int> weights(itemNumber);
        vector<int> values(itemNumber);
        for (int i = 0; i < itemNumber; i++) {
            cin >> weights[i] >> values[i];
        }
        int numCases = 1;
        cout << "Test Case: " << numCases << endl;
        numCases++;
        knapsack(knapsackSize, weights, values, itemNumber);
    }

    return 0;
}


