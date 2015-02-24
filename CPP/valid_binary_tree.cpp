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

	vector<TreeNode *> generateTrees(int n) {
		if (n == 0) return generate(1, 0);
		return generate(1, n);
	}

	vector<TreeNode *> generate(int start, int end) {
		vector<TreeNode *> result;
		if (start > end) {
			result.push_back(nullptr);
			return result;
		}
		for (int k = start; k <= end; k++) {
			vector<TreeNode *> left = generate(start, k-1);
			vector<TreeNode *> right = generate(k+1, end);
			for (auto i :left)
				for (auto j: right) {
					TreeNode *node = new TreeNode(k);
					node->left = i;
					node->right = j;
					result.push_back(node);
				}
		}
		return result;
	}

#define USER_SET_LEFT 0x1
#define USER_SET_RIGHT 0x2

    bool isValidBST(TreeNode *root) {
       return validateBST(root, INT_MIN, INT_MAX, 0);
	}

	bool validateBST(TreeNode* root, int lower, int upper, int level) {
		if (!root) return true;

		if (root->val < lower || root->val > upper) return false;


	    if ((root->val == lower && (level & USER_SET_LEFT)) ||
	           (root->val == upper && (level & USER_SET_RIGHT))) return false;


		return validateBST(root->left, lower, root->val, level | USER_SET_RIGHT) &&
				validateBST(root->right, root->val, upper, level | USER_SET_LEFT);
	}

};


void printPreOrder(TreeNode *root) {
	if (!root) return;
	cout << root->val << "\t" ;
	if (root->left) printPreOrder(root->left);
	if (root->right) printPreOrder(root->right);
}

void printInOrder(TreeNode *root) {
	if (!root) return;
	if (root->left) printPreOrder(root->left);
	cout << root->val << "\t" ;
	if (root->right) printPreOrder(root->right);
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
	vector<TreeNode*> tree = pp->generateTrees(3);


	cout << "the size is " << tree.size() << endl;

	for (auto & r : tree) {
		printInOrder(r);
		cout << endl;
	}


	TreeNode t1(1);
	TreeNode t2(1);

	t1.right = &t2;

	bool a = pp->isValidBST(&t1);

	cout << "the value is " << a << endl;



	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!


	return 0;
}
