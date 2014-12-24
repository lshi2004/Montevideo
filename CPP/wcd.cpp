// cont/vector1.cpp
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set> 
#include <map> 

using namespace std; 

int   test_main()
{ 
  set <string> S; 
  set <string>::iterator j; 
  string t; 
  
  while (cin >> t) 
    S.insert(t); 

  for (j = S.begin(); j != S.end(); ++j) 
    cout << *j << "\n"; 

  return 0; 
} 

int main()
{ 
  map <string, int> M; 
  map <string, int>::iterator j; 
  string t; 
  
  while (cin >> t) 
    M[t]++; 

  for (j = M.begin(); j != M.end(); ++j) 
    cout << j->first << " " << j->second << "\n"; 

  return 0; 
} 

