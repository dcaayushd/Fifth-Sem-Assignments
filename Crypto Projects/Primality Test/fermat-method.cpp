#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to calculate modular exponentiation (x^y mod p)
long long modExp(long long x, unsigned long long y, long long p) {
    long long result = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            result = (result * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return result;
}

// Fermat primality test function
bool isPrime(long long n, int k) {
    // Corner cases
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Run Fermat's test k times
    for (int i = 0; i < k; i++) {
        // Pick a random number 'a' in the range [2, n-2]
        long long a = 2 + rand() % (n - 4);

        // Check if a^(n-1) mod n is not 1, then n is composite
        if (modExp(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

int main() {
    long long num;
    int k;

    std::cout << "Enter the number to be tested for primality: ";
    std::cin >> num;

    std::cout << "Enter the number of iterations for Fermat test (k): ";
    std::cin >> k;

    srand(time(0)); // Seed for random number generation

    if (isPrime(num, k))
        std::cout << num << " is prime." << std::endl;
    else
        std::cout << num << " is composite." << std::endl;

    return 0;
}
