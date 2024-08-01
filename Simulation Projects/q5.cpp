#include <iostream>

using namespace std;

int main() {
    int seed = 1234; // Initial seed
    int multiplier = 7; // Multiplier
    int modulus = 8; // Modulus

    int num_random_numbers = 10; // Number of random numbers to generate

    cout << "Generated random numbers: ";
    for (int i = 0; i < num_random_numbers; i++) {
        seed = (multiplier * seed) % modulus;
        cout << seed << " ";
    }

    cout << endl;

    return 0;
}
