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

// Jacobi symbol calculation
int jacobiSymbol(long long a, long long n) {
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;
    int result = 1;
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            int r = n % 8;
            if (r == 3 || r == 5)
                result = -result;
        }
        long long temp = a;
        a = n;
        n = temp;
        if (a % 4 == 3 && n % 4 == 3)
            result = -result;
        a = a % n;
    }
    if (n == 1)
        return result;
    return 0;
}

// Solovay-Strassen primality test function
bool solovayStrassenTest(long long n, int k) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        int jacobi = jacobiSymbol(a, n);
        long long mod = modExp(a, (n - 1) / 2, n);
        if (jacobi == 0 || mod != jacobi)
            return false;
    }
    return true;
}

int main() {
    long long num;
    int k;

    printf("Enter the number to be tested for primality: ");
    scanf("%lld", &num);

    printf("Enter the number of iterations for Solovay-Strassen test (k): ");
    scanf("%d", &k);

    if (solovayStrassenTest(num, k))
        printf("%lld is prime.\n", num);
    else
        printf("%lld is composite.\n", num);

    return 0;
}
