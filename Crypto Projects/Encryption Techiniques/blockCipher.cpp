#include <iostream>
#include <string>

std::string xor_cipher(const std::string& input, char key) {
    std::string output;
    output.resize(input.size());
    for (int i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key;
    }
    return output;
}

int main() {
    std::string plaintext = "Hello, World!";
    char key = 'K'; // Key for XOR cipher

    // Encryption
    std::string ciphertext = xor_cipher(plaintext, key);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    // Decryption
    std::string decrypted = xor_cipher(ciphertext, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
