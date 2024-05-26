#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to encrypt the message
void vigenere_encrypt(string message, string key, string& encrypted_message) {
    int message_len = message.length();
    int key_len = key.length();
    encrypted_message.clear();

    for (int i = 0, j = 0; i < message_len; ++i, j = (j + 1) % key_len) {
        char c = (tolower(message[i]) - 'a' + tolower(key[j]) - 'a') % 26 + 'a';
        encrypted_message.push_back(c);
    }
}

// Function to decrypt the message
void vigenere_decrypt(string encrypted_message, string key, string& decrypted_message) {
    int message_len = encrypted_message.length();
    int key_len = key.length();
    decrypted_message.clear();

    for (int i = 0, j = 0; i < message_len; ++i, j = (j + 1) % key_len) {
        char c = (tolower(encrypted_message[i]) - tolower(key[j]) + 26) % 26 + 'a';
        decrypted_message.push_back(c);
    }
}

int main() {
    string message = "attackfromsoutheast";
    string key = "point";
    string encrypted_message, decrypted_message;

    vigenere_encrypt(message, key, encrypted_message);
    cout << "Encrypted Message: " << encrypted_message << endl;

    // To decrypt the message, we need to use the same key
    vigenere_decrypt(encrypted_message, key, decrypted_message);
    cout << "Decrypted Message: " << decrypted_message << endl;

    return 0;
}