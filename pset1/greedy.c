#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    int value,counter=0;
    float change;
    
    // Get a float value from user
    do
    {
        printf("Enter the change: ");
        change= GetFloat();
        
    } while(change<=0);
    
    // Rounds the float value and cast it to an integer value
    change = change*100;
    change=roundf(change);
    value=(int)change;
   
   /* Checks for the greater value first 
      to reduce the number of coins as per the spec*/
      
    while(value>=25)
    {
        counter++;
        value=value-25;
    }
  
       
    while(value>=10)
    {
        counter++;
        value=value-10;
    }
    
       
    while(value>=5)
    {
        counter++;
        value=value-5;
    }
   
       
    while(value>=1)
    {
        counter++;
        value=value-1;
    }
   
   // Prints the number of coins
    printf("%d\n",counter);
     
}
