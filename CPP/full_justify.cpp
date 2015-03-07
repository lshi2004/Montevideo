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
	vector<string> fullJustify(vector<string> &words, int L) {

		vector<string> result;

		const int n = words.size();

		if (n == 0 || L == 0) {
			result.push_back("");
			return result;
		}

		if (words[0].size() == 0) {
			string ss;
			ss.append(L, ' ');
			result.push_back(ss);
			return result;
		}

		int begin = 0, len = 0;
		for (int i = 0; i < n; ++i) {
			if (len + words[i].size() + (i - begin) > L) {
				cout << "push back 1 " << i << "and " << begin << endl;
				result.push_back(connect(words, begin, i - 1, len, L, false));
				begin = i;
				len = 0;
			}
			len += words[i].size();
		}

		result.push_back(connect(words, begin, n - 1, len, L, true));
		return result;
	}

	string connect(vector<string> &words, int begin, int end, int len, int L,
			bool is_last) {
		string s;

		int n = end - begin + 1;
		for (int i = 0; i < n; ++i) {
			s += words[begin + i];
			add_space(s, i, n - 1, L - len, is_last);
		}

		if (s.size() < L)
			s.append(L - s.size(), ' ');
		return s;
	}

	void add_space(string &s, int i, int n, int L, bool is_last) {
		if (n < 1 || i > n - 1)
			return;

		int spaces = is_last ? 1 : (L / n + (i < (L % n) ? 1 : 0));
		s.append(spaces, ' ');
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

#if 0
	auto result = pp->partitionN("a");
	for (auto i: result) {
		for (auto j: i)
		cout << j << "\t";
		cout << endl << "one more result " << endl << endl;
	}
#endif
	vector<string> t1;
	t1.push_back("a");
	t1.push_back("b");
	t1.push_back("c");
	t1.push_back("d");
	t1.push_back("e");

	auto r1 = pp->fullJustify(t1, 1);

	cout << "before " << endl;

	for (auto j : r1)
		cout << j << "\n" << endl;

	cout << "after " << endl;

	string s1 = "1.0";
	string s2 = "1.1";

	string ts1 = "aa";

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
