#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

char* encrypt(char* text, int s) {
    int len = strlen(text);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int i;

    for (i = 0; i < len; i++) {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result[i] = (char)((text[i] + s - 'A') % 26 + 'A');
        // Encrypt Lowercase letters
        else
            result[i] = (char)((text[i] + s - 'a') % 26 + 'a');
    }

    result[len] = '\0'; // Null terminate the string
    return result;
}

int main() {
    char text[] = "ISTUDYCRYPTO";
    int s = 4;

    printf("Text : %s\n", text);
    printf("Shift: %d\n", s);

    char* cipher = encrypt(text, s);
    printf("Cipher: %s\n", cipher);

    free(cipher); // Free the dynamically allocated memory

    return 0;
}