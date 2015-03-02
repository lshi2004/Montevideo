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
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if (n <= 1)
			return 0;
		vector<int> left(n, 0);
		vector<int> right(n, 0);

		int left_profit = 0;
		int right_profit = 0;

		int small = prices[0];
		for (int i = 1; i < n; i++) {
			small = min(small, prices[i]);
			left[i] = max(left[i - 1], prices[i] -small);
		}

		int large = prices[n - 1];
		for (int i = n - 2; i >= 0; i--) {
			large = max(large, prices[i]);
			right[i] = max(right[i+1], large - prices[i]);
		}

		int max_profit = 0;
		for (int i = 0; i < n; i++) {
			max_profit = max(max_profit, left[i] + right[i]);
		}

		return max_profit;
	}

	int maxProfit2(vector<int> &prices) {
		int n = prices.size();
		if (n <= 1)
			return 0;

		int diff;
		int profit = 0;
		for (int i = 1; i < n; i++) {
			diff = prices[i] - prices[i - 1];
			if (diff > 0)
				profit += diff;
		}
		return profit;
	}

	int maxProfit1(vector<int> &prices) {
		int n = prices.size();
		if (n <= 1)
			return 0;

		int profit = 0;
		int small = prices[0];

		for (int i = 1; i < n; i++) {
			small = min(small, prices[i]);
			profit = max(profit, prices[i] - small);
		}
		return profit;
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

//	auto pp = new LRUCache(100);

	int kk = INT_MIN;
	cout << "the integer min is " << kk << endl;
	cout << "the integer reversed is " << abs(kk) << endl;

	kk = INT_MAX;
	cout << "the integer max is " << kk << endl;

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
