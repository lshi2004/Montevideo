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

#if 0

1. Requirement details/timeline


The use case is IWAN support for SGT for the following technologies:
PfRv3 policies
Performance Monitor policies
QoS policies

The requirement is that SGT name be used in the configuration of SGT support in the policies.

 2. Technical Details
Make two APIs public to do SGT name and ID mapping.
When mapping changes, notification is needed.

the support of SG table download on S/T, esp. public API to map between SG name and tag. Are below the right ones? If yes, we need to make them public and have reg_invoke version for them since caller may not be built into all the same image set as CTS does.
char * cts_get_sgname_from_sgt (cts_sgt_tag_t sgt);
boolean cts_get_sgt_from_sgname (const char *sg_name_p, cts_sgt_t *sgt_p);

3. Setup info and configuration guide for ISE with CTS.
Any IOU (e.g. Standalone set up to test aaa download of SG table). I see there are commands “test cts aaa sg-table/sg-info”, but it seems we need some special procedures to get it working — trying on standalone device does not work.


-- Do not delete or change any of the text below this line --

WebEx information for your meeting scheduled on cisco.webex.com will be in this section after you save and send this invitation.
To preview the WebEx information, save the meeting.

#endif
