// Omar Waleed Zenhom               ID: 20206130
// Mohamed Alaa El-Deen Mohammed    ID: 20206068

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Maximum number of generations
const int MAX_GENERATIONS = 100;
// Maximum number of population size
const int POPULATION_SIZE = 100;// recommended N= 50
// Mutation rate
const double MUTATION_RATE = 0.05;// ratio recommended in the lectures M=0.05, C=0.9

// Item structure
struct Item
{
    int weight;
    int value;
};

// Chromosome structure
struct Chromosome
{
    vector<int> Genes;
    int totalValue;
    int totalWeight;
};

// Operator overload to compare chromosomes for sorting
bool operator<(const Chromosome& a, const Chromosome& b) {
    return a.totalValue > b.totalValue;
}

// Initialize the population of chromosomes with random genes
void initializePopulation(std::vector<Chromosome>& population, int knapsackSize, int numItems)
{
    population.clear();// Clear the population
    for (int i = 0; i < POPULATION_SIZE; i++) {
        Chromosome chromosome;
        chromosome.Genes.resize(numItems);// updating the size of the gene
        for (int j = 0; j < numItems ; j++)
        {
            chromosome.Genes[j] = (rand() % 2 == 1) ;// Randomly assign genes
        }
        population.push_back(chromosome);// Add the chromosome to the population
    }
}

// Evaluate the fitness of a chromosome based on the selected items
int evaluateFitness(Chromosome& chromosome, const std::vector<Item>& items, int knapsackSize) {
    chromosome.totalValue = 0;
    chromosome.totalWeight = 0;

    // Calculate the total weight and value of the selected items
    for (int i = 0; i < chromosome.Genes.size(); i++) {
        if (chromosome.Genes[i]) {
            chromosome.totalWeight += items[i].weight;
            chromosome.totalValue += items[i].value;
        }
    }

    // If the total weight exceeds the knapsack size, set the total value to 0
    if (chromosome.totalWeight > knapsackSize) {
        chromosome.totalValue = 0;
    }

    return chromosome.totalValue;
}

// Perform crossover between two parent chromosomes
void crossover(Chromosome& parent1, Chromosome& parent2) {
    int crossoverPoint = rand() % parent1.Genes.size();
    for (int i = crossoverPoint; i < parent1.Genes.size(); i++) {
        swap(parent1.Genes[i], parent2.Genes[i]);
    }
}

// Mutate the genes in a chromosome with a certain mutation rate
void mutate(Chromosome& chromosome) {
    for (int i = 0; i < chromosome.Genes.size(); i++) {
        if ((rand() / static_cast<double>(RAND_MAX)) < MUTATION_RATE)
        {
            if(chromosome.Genes[i]==1)
                chromosome.Genes[i]=0;
            else if (chromosome.Genes[i]==0)
                chromosome.Genes[i]=1;
        }
    }
}

// Perform rank-based selection by sorting the population based on fitness
void rankSelection(std::vector<Chromosome>& population)
{
    sort(population.begin(), population.end());
}

int main() {
    // Seed the random number generator that uses the current time to generate random numbers
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Please enter the number of test Cases followed by knapsack size"<<"\n"
              <<"followed by number of items then enter the items itself : "<< "\n";


    int numTestCases;
    cin >> numTestCases;

    for (int testCase = 1; testCase <= numTestCases; testCase++) {
        int knapsackSize;
        int numItems;
        cin >> knapsackSize >> numItems;

        std::vector<Item> items(numItems);
        for (int i = 0; i < numItems; i++) {
            cin >> items[i].weight >> items[i].value;
        }

        vector<Chromosome> population;
        initializePopulation(population, knapsackSize, numItems);// Initialize the population

        for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
            for (Chromosome& chromosome : population) {
                evaluateFitness(chromosome, items, knapsackSize);
            }

            rankSelection(population);

            vector<Chromosome> newPopulation;
            for (int i = 0; i < POPULATION_SIZE; i += 2) {
                Chromosome parent1 = population[i];
                Chromosome parent2 = population[i + 1];
                crossover(parent1, parent2);
                mutate(parent1);
                mutate(parent2);
                newPopulation.push_back(parent1);
                newPopulation.push_back(parent2);
            }

            population = newPopulation;// Update the population with the new generation
        }

        // Output the final result for the test case.
        int T_Values=0 ;
        int T_Weight=0 ;
        Chromosome bestSolution = population.front();
        for (int i = 0; i < numItems; i++) {
            if (bestSolution.Genes[i]) {
                T_Values+=items[i].value;
                T_Weight+=items[i].weight;
            }
        }

        cout << "Test Case " << testCase << ":\n";
        cout << "Number of selected items: " << std::count(bestSolution.Genes.begin(), bestSolution.Genes.end(), true) << "\n";
        cout << "Total value: " << T_Values << "\n";
        cout << "Total weight: " << T_Weight << "\n";
        cout << "Selected items (weight, value):\n";
        for (int i = 0; i < numItems; i++) {
            if (bestSolution.Genes[i]) {
                cout << items[i].weight << " " << items[i].value << "\n";
            }
        }
    }

    return 0;
}

