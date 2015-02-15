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

int main() {
	int *ptr = new int[10];
//	int **ary = new int*[100];

	ptr[0] = 1;
	ptr[1] = 2;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
