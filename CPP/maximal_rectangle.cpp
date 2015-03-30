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

	int maximalRectangal2(vector<vector<char>> &matrix) {

		if (matrix.empty()) return 0;
		const int m = matrix.size();
		const int n = matrix[0].size();

		vector<int> H(n, 0);
		vector<int> L(n, 0);
		vector<int>	R(n, n);

		int ret = 0;
		for (int i = 0; i < m; ++i) {
			int left = 0, right = n;
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					++H[j];
					L[j] = max(L[j], left);
				} else {
					left = j + 1;
					H[j] = 0; L[j] = 0; R[j] = n;
				}
			}

			for (int j = n - 1; j >= 0; --j) {
				if (matrix[i][j] == '1') {
					R[j] = min(R[j], right);
					ret = max(ret, H[j]*(R[j]-L[j]));
				} else {
					right = j;
				}
			}
		}

		return ret;
	}

	int maximalRectangal(vector<vector<char>> &matrix) {
		int row = matrix.size();
		if (row == 0) return 0;
		int result = 0;
		int col = matrix[0].size();

		vector<vector<int>> ones(row, vector<int>(col, 0));

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (matrix[i][j] == '1') {
					if (j == 0) ones[i][j] = 1;
					else ones[i][j] = ones[i][j-1] + 1;
				}
			}
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (ones[i][j] != 0) {
					int h = i - 1;
					int tmp_area = ones[i][j];
					int mini_width = ones[i][j];

					while (h >= 0) {
						if (ones[h][j] == 0) {
							break;
						} else {
							if (ones[h][j] < mini_width) {
								mini_width = ones[h][j];
							}
							if (tmp_area < mini_width * (i - h + 1)) {
								tmp_area = mini_width * (i - h + 1);
							}
							h--;
						}
					}
					if (result < tmp_area) {
						result = tmp_area;
					}

				}
			}
		}


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
