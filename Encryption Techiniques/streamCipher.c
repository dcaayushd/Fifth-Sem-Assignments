#include <stdio.h>
#include <stdlib.h> // Include this to use srand and rand functions
#include <string.h> // Include this for string operations

void stream_cipher(char *text, unsigned int key);

int main() {
    char msg[] = "Meet me tonight.";
    printf("%s\n", msg);

    stream_cipher(msg, 5235395);
    printf("%s\n", msg);

    stream_cipher(msg, 5235395);
    printf("%s\n", msg);

    return 0;
}

void stream_cipher(char *text, unsigned int key) {
    // Use the 'key' to seed the random number generator
    srand(key);

    // XOR each character in the string with the next random number
    for (int k = 0; text[k] != '\0'; ++k) {
        text[k] ^= (char)rand(); // Use explicit cast for type conversion
    }
}