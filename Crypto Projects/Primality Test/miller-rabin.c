#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

// Miller-Rabin primality test function
bool millerRabinTest(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = modExp(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    return false;
}

// Main function to check if a number is prime using Miller-Rabin test
bool isPrime(long long n, int k) {
    // Corner cases
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++) {
        if (!millerRabinTest(d, n))
            return false;
    }
    return true;
}

int main() {
    long long num;
    int k;

    printf("Enter the number to be tested for primality: ");
    scanf("%lld", &num);

    printf("Enter the number of iterations for Miller-Rabin test (k): ");
    scanf("%d", &k);

    srand(time(NULL)); // Seed for random number generation

    if (isPrime(num, k))
        printf("%lld is prime.\n", num);
    else
        printf("%lld is composite.\n", num);

    return 0;
}
