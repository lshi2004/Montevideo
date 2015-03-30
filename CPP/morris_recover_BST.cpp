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
#include <map>

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

struct Interval {
	int start;
	int end;
	Interval() :
			start(0), end(0) {
	}
	Interval(int s, int e) :
			start(s), end(e) {
	}
};

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) :
			label(x) {
	}
	;
};

struct Point {
	int x;
	int y;
	Point() :
			x(0), y(0) {
	}
	Point(int a, int b) :
			x(a), y(b) {
	}
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
	// time exceeded ...


private:
    typedef string::const_iterator Iterator;
    map<tuple<Iterator, Iterator, Iterator>, bool> cache;



public:

	bool isScramble(string s1, string s2) {
		cache.clear();
		return isScramble(s1.begin(), s1.end(), s2.begin());
	}

	bool isScramble(Iterator first1, Iterator last1, Iterator first2) {
		auto length = distance(first1, last1);
		auto last2 = next(first2, length);

		if (length == 1) return *first1 == *first2;

		for (int i = 1; i < length; ++i) {
			if (( getOrUpdate(first1, first1 + i, first2)
					&& getOrUpdate(first1 + i, last1, first2 + i))
					|| (getOrUpdate(first1, first1 + i, last2 - i)
						&& getOrUpdate(first1 + i, last1, first2)) )
				return true;
		}

		return false;
	}

	bool getOrUpdate(Iterator first1, Iterator last1, Iterator first2) {
		auto key = make_tuple(first1, last1, first2);
		auto pos = cache.find(key);

		if (pos != cache.end())
			return pos->second;

		cache[key] = isScramble(first1, last1, first2);

		return cache[key];
	}


#endif





private:

	vector<int> preorderTraversal(TreeNode *root) {
		vector<int> result;
		TreeNode *cur, *prev;

		cur = root;
		while (cur != nullptr) {
			if (cur->left == nullptr) {
				result.push_back(cur->val);
				prev = cur;
				cur = cur->right;
			} else {
				// look for pre-node
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur)
					node = node->right;

				if (node->right == nullptr) {
					result.push_back(cur->val);
					node->right = cur;
					cur = cur->left;
				} else {
					node->right = nullptr;
					cur = cur->right;
				}
			}
		}

		return result;
	}




	 void recoverTree(TreeNode *root) {

		 pair<TreeNode*, TreeNode*> broken;
	     TreeNode* prev = nullptr;
	     TreeNode* cur = root;

	     while (cur != nullptr) {
	    	 if (cur->left == nullptr) {
	    		 detect(broken, prev, cur);
	    		 prev = cur;
	    		 cur = cur->right;
	    	 } else {
	    		 auto node = cur->left;
	    		 while (node->right != nullptr && node->right != cur)
	    			 node = node->right;

	    		 if (node->right == nullptr) {
	    			 node->right = cur;
	    			 cur = cur->left;
	    		 } else {
	    			 detect(broken, prev, cur);
	    			 node->right = nullptr;
	    			 prev = cur;
	    			 cur = cur->right;
	    		 }
	    	 }

	     }

	     swap(broken.first->val, broken.second->val);
	 }

	 void detect(pair<TreeNode*, TreeNode*>& broken, TreeNode* prev, TreeNode* cur)
	 {
		 if (prev != nullptr && prev->val > cur->val) {
			 if (broken.first == nullptr) {
				 broken.first = prev;
			 }
			 broken.second = cur;
		 }

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

	auto pp = new LRUCache(100);

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
