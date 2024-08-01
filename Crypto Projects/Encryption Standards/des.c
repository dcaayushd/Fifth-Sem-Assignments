#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Initial permutation table
int IP[64] = { /* fill with actual IP table values */ };

// Final permutation table
int FP[64] = { /* fill with actual FP table values */ };

// Expansion table
int E[48] = { /* fill with actual E table values */ };

// S-boxes
int S[8][4][16] = {
    /* fill with actual S-box values */
};

// Permutation table
int P[32] = { /* fill with actual P table values */ };

// Permutation choice 1
int PC1[56] = { /* fill with actual PC1 table values */ };

// Permutation choice 2
int PC2[48] = { /* fill with actual PC2 table values */ };

// Number of left shifts per round
int SHIFTS[16] = { /* fill with actual SHIFTS values */ };

uint64_t initialPermutation(uint64_t input);
uint64_t finalPermutation(uint64_t input);
uint64_t expansion(uint32_t halfBlock);
uint32_t sBoxSubstitution(uint64_t expandedBlock);
uint32_t permutation(uint32_t input);
uint64_t desRound(uint64_t block, uint64_t subKey);
uint64_t desEncrypt(uint64_t plainText, uint64_t subKeys[16]);
void generateSubKeys(uint64_t key, uint64_t subKeys[16]);

uint64_t initialPermutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; ++i) {
        output |= ((input >> (64 - IP[i])) & 1) << (63 - i);
    }
    return output;
}

uint64_t finalPermutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; ++i) {
        output |= ((input >> (64 - FP[i])) & 1) << (63 - i);
    }
    return output;
}

uint64_t expansion(uint32_t halfBlock) {
    uint64_t expandedBlock = 0;
    for (int i = 0; i < 48; ++i) {
        expandedBlock |= ((halfBlock >> (32 - E[i])) & 1) << (47 - i);
    }
    return expandedBlock;
}

uint32_t sBoxSubstitution(uint64_t expandedBlock) {
    uint32_t substituted = 0;
    for (int i = 0; i < 8; ++i) {
        int row = ((expandedBlock >> (47 - i * 6)) & 0x20) | ((expandedBlock >> (42 - i * 6)) & 0x01);
        int col = (expandedBlock >> (43 - i * 6)) & 0x0F;
        int sBoxValue = S[i][row][col];
        substituted |= sBoxValue << (28 - i * 4);
    }
    return substituted;
}

uint32_t permutation(uint32_t input) {
    uint32_t output = 0;
    for (int i = 0; i < 32; ++i) {
        output |= ((input >> (32 - P[i])) & 1) << (31 - i);
    }
    return output;
}

uint64_t desRound(uint64_t block, uint64_t subKey) {
    uint32_t left = block >> 32;
    uint32_t right = block & 0xFFFFFFFF;
    uint64_t expandedRight = expansion(right);
    expandedRight ^= subKey;
    uint32_t substituted = sBoxSubstitution(expandedRight);
    uint32_t permutated = permutation(substituted);
    uint32_t newRight = left ^ permutated;
    uint64_t newBlock = ((uint64_t)right << 32) | newRight;
    return newBlock;
}

uint64_t desEncrypt(uint64_t plainText, uint64_t subKeys[16]) {
    uint64_t permutedText = initialPermutation(plainText);
    uint64_t tempText = permutedText;
    for (int round = 0; round < 16; ++round) {
        tempText = desRound(tempText, subKeys[round]);
    }
    uint64_t preOutput = ((tempText & 0xFFFFFFFF) << 32) | (tempText >> 32);
    uint64_t cipherText = finalPermutation(preOutput);
    return cipherText;
}

void generateSubKeys(uint64_t key, uint64_t subKeys[16]) {
    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; ++i) {
        permutedKey |= ((key >> (64 - PC1[i])) & 1) << (55 - i);
    }
    uint32_t left = (permutedKey >> 28) & 0x0FFFFFFF;
    uint32_t right = permutedKey & 0x0FFFFFFF;
    for (int round = 0; round < 16; ++round) {
        left = ((left << SHIFTS[round]) | (left >> (28 - SHIFTS[round]))) & 0x0FFFFFFF;
        right = ((right << SHIFTS[round]) | (right >> (28 - SHIFTS[round]))) & 0x0FFFFFFF;
        uint64_t combinedKey = ((uint64_t)left << 28) | right;
        subKeys[round] = 0;
        for (int i = 0; i < 48; ++i) {
            subKeys[round] |= ((combinedKey >> (56 - PC2[i])) & 1) << (47 - i);
        }
    }
}

int main() {
    uint64_t plainText = 0x0123456789ABCDEF; // Example 64-bit plaintext
    uint64_t key = 0x133457799BBCDFF1; // Example 64-bit key

    uint64_t subKeys[16];
    generateSubKeys(key, subKeys);

    uint64_t cipherText = desEncrypt(plainText, subKeys);

    printf("Cipher Text: %016llX\n", cipherText);

    return 0;
}
