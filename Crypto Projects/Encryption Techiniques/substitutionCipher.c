#include <stdio.h>
#include <string.h>
#include <ctype.h> // for isalpha() function

#define MAX_LEN 100

// Function to create a dictionary for encryption
void create_dict(char dict[], int key, int encrypt) {
    char all_letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = strlen(all_letters);
    int shift = encrypt ? key : -key;

    for (int i = 0; i < len; i++) {
        dict[all_letters[i]] = all_letters[(i + shift + len) % len];
    }
}

int main() {
    char plain_txt[MAX_LEN], cipher_txt[MAX_LEN], decrypt_txt[MAX_LEN];
    int key = 3;
    char encrypt_dict[256], decrypt_dict[256];

    printf("Enter the plaintext: ");
    fgets(plain_txt, MAX_LEN, stdin);

    // Create dictionaries for encryption and decryption
    create_dict(encrypt_dict, key, 1);
    create_dict(decrypt_dict, key, 0);

    // Encrypt the plaintext
    int i, j;
    for (i = 0, j = 0; plain_txt[i] != '\0'; i++) {
        if (isalpha(plain_txt[i])) {
            cipher_txt[j++] = encrypt_dict[plain_txt[i]];
        } else {
            cipher_txt[j++] = plain_txt[i];
        }
    }
    cipher_txt[j] = '\0';

    printf("Ciphertext: %s\n", cipher_txt);

    // Decrypt the ciphertext
    for (i = 0, j = 0; cipher_txt[i] != '\0'; i++) {
        if (isalpha(cipher_txt[i])) {
            decrypt_txt[j++] = decrypt_dict[cipher_txt[i]];
        } else {
            decrypt_txt[j++] = cipher_txt[i];
        }
    }
    decrypt_txt[j] = '\0';

    printf("Decrypted plaintext: %s\n", decrypt_txt);

    return 0;
}