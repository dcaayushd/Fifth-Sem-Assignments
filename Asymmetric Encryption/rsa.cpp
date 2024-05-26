// #include <iostream>
// #include <cmath>

// using namespace std;

// // Function to check if a number is prime
// bool isPrime(int n) {
//     if (n <= 1) return false;
//     if (n <= 3) return true;
//     if (n % 2 == 0 || n % 3 == 0) return false;
//     for (int i = 5; i * i <= n; i += 6)
//         if (n % i == 0 || n % (i + 2) == 0)
//             return false;
//     return true;
// }

// // Function to find GCD of two numbers
// int gcd(int a, int b) {
//     if (b == 0) return a;
//     return gcd(b, a % b);
// }

// // Function to generate keys for RSA
// void generateKeys(int p, int q, int& n, int& e, int& d) {
//     n = p * q;
//     int phi = (p - 1) * (q - 1);
//     for (e = 2; e < phi; e++) {
//         if (gcd(e, phi) == 1) break;
//     }
//     for (d = 2; d < phi; d++) {
//         if ((d * e) % phi == 1) break;
//     }
// }

// // Function to encrypt message
// int encrypt(int message, int e, int n) {
//     return int(pow(message, e)) % n;
// }

// // Function to decrypt message
// int decrypt(int cipher, int d, int n) {
//     return int(pow(cipher, d)) % n;
// }

// int main() {
//     int p, q, n, e, d;
//     cout << "Enter two prime numbers (p and q): ";
//     cin >> p >> q;
//     if (!isPrime(p) || !isPrime(q)) {
//         cout << "Both numbers must be prime." << endl;
//         return 1;
//     }
//     generateKeys(p, q, n, e, d);
//     cout << "Public Key (n, e): (" << n << ", " << e << ")" << endl;
//     cout << "Private Key (n, d): (" << n << ", " << d << ")" << endl;
//     int message;
//     cout << "Enter message to encrypt: ";
//     cin >> message;
//     int cipher = encrypt(message, e, n);
//     cout << "Encrypted message: " << cipher << endl;
//     int decrypted = decrypt(cipher, d, n);
//     cout << "Decrypted message: " << decrypted << endl;
//     return 0;
// }



#include <iostream>
using namespace std;

// Returns gcd of a and b
int gcd(int a, int h)
{
	int temp;
	while (1) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}

// Code to demonstrate RSA algorithm
int main()
{
	// Two random prime numbers
	double p = 3;
	double q = 7;

	// First part of public key:
	double n = p * q;

	// Finding other part of public key.
	// e stands for encrypt
	double e = 2;
	double phi = (p - 1) * (q - 1);
	while (e < phi) {
		// e must be co-prime to phi and
		// smaller than phi.
		if (gcd(e, phi) == 1)
			break;
		else
			e++;
	}

	// Private key (d stands for decrypt)
	// choosing d such that it satisfies
	// d*e = 1 + k * totient
	int k = 2; // A constant value
	double d = (1 + (k * phi)) / e;

	// Message to be encrypted
	double msg = 12;

	printf("Message data = %lf", msg);

	// Encryption c = (msg ^ e) % n
	double c = pow(msg, e);
	c = fmod(c, n);
	printf("\nEncrypted data = %lf", c);

	// Decryption m = (c ^ d) % n
	double m = pow(c, d);
	m = fmod(m, n);
	printf("\nOriginal Message Sent = %lf", m);

	return 0;
}
