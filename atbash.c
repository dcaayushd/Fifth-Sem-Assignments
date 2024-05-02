#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to implement Atbash Cipher
char* atbash(char* message) {
    int len = strlen(message);
    char* cipher = (char*)malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) {
        char letter = message[i];

        // Checking for space
        if (letter != ' ') {
            // Encrypt/Decrypt the letter
            if (isupper(letter)) {
                cipher[i] = 'Z' - (letter - 'A');
            } else {
                cipher[i] = 'z' - (letter - 'a');
            }
        } else {
            // Adds space
            cipher[i] = ' ';
        }
    }

    cipher[len] = '\0'; // Null terminate the string
    return cipher;
}

int main() {
    char message[] = "CODING IS SUPER FUN";
    printf("Original message: %s\n", message);

    char* encrypted = atbash(message);
    printf("Encrypted message: %s\n", encrypted);

    char* decrypted = atbash(encrypted);
    printf("Decrypted message: %s\n", decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}