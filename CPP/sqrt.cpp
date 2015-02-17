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


class RobotSolution {
public:
	int uniquePaths(int m, int n) {
		this->f = vector<vector<int>>(m+1, vector<int>(n+1, 0));
		return dfs(m, n);
	}

	int pathObstacles(vector<vector<int>> &grid) {
		const int m = grid.size();
		const int n = grid[0].size();
		this->f = vector<vector<int>>(m+1, vector<int>(n+1, 0));
		return dfsObstacles(m, n, grid);
	}

	int pathTwo(int m, int n) {
		vector<int> ff(n, 0);
		ff[0] = 1;

		for (int i = 0; i < m; i++) {
			for (int j = 1; j < n; j++) {
				ff[j] = ff[j-1] + ff[j];
			}
		}
		return ff[n-1];
	}
private:
	vector<vector<int>> f; //cache

	int dfs(int x, int y) {
		if (x < 1 || y < 1) return 0;

		if (x == 1 && y == 1) return 1;

		return getOrUpdate(x - 1, y) + getOrUpdate(x, y-1);
	}

	int getOrUpdate(int x, int y) {
		if (f[x][y] > 0)
			return f[x][y];
		else
			return f[x][y] = dfs(x, y);
	}

	int dfsObstacles(int x, int y, vector<vector<int>> &grid) {
		if (x < 1 || y < 1)
			return 0;

		if (grid[x-1][y-1])
			return 0;

		if (x == 1 && y == 1)
			return 1;

		return getOrUpdateObstacles(x - 1, y, grid)
				+ getOrUpdateObstacles(x, y - 1, grid);
	}

	int getOrUpdateObstacles(int x, int y, vector<vector<int>> &grid) {
		if (f[x][y] > 0)
			return f[x][y];
		else
			return f[x][y] = dfsObstacles(x, y, grid);
	}

};

class multipleQueens {
public:
	vector<vector<string>> solveQueens(int n) {
		this->columns = vector<int>(n, 0);
		this->mdiag = vector<int>(2*n, 0);
		this->adiag = vector<int>(2*n, 0);

		vector<vector<string>> result;
		vector<int> C(n, 0); //C[i] is the column number of queen
		dfs(C, result, 0);
		return result;
	}

private:
	vector<int> columns;
	vector<int> mdiag;
	vector<int> adiag;

	void dfs(vector<int> &C, vector<vector<string>> &result, int row) {
		const int N = C.size();
		if (row == N) {
			//save the results
			vector<string> solution;
			for (int i = 0; i < N; ++i) {
				string s(N, '.');
				for (int j = 0; j < N; ++j) {
					if (j == C[i]) s[j] = 'Q';
				}
				//cout << __FUNCTION__<<"   " << s<<endl;
				solution.push_back(s);
			}
			result.push_back(solution);
			return;
		}

		for (int j = 0; j < N; ++j) {
			const bool ok = columns[j] == 0 && mdiag[row +j]  == 0 &&
					adiag[row -j + N] == 0;
			if (!ok) continue;
			C[row] = j;
			columns[j] = mdiag[row +j] = adiag[row -j + N] = 1;
			dfs(C, result, row + 1);
			columns[j] = mdiag[row +j] = adiag[row -j + N] = 0;
		}

	}


};


class lengthSolution {
public:
	int lengthOfLastWord(const char *s)  {
		if (s == nullptr) return 0;
		int len = 0;

		while (*s) {
			if (*s != ' ') {
				len++;
			} else {
				if (*(s+1) && *(s+1) != ' ')
					len = 0;
			}
			s++;
		}
		return len;
	}

	string countAndSay(int n) {
	    string s("1");

	    while (--n > 0)	 {
	    	s = getNextString(s);
	    }
	    return s;
	}

	bool validParentheses(string const & s) {
		string left = "{([";
		string right = "}])";
		stack<char> stk;

		for (char c : s) {

			if (left.find(c) != string::npos) {
				stk.push(c);
			} else {
				if (stk.empty()) return false;
				if (right.find(c) == string::npos) return false;
				if (stk.top() != left[right.find(c)]) return false;
				stk.pop();
			}
		}
		return stk.empty();

	}



public:
	int mySqrt(int n) {
		if (n < 0) return -1;
		if (n < 2) return n;
		int low, high, mid, last_mid;
		low = 1;
		high = n / 2;

		while (low < high) {
			mid = low + (high - low) / 2;
			int r = n / mid;
			if (r == mid) return mid;
			else if (r < mid) {
				high = mid - 1;
			} else {
				low = mid + 1;
				last_mid = mid;
			}
		}

		return last_mid;

	}


private:
	string getNextString(const string &s) {
		stringstream ss;

		for (auto i = s.begin(); i != s.end(); ) {
			auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
			ss << distance(i, j) << *i;
			i = j;
		}
		return ss.str();
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

	for (auto i : result)  {
		for (auto j: i) {
			cout << j << " \t";
		}
		cout << endl <<endl  <<endl;
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
