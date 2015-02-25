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

#if 0

	int list_length(ListNode *node) {
		int n = 0;

		while (node) {
			++n;
			node = node->next;
		}
		return n;
	}

	ListNode *nth_node (ListNode *node, int n) {
		while (--n)
			node = node->next;
		return node;

	}

	TreeNode* sortedListToBST(ListNode *head, int len)	{
		if (len == 0) return nullptr;
		if (len == 1) return new TreeNode(head->val);

		ListNode *p = nth_node(head, len/2 + 1);
		TreeNode *root = new TreeNode(p->val);
		root->left = sortedListToBST(head, len/2);
		root->right = !p->next ? nullptr : sortedListToBST(p->next, (len-1)/2 );
		return root;
	}


	TreeNode* sortedListBST(ListNode* head){
		return sortedListToBST(head, list_length(head));
	}

	//odd number 2p+1
	//	p     ~p    p
	//even number 2p
	//  p     ~p    p-1
#endif
	 TreeNode *sortedListToBST(ListNode *head) {
		int len = 0;

		ListNode *p = head;
		while(p) {
			len++;
			p = p->next;
		}
		return sortedListToBST(head, 0, len -1);
	}

	TreeNode* sortedListToBST(ListNode*& list, int start, int end) {
		if (start > end) return nullptr;

		int mid = start + (end - start) / 2;
		TreeNode *left = sortedListToBST(list, start, mid - 1);
		TreeNode *parent = new TreeNode(list->val);
		parent->left = left;
		list = list->next;
		parent->right = sortedListToBST(list, mid + 1, end);
		return parent;
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

	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
