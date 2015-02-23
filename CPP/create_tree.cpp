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
	void connect(TreeLinkNode *root, TreeLinkNode *sibling) {
		if (!root)
			return;
		root->next = sibling;
		connect(root->left, root->right);
		connect(root->right, sibling ? sibling->left : nullptr);
	}

	void connect(TreeLinkNode *root) {
		connect(root, nullptr);
	}

	void connectII_R(TreeLinkNode *root) {
		if (root == nullptr)
			return;

		TreeLinkNode dummy(-1);
		for (TreeLinkNode *curr = root, *prev = &dummy; curr; curr =
				curr->next) {
			if (curr->left != nullptr) {
				prev->next = curr->left;
				prev = prev->next;
			}
			if (curr->right != nullptr) {
				prev->next = curr->right;
				prev = prev->next;
			}
		}
		connectII_R(dummy.next);
	}

#if 0

	if (root == nullptr) return;
	TreeLinkNode dummy(-1);
	for (TreeLinkNode *curr = root, *prev = &dummy;
			curr; curr = curr->next) {
		if (curr->left != nullptr) {
			prev->next = curr->left;
			prev = prev->next;
		}
		if (curr->right != nullptr) {
			prev->next = curr->right;
			prev = prev->next;
		}
	}
	connect(dummy.next);
#endif

	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {

		return createTree(preorder.begin(), preorder.end(), inorder.begin(),
				inorder.end());
	}

	template<typename InputIterator>
	TreeNode* createTree(InputIterator pre_first, InputIterator pre_last,
			InputIterator in_first, InputIterator in_last) {
		if (pre_first == pre_last)
			return nullptr;


		auto root = new TreeNode(*pre_first);

		auto in_pos = in_last;
		for (auto i = in_first; i != in_last; ++i)
			if (*i == *pre_first)
				in_pos = i;
		auto left_size = distance(in_first, in_pos);

		cout << "left size  " << left_size << endl;

		root->left = createTree(pre_first + 1, pre_first + left_size + 1,
				in_first, in_pos);


		root->right = createTree(pre_first + left_size + 1, pre_last,
				in_pos + 1, in_last);

		return root;
	}

};


void printPreOrder(TreeNode *root) {
	if (!root) return;
	cout << root->val << endl;
	if (root->left) printPreOrder(root->left);
	if (root->right) printPreOrder(root->right);
}

void printInOrder(TreeNode *root) {
	if (!root) return;
	if (root->left) printPreOrder(root->left);
	cout << root->val << endl;
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

	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	vector<int> v1{1, 2};
	vector<int> v2{2, 1};
	TreeNode *tn = pp->buildTree(v1, v2);

	cout << "In order sequences " << endl << endl;
	printInOrder(tn);
	cout << "Pre order sequences " << endl << endl;
	printPreOrder(tn);

	return 0;
}
