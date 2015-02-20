//============================================================================
// Name        : HC.cpp
// Author      : HS
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <stack>

using namespace std;

class lengthSolution {
public:
	int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		int total = 0;
		int j = -1;

		for (int i = 0, sum  = 0; i < gas.size(); i++) {
			sum += gas[i] - cost[i];
			total += gas[i] - cost[i];
			if (sum < 0) {
				j = i;
				sum = 0;
			}
		}

		return total >= 0 ? j + 1 : -1;
	}





};

int main() {
int *ptr = new int[10];
//	int **ary = new int*[100];

ptr[0] = 1;
ptr[1] = 2;

#if 0
auto q = new multipleQueens;
vector<vector<string>> result = q->solveQueens(4);

for (auto i : result) {
	for (auto j: i) {
		cout << j << " \t";
	}
	cout << endl <<endl <<endl;
}

#endif

auto pp = new lengthSolution;
int k1 = 0;
cout << "hello" << k1 << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
return 0;
}
