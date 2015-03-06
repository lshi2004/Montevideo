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

bool int_sort_function_old(int i, int j) {
	string s1 = to_string(i);
	string s2 = to_string(j);
	int k1, k2;

	for (k1 = 0, k2 = 0; k1 < s1.size() && k2 < s2.size(); k1++, k2++) {
		if (s1[k1] != s2[k2]) {
			return s1[k1] < s2[k2];
		}
	}

	return (k1 >= s1.size());
}

bool int_sort_function(int i, int j) {
	string s1 = to_string(i);
	string s2 = to_string(j);
	return s1 + s2 < s2 + s1;
}

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
	bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.length();
		int n2 = s2.length();
		int n3 = s3.length();

		if (n3 != n1 + n2) return false;

		vector<vector<bool>> f(s1.length() + 1, vector<bool>
					(s2.length() + 1, true));

		for (size_t i = 1; i <= n1; i++)
			f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];

		for (size_t i = 1; i <= n2; i++)
			f[0][i] = f[0][i-1] && s2[i -1 ] == s3[i - 1];

		for (size_t i = 1; i <= n1; i++)
			for (size_t j = 1; j <= n2; j++)
				f[i][j] = (s1[i-1] == s3[i+j-1] && f[i-1][j])
					|| (s2[j-1] == s3[i+j-1] && f[i][j-1]);

		return f[n1][n2];
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
void reverse_array(int nums[], int s, int e) {
	while (s < e) {
		int tmp = nums[s];
		nums[s] = nums[e];
		nums[e] = tmp;
		s++;
		e--;
	}
}

void rotate(int nums[], int n, int k) {
	if (k <= 0)
		return;
	k = k % n;
	reverse_array(nums, 0, n - 1);
	reverse_array(nums, 0, k - 1);
	reverse_array(nums, k, n - 1);

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

//	auto pp = new LRUCache(100);

#if 0
	auto result = pp->partitionN("a");
	for (auto i: result) {
		for (auto j: i)
		cout << j << "\t";
		cout << endl << "one more result " << endl << endl;
	}
#endif

	string s1 = "1.0";
	string s2 = "1.1";

	cout << endl << endl << endl;
	string ts1 = "aa";

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
