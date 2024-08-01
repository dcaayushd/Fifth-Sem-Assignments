#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Define a struct for a state
struct State {
    string name;
    vector<double> transitionProbabilities;
};

// Function to generate a random number between 0 and 1
double generateRandomNumber() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

// Function to simulate a Markov chain
void simulateMarkovChain(vector<State>& states, int numSteps) {
    int currentStateIndex = 0; // Start at state 0

    for (int i = 0; i < numSteps; ++i) {
        cout << states[currentStateIndex].name << " ";

        double randomValue = generateRandomNumber();
        double cumulativeProbability = 0.0;

        for (int j = 0; j < states[currentStateIndex].transitionProbabilities.size(); ++j) {
            cumulativeProbability += states[currentStateIndex].transitionProbabilities[j];
            if (randomValue <= cumulativeProbability) {
                currentStateIndex = j;
                break;
            }
        }
    }
    cout << endl;
}

int main() {
    // Define states and transition probabilities
    vector<State> states = {
        {"A", {0.3, 0.5, 0.2}},
        {"B", {0.1, 0.7, 0.2}},
        {"C", {0.4, 0.3, 0.3}}
    };

    int numSteps = 10; // Number of steps to simulate

    simulateMarkovChain(states, numSteps);

    return 0;
}
