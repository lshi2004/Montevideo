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

	bool isPalindrome(string s) {
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		auto left = s.begin();
		auto right = prev(s.end());

		while (left < right) {
			if (!::isalnum(*left))
				++left;
			else if (!::isalnum(*right))
				--right;
			else if (*left != *right)
				return false;
			else {
				left++;
				right--;
			}
		}

		return true;
	}

public:
	vector<string> anagrams(vector<string> &strs) {
		unordered_map<string, vector<string>> group;
		for (const auto &s : strs) {
			string key = s;
			sort(key.begin(), key.end());
			group[key].push_back(s);
		}

		vector<string> result;
		for (auto it = group.cbegin(); it != group.cend(); ++it) {
			if (it->second.size() > 1) {
				result.insert(result.end(), it->second.begin(),
						it->second.end());
			}
		}
		return result;
	}
public:
	int largestRectangleArea(vector<int> &height) {
		stack<int> s;
		int result = 0;

		//cover last element in the vector
		height.push_back(0);
		for (int i = 0; i < height.size(); ) {
			if (s.empty() || height[i] > height[s.top()])
				s.push(i++);
			else {
				int tmp = s.top();
				s.pop();
				result = max(result, height[tmp] * (s.empty() ? i : i - s.top() -1));
			}
		}
		return result;
	}

	// 0   		1  		2
	// 10 		20 		15
	// i = 0, push 0 for 10, stack is (0)
	// i = 1, push 1 for 20, stack is (0, 1)
	// i = 2, handling 15
	//     pop (1) and get 20 for tmp, stack is not empty (0)
	//     tmp = 1, 20, s.top() now is 0
	//        result = max (0, 20 * (2-0-1)) = 20
	// i = 2, handling 15 again
	//

	// 0    1	2
	//40  	20  15

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

	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
