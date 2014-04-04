/*
*  caesar.c
*  by Jayasakthi
*
*  Encipher messages by rotating 
*  each letter by k position,wrapping around from z to a
*  as needed.
* 
*  Usage: ./caesar key
*
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key;
    
    // Validating the command line input
    if (argc == 2)
    {
        key = atoi(argv[1]);
    }
    else
    {
        printf("Invalid Key\n");
        return 1;
    }
    // Get the Plain text from the user   
    string ptext = GetString();
    
    // Encipher the message
    for(int i = 0, n = strlen(ptext); i < n; i++)
    {
        // Encipher for capital Letters
        if ( ptext[i] >= 65 && ptext[i] < 91)
        {
            int cipher = ((((ptext[i] - 65) + key)) % 26) + 65;
            printf("%c", cipher);
        }
        // For Lower case letters
        else if (ptext[i] >= 97 && ptext[i] < 123)
        {
            int cipher = ((((ptext[i] - 97) + key)) % 26) + 97;
            printf("%c", cipher);
        }
        // For other characters
        else
        {
            printf("%c", ptext[i]);
        }

    }
    printf("\n");

    return EXIT_SUCCESS;
     
}
