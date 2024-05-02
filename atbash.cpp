// C++ program to implement Atbash Cipher

#include <iostream>
#include <string>
#include <map>

using namespace std;

// Map to lookup various alphabets
map<char, char> lookup_table;

// Function to initialize the lookup_table
void initializeLookupTable() {
    lookup_table['A'] = 'Z';
    lookup_table['B'] = 'Y';
    lookup_table['C'] = 'X';
    lookup_table['D'] = 'W';
    lookup_table['E'] = 'V';
    lookup_table['F'] = 'U';
    lookup_table['G'] = 'T';
    lookup_table['H'] = 'S';
    lookup_table['I'] = 'R';
    lookup_table['J'] = 'Q';
    lookup_table['K'] = 'P';
    lookup_table['L'] = 'O';
    lookup_table['M'] = 'N';
    lookup_table['N'] = 'M';
    lookup_table['O'] = 'L';
    lookup_table['P'] = 'K';
    lookup_table['Q'] = 'J';
    lookup_table['R'] = 'I';
    lookup_table['S'] = 'H';
    lookup_table['T'] = 'G';
    lookup_table['U'] = 'F';
    lookup_table['V'] = 'E';
    lookup_table['W'] = 'D';
    lookup_table['X'] = 'C';
    lookup_table['Y'] = 'B';
    lookup_table['Z'] = 'A';
}

// Function to implement Atbash Cipher
string atbash(string message) {
    string cipher = "";
   for (string::size_type i = 0; i < message.length(); ++i) {
    char letter = message[i];
        // Checking for space
        if (letter != ' ') {
            // Adds the corresponding letter from the lookup_table
            cipher += lookup_table[toupper(letter)];
        }
        else {
            // Adds space
            cipher += ' ';
        }
    }
    return cipher;
}

// Driver function to run the program
int main() {
    initializeLookupTable(); // Initialize the lookup_table

    // Encrypt the given message
    string message = "I LOVE CODING";
    cout << atbash(message) << "\n";

    // Decrypt the given message
    message = "R OLEV XLWRMT";
    cout << atbash(message) << "\n";

    return 0;
}