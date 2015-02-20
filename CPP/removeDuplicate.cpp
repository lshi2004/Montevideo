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
#include <stack>

using namespace std;

class Solution {
public:
	int removeDuplicates(int A[], int n) {
		if (n == 0)
			return 0;

		int index = 0;
		int times = 0;
		for (int i = 1; i < n; i++) {
			if (A[index] != A[i] || times < 1) {
				if (A[index] == A[i]) {
					times++;
				} else {
					times = 0;
				}
				A[++index] = A[i];
			}
		}
		return index + 1;
	}

	int removeDuplicates_new(int A[], int n) {
		return distance(A, unique(A, A + n));
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
	bool k1 = pp->validParentheses("()");
	cout << "hello" << k1 << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
