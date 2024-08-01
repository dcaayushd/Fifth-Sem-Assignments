#include <stdio.h>

#define BLOCK_SIZE 8

void encrypt(char block[BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = block[i] ^ 0xFF; // Simple XOR operation with a constant
    }
}

void decrypt(char block[BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = block[i] ^ 0xFF; // XOR operation is its own inverse
    }
}

int main() {
    char block[BLOCK_SIZE] = "ABCDEFGH";

    printf("Original text: %s\n", block);

    encrypt(block);
    printf("Encrypted text: %s\n", block);

    decrypt(block);
    printf("Decrypted text: %s\n", block);

    return 0;
}
