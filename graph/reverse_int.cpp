#include <stdio.h> 

bool isPlaindrome(int x) 
{
    if (x < 0) return false; 

    int div = 1; 
    while ( x / div >= 10) div *= 10; 

    while (x > 0) { 
        int x1 = x / div; 
        int x2 = x % 10; 
        if (x1 != x2) return false;         
       
        x %= div; 
        x /= 10; 
        div /= 100;  
               
    }      

    return true; 
} 


int reverse(int x) 
{
    int r = 0; 
    while (x != 0) { 
        r = r * 10 + x % 10; 
        x /= 10; 
    }
    return r;  
} 

int main() 
{ 
    int x = -321; 

    printf(" old %d new %d \n", 
           x, reverse(x)); 

    printf(" palindrome %d  and %d", isPlaindrome(4334), 
           isPlaindrome(78977)); 

    return 0; 
} 
