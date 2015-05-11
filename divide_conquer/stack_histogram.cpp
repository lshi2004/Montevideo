#include <stack> 
#include <stdio.h>
#include <vector> 
#include <iostream> 
 
using namespace std; 

int largestRectangleArea(vector<int> &h) {  
       stack<int> S;  
       h.push_back(0);  
       int sum = 0;  
       for (int i = 0; i < h.size(); i++) {  
            if (S.empty() || h[i] > h[S.top()]) { 
                S.push(i); cout << "push " << i << endl;   
            } else {  
                 int tmp = S.top();  
                 S.pop();  
                 cout << "pop " << tmp << " and " << i << endl; 
                 sum = max(sum, h[tmp]*(S.empty()? i : i-S.top()-1));  
                 i--;  
            }  
       }  
       return sum;  
  }  

int main()
{ 
    vector<int> v; 
 
    v  = { 2, 1, 5, 6, 2, 3 } ; 

    int l = largestRectangleArea(v); 

    cout << "the answer is " << l << endl; 

    return 0; 
} 


