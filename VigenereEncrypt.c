// Encrypt and Decrypt the message "attack from south east’ with key ‘point’ using vigenere cipher.
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//function to encrypt the message
void vigenere_encrypt(char *message, char *key, char *encrypted_message)
{
    int message_len = strlen(message);
    int key_len = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < message_len; ++i, j = (j + 1) % key_len)
    {
        char c = (tolower(message[i]) - 'a' + tolower(key[j]) - 'a') % 26 + 'a';
        encrypted_message[i] = c;
    }
    encrypted_message[i] = '\0';
}

//function to decrypt the message
void vigenere_decrypt(char *encrypted_message, char *key, char *decrypted_message)
{
    int message_len = strlen(encrypted_message);
    int key_len = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < message_len; ++i, j = (j + 1) % key_len)
    {
        char c = (tolower(encrypted_message[i]) - tolower(key[j]) + 26) % 26 + 'a';
        decrypted_message[i] = c;
    }
    decrypted_message[i] = '\0';
}

int main()
{
    char message[] = "attackfromsoutheast";
    char key[] = "point";
    char encrypted_message[50];
    char decrypted_message[50];

    vigenere_encrypt(message, key, encrypted_message);

    printf("Encrypted Message: %s\n", encrypted_message);

    //To Decrypt the message we need to use the same Key.
    vigenere_decrypt(encrypted_message, key, decrypted_message);

    printf("Decrypted Message: %s\n", decrypted_message);

    return 0;
}
