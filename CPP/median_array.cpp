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

class lengthSolution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int total = m + n;

		if (total & 0x01) {
			return find_kth(A, m, B, n, total / 2 + 1);
		} else {
			return (find_kth(A, m, B, n, total / 2) + find_kth(A, m, B, n, total/2 + 1))/2.0;
		}
	}

	int find_kth(int A[], int m, int B[], int n, int k) {
		if (m > n) return find_kth(B, n, A, m, k);

		if (m == 0) return B[k-1];
		if (k == 1) return min(A[0], B[0]);

		int ia = min(k/2, m), ib = k -ia;
		if (A[ia - 1] < B[ib - 1]) {
			return find_kth(A + ia, m - ia, B, n,  k - ia);
		} else if (A[ia - 1] > B[ib - 1]) {
	        return find_kth(A, m, B + ib, n - ib, k - ib);
		} else {
	    	return A[ia - 1];
		}

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
