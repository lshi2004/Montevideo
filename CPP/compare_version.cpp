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

int compareVersion(string version1, string version2) {
	size_t t1 = version1.find(".");
	size_t t2 = version2.find(".");

	int i1_first = atoi(version1.substr(0, t1).c_str());
	int i1_last =
			t1 == string::npos ? 0 : atoi(version1.substr(t1 + 1).c_str());
	//cout << "left of 1: " << version1.substr(t1+1)<<endl;

	int i2_first = atoi(version2.substr(0, t2).c_str());
	int i2_last =
			t2 == string::npos ? 0 : atoi(version2.substr(t2 + 1).c_str());

	//cout << "num 1: " << i1_first << "\t " << i1_last<<endl;
	//cout << "num 2: " << i2_first << "\t " << i2_last<<endl;

	if (i1_first < i2_first)
		return -1;
	else if (i1_first > i2_first)
		return 1;
	else {
		if (i1_last < i2_last)
			return -1;
		else if (i1_last > i2_last)
			return 1;
		else
			return 0;
	}
}

int compareVersion2(string version1, string version2) {
	int sum1, sum2;
	int size1 = version1.size();
	int size2 = version2.size();

	for (int i = 0, j = 0; i < size1 || j < size2; i++, j++) {
		sum1 = 0;
		while (i < size1 && version1[i] != '.') {
			sum1 = sum1 * 10 + (version1[i] - '0');
			++i;
		}
		sum2 = 0;
		while (j < size2 && version2[j] != '.') {
			sum2 = sum2 * 10 + (version2[j] - '0');
			++j;
		}
		if (sum1 > sum2) return 1;
		if (sum1 < sum2) return -1;
	}

	return 0;
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
	int kkk = compareVersion(s1, s2);

	cout << endl << endl << endl;
	string ts1 = "aa";
	cout << "size of aa is " << kkk << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}

#
