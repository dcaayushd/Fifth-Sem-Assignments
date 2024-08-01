//Encrypt the plaintext "I study Cryptography" with depth 2 and 3 separately using Rail fence cipher in C
#include <stdio.h>
#include <string.h>

void railFenceCipher(char* plaintext, int depth) {
    int len = strlen(plaintext);
    char rail[depth][len];

    for (int i=0; i < depth; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int dir_down = 0;
    int row = 0, col = 0;

    for (int i=0; i < len; i++) {
        if (row == 0 || row == depth-1)
            dir_down = !dir_down;

        rail[row][col++] = plaintext[i];

        dir_down?row++ : row--;
    }

    printf("Encrypted Message: ");
    for (int i=0; i < depth; i++)
        for (int j=0; j < len; j++)
            if (rail[i][j]!='\n')
                printf("%c", rail[i][j]);
    printf("\n");
}

int main() {
    char plaintext[] = "IstudyCryptography";

    printf("Encryption with depth 2: ");
    railFenceCipher(plaintext, 2);
    
    printf("Encryption with depth 3: ");
    railFenceCipher(plaintext, 3);

    return 0;
}
