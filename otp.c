#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>

// Method 1
// Returning encrypted text
char* stringEncryption(char* text, char* key)
{
    int len = strlen(text);
    char* cipherText = (char*)malloc(len + 1);
    int cipher[len];

    for (int i = 0; i < len; i++) {
        cipher[i] = toupper(text[i]) - 'A' + toupper(key[i]) - 'A';
    }

    for (int i = 0; i < len; i++) {
        if (cipher[i] > 25) {
            cipher[i] = cipher[i] - 26;
        }
    }

    for (int i = 0; i < len; i++) {
        cipherText[i] = cipher[i] + 'A';
    }
    cipherText[len] = '\0';

    return cipherText;
}

// Method 2
// Returning plain text
char* stringDecryption(char* s, char* key)
{
    int len = strlen(s);
    char* plainText = (char*)malloc(len + 1);
    int plain[len];

    for (int i = 0; i < len; i++) {
        plain[i] = s[i] - 'A' - (toupper(key[i]) - 'A');
    }

    for (int i = 0; i < len; i++) {
        if (plain[i] < 0) {
            plain[i] = plain[i] + 26;
        }
    }

    for (int i = 0; i < len; i++) {
        plainText[i] = plain[i] + 'A';
    }
    plainText[len] = '\0';

    return plainText;
}

// Method 3
// Main driver method
int main()
{
    char plainText[] = "Hello";
    char key[] = "MONEY";

    for (int i = 0; plainText[i]; i++) {
        plainText[i] = toupper(plainText[i]);
    }

    for (int i = 0; key[i]; i++) {
        key[i] = toupper(key[i]);
    }

    char* encryptedText = stringEncryption(plainText, key);

    printf("Cipher Text - %s\n", encryptedText);

    char* message = stringDecryption(encryptedText, key);
    printf("Message - %s\n", message);

    free(encryptedText);
    free(message);

    return 0;
}