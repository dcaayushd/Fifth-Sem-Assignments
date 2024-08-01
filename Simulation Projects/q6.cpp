#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int seed = 1234; // Initial seed
    int num_random_numbers = 10; // Number of random numbers to generate

    cout << "Generated random numbers: ";
    for (int i = 0; i < num_random_numbers; i++) {
        int squared_seed = seed * seed;
        int num_digits = to_string(squared_seed).length();
        int mid_point = num_digits / 2;

        // Handle odd number of digits
        if (num_digits % 2 == 1) {
            mid_point++;
        }

        string squared_seed_str = to_string(squared_seed);
        string mid_part = squared_seed_str.substr(mid_point - 2, 4);

        seed = stoi(mid_part);

        cout << seed << " ";
    }

    cout << endl;

    return 0;
}
