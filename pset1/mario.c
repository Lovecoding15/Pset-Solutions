#include<cs50.h>
#include <stdio.h>
#include<math.h>

 int main() {
 int row,column,height;
 
 // Gets an integer value
 do
 {
    printf("Height:");
    height= GetInt();
 }
 while(height<0 || height>23);
 
 // Prints a Right aligned triangle
 for(row=2;row<=height+1;row++)
 {
   for(column=0;column<=height-row;column++)
   printf(" ");
    
       for(;column<=height;column++)
             printf("#");
     
   printf("\n");
  }
  
 }
