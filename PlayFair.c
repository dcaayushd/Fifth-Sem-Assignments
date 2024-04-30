//Encrypt the plaintext "I study Cryptography" with the key 'guys' using playfair cipher in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

char mat[SIZE][SIZE];

void createMatrix(char key[]) {
    int i, j, k, flag = 0, *dicty;
    dicty = (int *)calloc(26, sizeof(int));
    char c;

    k = 0;
    c = 'A';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k <= strlen(key)) {
                if (key[k] == 'j')
                    key[k] = 'i';
                if (dicty[key[k] - 97] == 0) {
                    mat[i][j] = key[k];
                    dicty[key[k] - 97] = 1;
                } else
                    j--;
            } else {
                if (dicty[c - 97] == 0) {
                    mat[i][j] = c;
                    dicty[c - 97] = 1;
                } else
                    j--;
                c++;
            }
            k++;
        }
    }
}

void Playfair(char ch1, char ch2, char key[]) {
    int i, j, w, x, y, z;
    createMatrix(key);

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (ch1 == mat[i][j]) {
                w = i;
                x = j;
            } else if (ch2 == mat[i][j]) {
                y = i;
                z = j;
            }
        }
    }

    printf("%c%c", mat[w][z], mat[y][x]);
}

void cipher(char str[], char key[]) {
    int i, j;
    char msg[100];

    j = 0;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') {
            msg[j] = str[i];
            j++;
        }
    }
    msg[j] = '\0';

    for (i = 0; i < strlen(msg); i += 2) {
        if (msg[i + 1] == '\0')
            Playfair(msg[i], 'x', key);
        else {
            Playfair(msg[i], msg[i + 1], key);
        }
    }
}

int main() {
    char key[50], str[50];

    strcpy(key, "guys");
    strcpy(str, "IstudyCryptography");

    printf("Encryption: ");
    cipher(str, key);
    printf("\n");

    return 0;
}
