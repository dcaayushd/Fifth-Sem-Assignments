#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}

// Function to calculate modular exponentiation (x^y mod p)
int modExp(int x, unsigned int y, int p) {
    int result = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            result = (result * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return result;
}

// Function to find primitive root of a prime number
int findPrimitiveRoot(int p) {
    int phi = p - 1;
    for (int r = 2; r < p; r++) {
        int flag = 0;
        for (int i = 2; i * i <= phi; i++) {
            if (phi % i == 0) {
                if (modExp(r, phi / i, p) == 1) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
            return r;
    }
    return -1;
}

// Function to perform ElGamal encryption
void elgamalEncrypt(int msg, int p, int g, int y, int *c1, int *c2) {
    int k = rand() % (p - 2) + 1; // Generate random integer k, 1 <= k <= p-2
    *c1 = modExp(g, k, p);
    *c2 = (msg * modExp(y, k, p)) % p;
}

// Function to perform ElGamal decryption
int elgamalDecrypt(int c1, int c2, int p, int x) {
    int m = (c2 * modExp(c1, p - 1 - x, p)) % p;
    return m;
}

int main() {
    int p, g, x, y, m, c1, c2;

    printf("Enter prime number (p): ");
    scanf("%d", &p);
    if (!isPrime(p)) {
        printf("%d is not a prime number.\n", p);
        return 1;
    }

    g = findPrimitiveRoot(p);
    if (g == -1) {
        printf("Primitive root does not exist for %d.\n", p);
        return 1;
    }

    printf("Enter private key (x): ");
    scanf("%d", &x);
    if (x <= 1 || x >= p - 1) {
        printf("Private key must be between 1 and %d.\n", p - 2);
        return 1;
    }

    y = modExp(g, x, p);

    printf("Public Key (p, g, y): (%d, %d, %d)\n", p, g, y);

    printf("Enter message to encrypt (m): ");
    scanf("%d", &m);

    elgamalEncrypt(m, p, g, y, &c1, &c2);
    printf("Encrypted message (c1, c2): (%d, %d)\n", c1, c2);

    int decryptedMessage = elgamalDecrypt(c1, c2, p, x);
    printf("Decrypted message: %d\n", decryptedMessage);

    return 0;
}
