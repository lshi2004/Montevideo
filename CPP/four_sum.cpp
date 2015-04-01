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

	vector<vector<int> > fourSum2(vector<int> &num, int target) {
		vector<vector<int>> result;
		if (num.size() < 4)
			return result;

		sort(num.begin(), num.end());
		unordered_map<int, vector<pair<int, int> > > cache;

		for (size_t a = 0; a < num.size(); ++a) {
			for (size_t b = a + 1; b < num.size(); ++b) {
				cache[num[a] + num[b]].push_back(pair<int, int>(a, b));
			}
		}

		for (int c = 0; c < num.size(); ++c) {
			for (size_t d = c + 1; d < num.size(); ++d) {
				const int key = target - num[c] - num[d];
				if (cache.find(key) == cache.end())
					continue;
				const auto& vec = cache[key];
				for (size_t k = 0; k < vec.size(); ++k) {
					if (c <= vec[k].second)
						continue; // 有重叠
					result.push_back( { num[vec[k].first], num[vec[k].second],
							num[c], num[d] });
				}
			}
		}

		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}

	vector<vector<int> > fourSum(vector<int> &num, int target) {
		vector<vector<int>> result;

		if (num.size() < 4)
			return result;
		sort(num.begin(), num.end());

		unordered_map<int, vector<pair<int, int>>> cache;
		for (size_t a = 0; a < num.size(); ++a) {
			for (size_t b = a + 1; b < num.size(); ++b) {
				cache[num[a] + num[b]].push_back(pair<int, int>(a, b));
			}
		}

		for (size_t c = 0; c < num.size(); ++c) {
			for (size_t d = c + 1; d < num.size(); ++d) {
				const int key = target - num[c] - num[d];

				if (cache.find(key) == cache.end())
					continue;
				const auto & vec = cache[key];

				for (size_t k = 0; k < vec.size(); ++k) {

					if (c <= vec[k].second)
						continue;
					result.push_back( { num[vec[k].first], num[vec[k].second],
							num[c], num[d] });
				}
			}
		}

		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()));

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

	auto pp = new LRUCache(100);

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
