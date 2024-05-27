#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate modular exponentiation (x^y mod p)
long long int modExp(long long int x, unsigned long long int y, long long int p) {
    long long int result = 1;
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
bool isPrime(long long int n, int k) {
    // Corner cases
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Run Fermat's test k times
    for (int i = 0; i < k; i++) {
        // Pick a random number 'a' in the range [2, n-2]
        long long int a = 2 + rand() % (n - 4);

        // Check if a^(n-1) mod n is not 1, then n is composite
        if (modExp(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

int main() {
    long long int num;
    int k;

    printf("Enter the number to be tested for primality: ");
    scanf("%lld", &num);

    printf("Enter the number of iterations for Fermat test (k): ");
    scanf("%d", &k);

    srand(time(0)); 
    
    if (isPrime(num, k))
        printf("%lld is prime.\n", num);
    else
        printf("%lld is composite.\n", num);

    return 0;
}
