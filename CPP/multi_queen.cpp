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
#include <numeric>
#include <list>
#include <unordered_map>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) :
			label(x), next(NULL), random(NULL) {
	}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) :
			val(x), left(NULL), right(NULL), next(NULL) {
	}
};

class lengthSolution {
private:
};

class LRUCache {
private:
	struct CacheNode {
		int key;
		int value;
		CacheNode(int k, int v) :
				key(k), value(v) {
		}
	};

	list<CacheNode> cacheList;
	unordered_map<int, list<CacheNode>::iterator> cacheMap;
	int capacity;

public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	int get(int key) {
		if (cacheMap.find(key) == cacheMap.end())
			return -1;
		cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
		cacheMap[key] = cacheList.begin();
		return cacheMap[key]->value;
	}

	void set(int key, int value) {
		//unordered_map<int, list<CacheNode>::iterator>::const_iterator it;
		auto it = cacheMap.find(key);

		if (it == cacheMap.end()) {
			if (cacheList.size() == capacity) {
				cacheMap.erase(cacheList.back().key);
				cacheList.pop_back();
			}
			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();
		} else {
			cacheList.erase(cacheMap[key]);
			//	cacheList.erase(it->second);
			cacheMap.erase(key);

			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();

		}
	}

public:
	int uniquePaths(int m, int n) {
		red = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
		return dfs(m, n);
	}

	int dfs(int x, int y)  {
		if (x < 1 || y < 1) return 0;
		if (x == 1 && y == 1) return 1;

		return getUpdate(x - 1, y) + getUpdate(x, y - 1);
	}

	int getUpdate(int x, int y) {
		if (red[x][y] == 0) {
			red[x][y] = dfs(x, y);
		}

		return red[x][y];
	}

	// f[i][j] = f[i-1][j] + f[i][j-1]
	int uniquePathsD(int m, int n) {
		vector<int> f(n, 0);
		f[0] = 1;
		for (int i = 0; i < m; i++) {
			for (int j = 1; j < n; j++) {
				f[j] = f[j - 1] + f[j];
			}
		}

		return f[n - 1];
	}

private:
	vector<vector<int>> red;



};


class multipleQueens {
public:
    vector<vector<string>> solveQueens(int n) {
        this->columns = vector<int>(n, 0);
        this->mdiag = vector<int>(2 * n, 0);
        this->adiag = vector<int>(2 * n, 0);

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
                    if (j == C[i])
                        s[j] = 'Q';
                }
                //cout << __FUNCTION__<<"   " << s<<endl;
                solution.push_back(s);
            }
            result.push_back(solution);
            return;
        }

        for (int j = 0; j < N; ++j) {
            const bool ok = columns[j] == 0 && mdiag[row + j] == 0
                    && adiag[row - j + N] == 0;
            if (!ok)
                continue;
            C[row] = j;
            columns[j] = mdiag[row + j] = adiag[row - j + N] = 1;
             dfs(C, result, row + 1);
             columns[j] = mdiag[row + j] = adiag[row - j + N] = 0;
         }

     }

 };


void printPreOrder(TreeNode *root) {
	if (!root)
		return;
	cout << root->val << "\t";
	if (root->left)
		printPreOrder(root->left);
	if (root->right)
		printPreOrder(root->right);
}

void printInOrder(TreeNode *root) {
	if (!root)
		return;
	if (root->left)
		printPreOrder(root->left);
	cout << root->val << "\t";
	if (root->right)
		printPreOrder(root->right);
}

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

	auto pp = new LRUCache(100);

#if 0
	auto result = pp->partitionN("a");


	for (auto i: result) {
		for (auto j: i)
		cout << j << "\t";
		cout << endl << "one more result " << endl << endl;
	}
#endif

	cout << endl << endl << endl;
	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
