/**
 * vigenere.c
 * by Jayasakthi
 * 
 * Encripts the messages using a sequence of keys. 
 *
 * Usage: ./vigenere key
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
# include <ctype.h>

int main(int argc, string argv[])
{    
    // Validating the command line input
    if (argc != 2)
    
    {
        printf("Invalid Key\n");
        return 1;
    }
     
    string str = argv[1];
    int n= strlen(str);
    
    // check for numbers in keyword    
    for(int i=0;i < n;i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            printf("Error\n");
            return 1;
        }
    }
    
    // Get the Plain text from the user  
    string ptext = GetString();
    int i, j, len;
    
    // Encipher the message
    for (i = 0, j = 0,len = strlen(ptext); i < len; i++, j++)
    {
        if (j > strlen(str) - 1)
        {
            j = 0;
        }
          
        // If the user string is uppercase  
        if (ptext[i] >= 'A' && ptext[i] <= 'Z') 
        {    
            // Key is also uppercase    
            if (str[j] >= 'A' && str[j] <= 'Z') 
            {
                int cipher = ((((ptext[i] - 'A') + (str[j] - 'A')) % 26) + 'A'); 
                printf("%c", cipher);               
            }
            else
            {
                int cipher = ((((ptext[i] - 'A') + (str[j] - 'a')) % 26) + 'A'); 
                printf("%c", cipher);                
            }    
        }  
        
        // If string is lowercase
        else if (ptext[i] >= 'a' && ptext[i] <= 'z') 
        {
            // If key is also lower case
            if (str[j] >= 'a' && str[j] <= 'z') 
            {
                int cipher = ((((ptext[i] - 'a') + (str[j] - 'a')) % 26) + 'a'); 
                printf("%c", cipher);        
            }
            else
            {
                int cipher = ((((ptext[i] - 'a') + (str[j] - 'A')) % 26) + 'a'); 
                printf("%c", cipher);                
            }        
        }  
        
        // other than alphabets just print it.
        else
        {
            printf("%c", ptext[i]);
            j--;
        }            
    }
    
    printf("\n");
    return 0; 
  
        
 }
