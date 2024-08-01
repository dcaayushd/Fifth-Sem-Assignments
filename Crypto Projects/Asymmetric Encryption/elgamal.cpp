#include <iostream>
#include <cmath>
#include <vector>

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    return true;
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
        bool flag = true;
        for (int i = 2; i * i <= phi; i++) {
            if (phi % i == 0) {
                if (modExp(r, phi / i, p) == 1) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag)
            return r;
    }
    return -1;
}

// Function to perform ElGamal encryption
void elgamalEncrypt(int msg, int p, int g, int y, int& c1, int& c2) {
    int k = rand() % (p - 2) + 1; // Generate random integer k, 1 <= k <= p-2
    c1 = modExp(g, k, p);
    c2 = (msg * modExp(y, k, p)) % p;
}

// Function to perform ElGamal decryption
int elgamalDecrypt(int c1, int c2, int p, int x) {
    int m = (c2 * modExp(c1, p - 1 - x, p)) % p;
    return m;
}

int main() {
    int p, g, x, y, m, c1, c2;

    std::cout << "Enter prime number (p): ";
    std::cin >> p;
    if (!isPrime(p)) {
        std::cout << p << " is not a prime number." << std::endl;
        return 1;
    }

    g = findPrimitiveRoot(p);
    if (g == -1) {
        std::cout << "Primitive root does not exist for " << p << "." << std::endl;
        return 1;
    }

    std::cout << "Enter private key (x): ";
    std::cin >> x;
    if (x <= 1 || x >= p - 1) {
        std::cout << "Private key must be between 1 and " << p - 2 << "." << std::endl;
        return 1;
    }

    y = modExp(g, x, p);

    std::cout << "Public Key (p, g, y): (" << p << ", " << g << ", " << y << ")" << std::endl;

    std::cout << "Enter message to encrypt (m): ";
    std::cin >> m;

    elgamalEncrypt(m, p, g, y, c1, c2);
    std::cout << "Encrypted message (c1, c2): (" << c1 << ", " << c2 << ")" << std::endl;

    int decryptedMessage = elgamalDecrypt(c1, c2, p, x);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}
