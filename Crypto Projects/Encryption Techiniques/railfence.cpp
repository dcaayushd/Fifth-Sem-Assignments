#include <iostream>
#include <string>

using namespace std;

void railFenceCipher(string plaintext, int depth) {
    int len = plaintext.length();
    char rail[depth][len];
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == depth - 1)
            dir_down = !dir_down;
        rail[row][col++] = plaintext[i];
        dir_down ? row++ : row--;
    }

    cout << "Encrypted Message: ";
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                cout << rail[i][j];
    cout << endl;
}

int main() {
    string plaintext = "IstudyCryptography";
    cout << "Encryption with depth 2: ";
    railFenceCipher(plaintext, 2);
    cout << "Encryption with depth 3: ";
    railFenceCipher(plaintext, 3);
    return 0;
}