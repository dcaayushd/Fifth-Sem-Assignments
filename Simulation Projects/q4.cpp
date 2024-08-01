#include <iostream>

using namespace std;

int main() {
    int seed = 1; // Initial seed
    int a = 5; // Multiplier
    int c = 3; // Increment
    int m = 16; // Modulus

    int num_random_numbers = 10; // Number of random numbers to generate

    cout << "Generated random numbers: ";
    for (int i = 0; i < num_random_numbers; i++) {
        seed = (a * seed + c) % m;
        cout << seed << " ";
    }

    cout << endl;

    return 0;
}
