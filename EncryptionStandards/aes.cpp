#include <iostream>
#include <vector>
#include <iomanip>

// AES parameters
const int Nb = 4;           // Number of columns (32-bit words) comprising the state
const int Nk = 4;           // Number of 32-bit words comprising the key (4 for 128-bit key)
const int Nr = 10;          // Number of rounds (10 for 128-bit key)

// AES S-box
const uint8_t sBox[256] = {
    // 0     1    2      3     4     5     6     7     8     9     A     B     C     D     E     F
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// AES Rcon
const uint8_t Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// Helper function to print a 4x4 matrix
void printState(uint8_t state[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(state[i][j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// AES key expansion
void keyExpansion(const uint8_t* key, uint8_t* w) {
    int i, j;
    uint8_t temp[4], k;

    for (i = 0; i < Nk; ++i) {
        w[4 * i + 0] = key[4 * i + 0];
        w[4 * i + 1] = key[4 * i + 1];
        w[4 * i + 2] = key[4 * i + 2];
        w[4 * i + 3] = key[4 * i + 3];
    }

    for (i = Nk; i < Nb * (Nr + 1); ++i) {
        temp[0] = w[4 * (i - 1) + 0];
        temp[1] = w[4 * (i - 1) + 1];
        temp[2] = w[4 * (i - 1) + 2];
        temp[3] = w[4 * (i - 1) + 3];

        if (i % Nk == 0) {
            // RotWord
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;

            // SubWord
            temp[0] = sBox[temp[0]];
            temp[1] = sBox[temp[1]];
            temp[2] = sBox[temp[2]];
            temp[3] = sBox[temp[3]];

            // Rcon
            temp[0] ^= Rcon[i / Nk - 1];
        }

        w[4 * i + 0] = w[4 * (i - Nk) + 0] ^ temp[0];
        w[4 * i + 1] = w[4 * (i - Nk) + 1] ^ temp[1];
        w[4 * i + 2] = w[4 * (i - Nk) + 2] ^ temp[2];
        w[4 * i + 3] = w[4 * (i - Nk) + 3] ^ temp[3];
    }
}

// AES AddRoundKey
void addRoundKey(uint8_t state[4][4], const uint8_t* roundKey) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] ^= roundKey[i * 4 + j];
        }
    }
}

// AES SubBytes
void subBytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = sBox[state[i][j]];
        }
    }
}

// AES ShiftRows
void shiftRows(uint8_t state[4][4]) {
    uint8_t temp;

    // Rotate first row 1 columns to left
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Rotate second row 2 columns to left
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Rotate third row 3 columns to left
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

// AES MixColumns
void mixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];

    for (int i = 0; i < 4; ++i) {
        temp[0] = (state[0][i] << 1) ^ ((state[0][i] >> 7) * 0x1b) ^ (state[1][i] << 1) ^ ((state[1][i] >> 7) * 0x1b) ^ state[1][i] ^ state[2][i] ^ state[3][i];
        temp[1] = state[0][i] ^ (state[1][i] << 1) ^ ((state[1][i] >> 7) * 0x1b) ^ (state[2][i] << 1) ^ ((state[2][i] >> 7) * 0x1b) ^ state[2][i] ^ state[3][i];
        temp[2] = state[0][i] ^ state[1][i] ^ (state[2][i] << 1) ^ ((state[2][i] >> 7) * 0x1b) ^ (state[3][i] << 1) ^ ((state[3][i] >> 7) * 0x1b) ^ state[3][i];
        temp[3] = (state[0][i] << 1) ^ ((state[0][i] >> 7) * 0x1b) ^ state[0][i] ^ state[1][i] ^ state[2][i] ^ (state[3][i] << 1) ^ ((state[3][i] >> 7) * 0x1b);

        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];
    }
}

// AES encryption
void aesEncrypt(const uint8_t* input, const uint8_t* key, uint8_t* output) {
    uint8_t state[4][4];
    std::vector<uint8_t> roundKey(Nb * (Nr + 1) * 4);

    keyExpansion(key, roundKey.data());

    // Copy input to state
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] = input[i * 4 + j];
        }
    }

    addRoundKey(state, roundKey.data());

    for (int round = 1; round < Nr; ++round) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, roundKey.data() + round * Nb * 4);
    }

    subBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKey.data() + Nr * Nb * 4);

    // Copy state to output
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            output[i * 4 + j] = state[j][i];
        }
    }
}

int main() {
    uint8_t plaintext[16] = {
        0x32, 0x43, 0xF6, 0xA8, 0x88, 0x5A, 0x30, 0x8D,
        0x31, 0x31, 0x98, 0xA2, 0xE0, 0x37, 0x07, 0x34
    };
    uint8_t key[16] = {
        0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0x88, 0x09, 0xCF, 0x4F, 0x3C, 0x4F
    };
    uint8_t ciphertext[16];

    aesEncrypt(plaintext, key, ciphertext);

    std::cout << "Cipher Text:\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ciphertext[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}
