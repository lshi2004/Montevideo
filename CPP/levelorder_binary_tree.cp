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
	vector<vector<int> > levelOrderR(TreeNode *root) {
		vector<vector<int>> result;
		traverseR(root, 0, result);
		return result;
	}

	void traverseR(TreeNode *root, int level, vector<vector<int>> & result) {
		if (!root)
			return;

		if (level >= result.size())
			result.push_back(vector<int>());

		result[level].push_back(root->val);
		traverseR(root->left, level + 1, result);
		traverseR(root->right, level + 1, result);
	}

	vector<vector<int> > levelOrderI(TreeNode *root) {
		vector<vector<int>> result;
		if (!root)
			return result;

		queue<TreeNode *> current, next;
		vector<int> level;

		current.push(root);
		while (!current.empty()) {
			while (!current.empty()) {
				TreeNode *node = current.front();
				current.pop();
				level.push_back(node->val);
				if (node->left)
					next.push(node->left);
				if (node->right)
					next.push(node->right);
			}
			result.push_back(level);
			level.clear();
			swap(next, current);
		}
		return result;
	}

//////////////////////////////////////////////////////////////////
	vector<vector<int> > levelOrderBottomR(TreeNode *root) {
		vector<vector<int>> result;
		traverseR(root, 1, result);
		reverse(result.begin(), result.end()); // 比上一题多此一行
		return result;
	}
	vector<vector<int> > levelOrderBottomI(TreeNode *root) {

		vector<vector<int>> result;
		if (!root)
			return result;

		queue<TreeNode *> current, next;
		vector<int> level;

		current.push(root);
		while (!current.empty()) {
			while (!current.empty()) {
				TreeNode *node = current.front();
				current.pop();
				level.push_back(node->val);
				if (node->left)
					next.push(node->left);
				if (node->right)
					next.push(node->right);
			}
			result.push_back(level);
			level.clear();
			swap(next, current);
		}
		reverse(result.begin(), result.end());
		return result;
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

	// auto pp = new LRUCache(100);

	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
