#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string all_letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int key = 3;

    // Create a dictionary to store the substitution for the given alphabet in the plain text based on the key
    map<char, char> dict1;
    for (int i = 0; i < all_letters.length(); i++)
    {
        dict1[all_letters[i]] = all_letters[(i + key) % all_letters.length()];
    }

    string plain_txt = "I am studying Data Encryption";
    string cipher_txt;

    // Loop to generate ciphertext
    for (int i = 0; i < plain_txt.length(); i++)
    {
        char c = plain_txt[i];
        if (all_letters.find(c) != string::npos)
        {
            cipher_txt += dict1[c]; // Convert char to string
        }
        else
        {
            cipher_txt += c;
        }
    }

    cout << "Cipher Text is: " << cipher_txt << endl;

    // Create a map to store the substitution for the given alphabet in the cipher text based on the key
    map<char, char> dict2;
    for (int i = 0; i < all_letters.length(); i++)
    {
        dict2[all_letters[i]] = all_letters[(i - key) % all_letters.length()];
    }

    string decrypt_txt;

    // Loop to recover plain text
    for (int i = 0; i < cipher_txt.length(); i++)
    {
        char c = cipher_txt[i];
        if (all_letters.find(c) != string::npos)
        {
            decrypt_txt += dict2[c]; // Convert char to string
        }
        else
        {
            decrypt_txt += c;
        }
    }

    cout << "Recovered plain text : " << decrypt_txt << endl;

    return 0;
}