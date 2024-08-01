//Encrypt and Decrypt the message 'hide money' with key 'tutorials' using polyalphabetic cipher in C
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// function to encrypt the message 'hide money' using polyalphabetic cipher
void encrypt(char* message, char* key, char* encryptedMsg) {
    int msgLen = strlen(message), keyLen = strlen(key), i, j;

    char newKey[msgLen];

    // generating new key
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }
    newKey[i] = '\0';

    // encryption
    for(i = 0; i < msgLen; ++i)
        encryptedMsg[i] = ((message[i] + newKey[i]) % 26) + 'A';

    encryptedMsg[i] = '\0';
}

// function to decrypt message
void decrypt(char* encryptedMsg, char* key, char* decryptedMsg) {
    int msgLen = strlen(encryptedMsg), keyLen = strlen(key), i, j;

    char newKey[msgLen];

    // generating new key
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }
    newKey[i] = '\0';

    // decryption
    for(i = 0; i < msgLen; ++i)
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';

    decryptedMsg[i] = '\0';
}

int main() {
    char message[] = "HIDEMONEY";
    char key[] = "TUTORIALS";
    char encryptedMsg[100];
    char decryptedMsg[100];

    // encrypts the message using the provided key and stores it in encryptedMsg
    encrypt(message, key, encryptedMsg);
    printf("Encrypted Message: %s\n", encryptedMsg);
    
    // decrypting the same message to check correctness of encryption/decryption process.
    decrypt(encryptedMsg, key, decryptedMsg);
    printf("Decrypted Message: %s\n", decryptedMsg);
    
    return 0;
}
