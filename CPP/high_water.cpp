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
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int total = m + n;

		if (total & 0x01) {
			return find_kth(A, m, B, n, total / 2 + 1);
		} else {
			return (find_kth(A, m, B, n, total / 2)
					+ find_kth(A, m, B, n, total / 2 + 1)) / 2.0;
		}
	}

	int find_kth(int A[], int m, int B[], int n, int k) {
		if (m > n)
			return find_kth(B, n, A, m, k);

		if (m == 0)
			return B[k - 1];
		if (k == 1)
			return min(A[0], B[0]);

		int ia = min(k / 2, m), ib = k - ia;
		if (A[ia - 1] < B[ib - 1]) {
			return find_kth(A + ia, m - ia, B, n, k - ia);
		} else if (A[ia - 1] > B[ib - 1]) {
			return find_kth(A, m, B + ib, n - ib, k - ib);
		} else {
			return A[ia - 1];
		}

	}

	int longestConsecutive(vector<int> &num) {
		unordered_map<int, int> used;

		for (auto i : num)
			used[i] = 0;

		int longest = 0;

		for (auto i : num) {
			if (used[i] > 0)
				continue;

			int length = 1;
			used[i] = 1;

			for (int j = i + 1; used.find(j) != used.end(); j++) {
				length++;
				used[j] = 1;
			}

			for (int j = i - 1; used.find(j) != used.end(); j--) {
				length++;
				used[j] = 1;
			}

			longest = max(longest, length);
		}

		return longest;

	}

	vector<int> twoSum(vector<int> &num, int target) {
		unordered_map<int, int> key_map;
		vector<int> result;

		for (int i = 0; i < num.size(); ++i) {
			key_map[num[i]] = i;
		}

		for (int i = 0; i < num.size(); ++i) {
			const int gap = target - num[i];
			if (key_map.find(gap) != key_map.end() && key_map[gap] != i) {
				result.push_back(i + 1);
				result.push_back(key_map[gap] + 1);
				break;
			}
		}

		return result;
	}

	vector<vector<int>> threeSum(vector<int>& num) {
		vector<vector<int>> result;

		if (num.size() < 3)
			return result;
		sort(num.begin(), num.end());
		int target = 0;

		auto last = num.end();
		for (auto i = num.begin(); i < last - 2; ++i) {
			auto j = i + 1;
			if (i > num.begin() && *i == *(i - 1))
				continue;
			auto k = last - 1;
			target = 0 - *i;
			while (j < k) {
				if (*j + *k < target) {
					++j;
					while (*j == *(j - 1) && j < k)
						++j;
				} else if (*j + *k > target) {
					--k;
					while (*k == *(k + 1) && j < k)
						--k;
				} else {
					result.push_back( { *i, *j, *k });
					++j;
					--k;
					while (*j == *(j - 1) && *k == *(k + 1) && j < k)
						++j;
				}
			}
		}
		return result;
	}

	vector<vector<int>> threeSum1(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		std::sort(num.begin(), num.end());
		vector<vector<int> > result;
		int len = num.size();
		for (int i = 0; i < len; i++) {
			int target = 0 - num[i];
			int start = i + 1, end = len - 1;
			while (start < end) {
				if (num[start] + num[end] == target) {
					vector<int> solution;
					solution.push_back(num[i]);
					solution.push_back(num[start]);
					solution.push_back(num[end]);
					result.push_back(solution);
					start++;
					end--;
					while (start < end && num[start] == num[start - 1])
						start++;
					while (start < end && num[end] == num[end + 1])
						end--;
				} else if (num[start] + num[end] < target) {
					start++;
				} else {
					end--;
				}
			}
			if (i < len - 1) {
				while (num[i] == num[i + 1])
					i++;
			}
		}
		return result;
	}

	int threeSumClosest(vector<int>& num, int target) {
		int result;
		int min_gap = INT_MAX;

		sort(num.begin(), num.end());
		for (auto a = num.begin(); a != prev(num.end(), 2); ++a) {
			auto b = next(a);
			auto c = prev(num.end());

			while (b < c) {
				const int sum = *a + *b + *c;
				const int gap = abs(sum - target);
				if (gap < min_gap) {
					result = sum;
					min_gap = gap;
				}
				if (sum < target)
					++b;
				else
					--c;
			}
		}

		return result;
	}

	int removeElement(int A[], int n, int elem) {
		int index = 0;
		for (int i = 0; i < n; ++i) {
			if (A[i] != elem) {
				A[index++] = A[i];
			}
		}
		return index;
	}

	bool isValidSudoku(const vector<vector<char>>& board) {
		bool used[9];
		for (int i = 0; i < 9; ++i) {
			fill(used, used + 9, false);
			for (int j = 0; j < 9; ++j)
				if (!check(board[i][j], used))
					return false;
			fill(used, used + 9, false);
			for (int j = 0; j < 9; ++j)
				if (!check(board[i][j], used))
					return false;
		}
		for (int r = 0; r < 3; ++r)
			for (int c = 0; c < 3; ++c) {
				fill(used, used + 9, false);
				for (int i = r * 3; i < r * 3 + 3; ++i)
					for (int j = c * 3; j < c * 3 + 3; ++j)
						if (!check(board[i][j], used))
							return false;
			}
		return true;
	}

	bool check(char ch, bool used[9]) {
		if (ch == '.')
			return true;
		if (used[ch - '1'])
			return false;
		return used[ch - '1'] = true;
	}

	int trap(int A[], int n) {
		int *max_left = new int[n]();
		int *max_right = new int[n]();

		for (int i = 1; i < n; i++) {
			max_left[i] = max(max_left[i - 1], A[i - 1]);
			max_right[n - 1 - i] = max(max_right[n - i], A[n - i]);
		}

		int sum = 0;
		for (int i = 0; i < n; i++) {
			int height = min(max_left[i], max_right[i]);
			if (height > A[i]) {
				sum += height - A[i];
			}
		}

		delete[] max_left;
		delete[] max_right;
		return sum;
	}

	void rotate(vector<vector<int>>& matrix) {
		const int n = matrix.size();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n - i; ++j)
				swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);

		for (int i = 0; i < n / 2; ++i)
			// 沿着水平中线反转
			for (int j = 0; j < n; ++j)
				swap(matrix[i][j], matrix[n - 1 - i][j]);
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
