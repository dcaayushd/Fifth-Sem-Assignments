#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to perform modular exponentiation
int modexp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to generate a random prime number
int generate_prime() {
    int primes[] = { 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
                     151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };
    int size = sizeof(primes) / sizeof(primes[0]);
    return primes[rand() % size];
}

int main() {
    srand(time(NULL));

    // Generate two random prime numbers p and q
    int p = generate_prime();
    int q = generate_prime();
    while (q == p) {
        q = generate_prime();
    }

    // Calculate n = p * q
    int n = p * q;

    // Calculate the totient function phi(n) = (p-1) * (q-1)
    int phi = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    int e;
    do {
        e = rand() % (phi - 2) + 2;
    } while (gcd(e, phi) != 1);

    // Calculate d such that (d * e) % phi(n) = 1
    int d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }

    // Display the public and private keys
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Encrypt a message
    int message;
    printf("Enter a message to encrypt (integer): ");
    scanf("%d", &message);
    int encrypted_message = modexp(message, e, n);
    printf("Encrypted Message: %d\n", encrypted_message);

    // Decrypt the message
    int decrypted_message = modexp(encrypted_message, d, n);
    printf("Decrypted Message: %d\n", decrypted_message);

    return 0;
}
