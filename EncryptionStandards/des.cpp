#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Initial permutation table
const int IP[64] = { /* fill with actual IP table values */ };

// Final permutation table
const int FP[64] = { /* fill with actual FP table values */ };

// Expansion table
const int E[48] = { /* fill with actual E table values */ };

// S-boxes
const int S[8][4][16] = {
    /* fill with actual S-box values */
};

// Permutation table
const int P[32] = { /* fill with actual P table values */ };

// Permutation choice 1
const int PC1[56] = { /* fill with actual PC1 table values */ };

// Permutation choice 2
const int PC2[48] = { /* fill with actual PC2 table values */ };

// Number of left shifts per round
const int SHIFTS[16] = { /* fill with actual SHIFTS values */ };

// Function prototypes
bitset<64> initialPermutation(bitset<64> input);
bitset<64> finalPermutation(bitset<64> input);
bitset<48> expansion(bitset<32> halfBlock);
bitset<32> sBoxSubstitution(bitset<48> expandedBlock);
bitset<32> permutation(bitset<32> input);
bitset<64> desRound(bitset<64> block, bitset<48> subKey);
bitset<64> desEncrypt(bitset<64> plainText, const vector<bitset<48> > &subKeys);
vector<bitset<48> > generateSubKeys(bitset<64> key);

bitset<64> initialPermutation(bitset<64> input)
{
    bitset<64> output;
    for (int i = 0; i < 64; ++i)
        output[63 - i] = input[64 - IP[i]];
    return output;
}

bitset<64> finalPermutation(bitset<64> input)
{
    bitset<64> output;
    for (int i = 0; i < 64; ++i)
        output[63 - i] = input[64 - FP[i]];
    return output;
}

bitset<48> expansion(bitset<32> halfBlock)
{
    bitset<48> expandedBlock;
    for (int i = 0; i < 48; ++i)
        expandedBlock[47 - i] = halfBlock[32 - E[i]];
    return expandedBlock;
}

bitset<32> sBoxSubstitution(bitset<48> expandedBlock)
{
    bitset<32> substituted;
    for (int i = 0; i < 8; ++i)
    {
        int row = expandedBlock[47 - (i * 6)] * 2 + expandedBlock[47 - (i * 6 + 5)];
        int col = expandedBlock[47 - (i * 6 + 1)] * 8 + expandedBlock[47 - (i * 6 + 2)] * 4 +
                  expandedBlock[47 - (i * 6 + 3)] * 2 + expandedBlock[47 - (i * 6 + 4)];
        int sBoxValue = S[i][row][col];
        for (int j = 0; j < 4; ++j)
        {
            substituted[31 - (i * 4 + j)] = (sBoxValue >> (3 - j)) & 1;
        }
    }
    return substituted;
}

bitset<32> permutation(bitset<32> input)
{
    bitset<32> output;
    for (int i = 0; i < 32; ++i)
        output[31 - i] = input[32 - P[i]];
    return output;
}

bitset<64> desRound(bitset<64> block, bitset<48> subKey)
{
    bitset<32> left, right, newRight;
    for (int i = 0; i < 32; ++i)
    {
        left[i] = block[63 - i];
        right[i] = block[31 - i];
    }
    bitset<48> expandedRight = expansion(right);
    expandedRight ^= subKey;
    bitset<32> substituted = sBoxSubstitution(expandedRight);
    bitset<32> permutated = permutation(substituted);
    newRight = left ^ permutated;

    bitset<64> newBlock;
    for (int i = 0; i < 32; ++i)
    {
        newBlock[63 - i] = right[i];
        newBlock[31 - i] = newRight[i];
    }
    return newBlock;
}

bitset<64> desEncrypt(bitset<64> plainText, const vector<bitset<48> > &subKeys)
{
    bitset<64> permutedText = initialPermutation(plainText);
    bitset<64> tempText = permutedText;
    for (int round = 0; round < 16; ++round)
    {
        tempText = desRound(tempText, subKeys[round]);
    }
    bitset<64> preOutput;
    for (int i = 0; i < 32; ++i)
    {
        preOutput[63 - i] = tempText[31 - i];
        preOutput[31 - i] = tempText[63 - i];
    }
    bitset<64> cipherText = finalPermutation(preOutput);
    return cipherText;
}

vector<bitset<48> > generateSubKeys(bitset<64> key)
{
    vector<bitset<48> > subKeys(16);
    bitset<56> permutedKey;
    for (int i = 0; i < 56; ++i)
        permutedKey[55 - i] = key[64 - PC1[i]];

    bitset<28> left, right;
    for (int i = 0; i < 28; ++i)
    {
        left[i] = permutedKey[55 - i];
        right[i] = permutedKey[27 - i];
    }

    for (int round = 0; round < 16; ++round)
    {
        left = left << SHIFTS[round] | left >> (28 - SHIFTS[round]);
        right = right << SHIFTS[round] | right >> (28 - SHIFTS[round]);

        bitset<56> combinedKey;
        for (int i = 0; i < 28; ++i)
        {
            combinedKey[i + 28] = left[i];
            combinedKey[i] = right[i];
        }

        for (int i = 0; i < 48; ++i)
            subKeys[round][47 - i] = combinedKey[56 - PC2[i]];
    }
    return subKeys;
}

int main()
{
    //Plain text 64 bits
    bitset<64> plainText(string("0000000100100011010001010110011110001001101010111100110111101111")); 
    //Key 64 bits
    bitset<64> key(string("0001001100110100010101110111100110011011101111001101111111110001")); 

    vector<bitset<48> > subKeys = generateSubKeys(key);

    bitset<64> cipherText = desEncrypt(plainText, subKeys);

    cout << "Cipher Text: " << cipherText << endl;

    return 0;
}
