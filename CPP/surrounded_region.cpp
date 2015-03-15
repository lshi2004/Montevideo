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
    void solve(vector<vector<char>> &board) {
        if (board.empty()) return;

		 const int m = board.size();
		 const int n = board[0].size();

		 for (int i = 0; i < n; i++) {
			 bfs(board, 0, i);
			 bfs(board, m - 1, i);
		 }

		 for (int j = 1; j < m - 1; j++) {
			 bfs(board, j, 0);
			 bfs(board, j, n - 1);
		 }

		 for (int i = 0; i < m; i++)
			 for (int j = 0; j < n; j++)
				 if (board[i][j] == 'O')
					 board[i][j] = 'X';
				 else if (board[i][j] == '+')
					 board[i][j] = 'O';
	 }

	 void bfs(vector<vector<char>> &board, int i, int j) {
		 typedef pair<int, int> state_t;

		 queue<state_t> q;
		 const int m = board.size();
		 const int n = board[0].size();

		 auto is_valid = [&] (const state_t &s) {
			 const int x = s.first;
			 const int y = s.second;
			 if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				 return false;
			 return true;
		 };

		 auto state_extend = [&] (const state_t &s) {
			 vector<state_t> result;
			 const int x = s.first;
			 const int y = s.second;

			 const state_t new_states[4] = { {x - 1, y}, {x + 1, y} ,
					 {x, y - 1}, {x, y + 1}};

			 for (int k = 0; k < 4; ++k) {
				 if (is_valid(new_states[k])) {
					 board[new_states[k].first][new_states[k].second] = '+';
					 result.push_back(new_states[k]);
				 }
			 };

			 return result;
		 };

		 state_t start = {i, j};
		 if (is_valid(start)) {
			 board[i][j] = '+';
			 q.push(start);
		 }

		 while (!q.empty())	{
			 auto cur = q.front();
			 q.pop();
			 auto new_states = state_extend(cur);
			 for (auto s : new_states) q.push(s);
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

//	auto pp = new LRUCache(100);

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
