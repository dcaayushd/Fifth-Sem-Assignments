#include <iostream>
#include <vector>
#include <string>

#define SIZE 5

using namespace std;

vector<vector<char> > mat(SIZE, vector<char>(SIZE));

void createMatrix(string key) {
    int i, j, k, flag = 0;
    vector<int> dicty(26, 0);
    char c;

    k = 0;
    c = 'A';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k <= key.length()) {
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

void Playfair(char ch1, char ch2, string key) {
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

    cout << mat[w][z] << mat[y][x];
}

void cipher(string str, string key) {
    int i, j;
    string msg;

    j = 0;
    for (i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            msg += str[i];
            j++;
        }
    }

    for (i = 0; i < msg.length(); i += 2) {
        if (msg[i + 1] == '\0')
            Playfair(msg[i], 'x', key);
        else {
            Playfair(msg[i], msg[i + 1], key);
        }
    }
}

int main() {
    string key = "guys";
    string str = "IstudyCryptography";

    cout << "Encryption: ";
    cipher(str, key);
    cout << "\n";

    return 0;
}
