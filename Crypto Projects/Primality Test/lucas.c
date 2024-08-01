#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Modular exponentiation function (x^y mod p)
uint64_t modExp(uint64_t x, uint64_t y, uint64_t p) {
    uint64_t result = 1;
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
int jacobiSymbol(int64_t a, int64_t n) {
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
        int64_t temp = a;
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

// Lucas primality test function
bool lucasTest(uint64_t n) {
    if (n == 2)
        return true;
    if (n < 2 || n % 2 == 0)
        return false;

    int64_t d = 5;
    int64_t dd = 4;
    while (true) {
        int jacobi = jacobiSymbol(d, n);
        if (jacobi == 0)
            return false;
        int64_t mod = modExp(d, (n - 1) / 2, n);
        if (jacobi != 1 && mod != jacobi)
            return false;

        if (dd >= n)
            break;
        d = d + dd;
        dd = dd + 2;
    }
    return true;
}

int main() {
    uint64_t num;

    printf("Enter the number to be tested for primality: ");
    scanf("%lu", &num);

    if (lucasTest(num))
        printf("%lu is prime.\n", num);
    else
        printf("%lu is composite.\n", num);

    return 0;
}
