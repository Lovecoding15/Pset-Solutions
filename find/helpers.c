/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   // Binary Search Algorithm
    
    if(n<0)
    {
        return false;
    }
    
    int first=0, last= n-1, middle= (first+last)/2;
    
    while(first<=last)
    {
        if(values[middle]==value)
        return true;
        
        else if(values[middle]<value)
        first= middle+1;
        
        else
        last= middle-1;
        
        middle = (first+last)/2;   
    }
    
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)  //Bubble sort
{
    // implement an O(n^2) sorting algorithm
    int i,j,swap;
    for(i=0;i<(n-1);i++)
    {
        for(j=0;j<(n-i-1);j++)
        {
            if(values[j]>values[j+1])
            {
                swap=values[j];
                values[j]=values[j+1];
                values[j+1]=swap;   
            }
        }
    }
   
}
