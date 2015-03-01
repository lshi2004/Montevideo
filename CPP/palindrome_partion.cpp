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
	vector<vector<string>> partition(string s) {
		vector<vector<string>> result;
		vector<string> path;

		dfs(s, path, result, 0, 1);
		return result;
	}

	void dfs(string &s, vector<string> &path,
			vector<vector<string>> &result, size_t prev,
			size_t start) {
		if (start == s.size()) {
			if (isPalindrome(s, prev, start-1)) {
				path.push_back(s.substr(prev, start - prev));
				result.push_back(path);
				path.pop_back();
			}
			return;
		}
		dfs(s, path, result, prev, start + 1);
		if (isPalindrome(s, prev, start-1)) {
			path.push_back(s.substr(prev, start - prev));
			dfs(s, path, result, start, start + 1);
			path.pop_back();
		}
	}

	bool isPalindrome(const string &s, int start, int end) {
		while (start < end && s[start] == s[end]) {
			start++;
			end--;
		}
		return start >= end;
	}


	vector<vector<string>> partitionN(string s) {
		vector<vector<string>> result;
		vector<string> path;
		DFS(s, path, result, 0);
		return result;
	}

	void DFS(string & s, vector<string> &path,
			vector<vector<string>> result, int start) {
		if (start == s.size()) {
			result.push_back(path);
			return;
		}

		for (int i = start; i < s.size(); i++) {
			if (isPalindrome(s, start, i)) {
				path.push_back(s.substr(start, i - start + 1));
				DFS(s, path, result, i+1);
				path.pop_back();
			}
		}

	}

	vector<vector<string>> partitionD(string s) {
		const int n = s.size();
		bool p[n][n];
		fill_n(&p[0][0], n*n, false);

		for (int i = n -1; i >= 0; --i)
			for (int j = i; j < n; ++j)
				p[i][j] = s[i] == s[j]	&& ((j - i < 2) || p[i+1][j-1]);

		vector<vector<vector<string>>> sub_palins(n);

		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j)
				if (p[i][j]) {
					const string palindrome = s.substr(i, j - i + 1);
					if (j + 1 < n) {
						for (auto v : sub_palins[j + 1]) {
							v.insert(v.begin(), palindrome);
							sub_palins[i].push_back(v);
						}
					} else {
						sub_palins[i].push_back(vector<string>{palindrome});
					}
				}
		}

		return sub_palins[0];

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
	auto result = pp->partitionN("a");


	for (auto i: result) {
		for (auto j: i)
		cout << j << "\t";
		cout << endl << "one more result " << endl << endl;
	}

	cout << endl << endl << endl;
	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
