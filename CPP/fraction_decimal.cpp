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

	string num2str(long a) {
		if (a < 0) {
			a = -a;
		}
		ostringstream os;
		os << a;
		return os.str();
	}

	string fractionToDecimal(int numerator, int denominator) {
		if (numerator == 0 || denominator == 0) {
			return "0";
		}
		bool pos = true;
		if ((numerator < 0 && denominator > 0)
				|| (numerator > 0 && denominator < 0)) {
			pos = false;
		}

		long numer = abs(numerator);
		long denom = abs(denominator);

		int l = -1;
		vector<string> res;
		int maxlen = 1000;
		vector<string> mod;

		while (mod.size() < maxlen) {
			res.push_back(num2str(numer / denom));
			long m = numer % denom;
			if (m == 0) {
				break;
			}

			for (int i = 0; i < mod.size(); i++) {
				if (mod[i] == num2str(m)) {
					l = i;
					break;
				}
			}

			if (l == -1) {
				mod.push_back(num2str(m));
				numer = m * 10;
			} else {
				break;
			}
		}

		string r = "";

		if (res.size() == 1) {
			r = res[0];
		} else {
			r = res[0] + ".";
			for (int i = 1; i < res.size(); i++) {
				if (i == l + 1) {
					r += "(";
				}
				r += res[i];
			}
			if (l != -1) {
				r += ")";
			}
		}

		if (pos) {
			return r;
		} else {
			return "-" + r;
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

	string s1 = "1.0";
	string s2 = "1.1";

	string ts1 = "aa";

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
