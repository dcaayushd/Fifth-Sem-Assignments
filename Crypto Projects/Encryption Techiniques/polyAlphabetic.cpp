#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to encrypt the message using polyalphabetic cipher
void encrypt(string message, string key, string& encryptedMsg) {
    int msgLen = message.length(), keyLen = key.length();
    string newKey(msgLen, ' ');
    
    // Generating new key
    for (int i = 0, j = 0; i < msgLen; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        newKey[i] = key[j];
    }
    
    encryptedMsg.clear();
    
    // Encryption
    for (int i = 0; i < msgLen; ++i)
        encryptedMsg.push_back(((toupper(message[i]) - 'A' + toupper(newKey[i]) - 'A') % 26) + 'A');
}

// Function to decrypt the message
void decrypt(string encryptedMsg, string key, string& decryptedMsg) {
    int msgLen = encryptedMsg.length(), keyLen = key.length();
    string newKey(msgLen, ' ');
    
    // Generating new key
    for (int i = 0, j = 0; i < msgLen; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        newKey[i] = key[j];
    }
    
    decryptedMsg.clear();
    
    // Decryption
    for (int i = 0; i < msgLen; ++i)
        decryptedMsg.push_back((((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A');
}

int main() {
    string message = "HIDEMONEY";
    string key = "TUTORIALS";
    string encryptedMsg, decryptedMsg;
    
    // Encrypts the message using the provided key and stores it in encryptedMsg
    encrypt(message, key, encryptedMsg);
    cout << "Encrypted Message: " << encryptedMsg << endl;
    
    // Decrypting the same message to check correctness of encryption/decryption process.
    decrypt(encryptedMsg, key, decryptedMsg);
    cout << "Decrypted Message: " << decryptedMsg << endl;
    
    return 0;
}