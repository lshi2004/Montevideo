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

	int atoi(string str) {
		int num = 0;
		int sign = 1;
		const char *c_str = str.c_str();

		const int n = strlen(c_str);
		int i = 0;

		while (c_str[i] == ' ' && i < n)
			i++;

		if (c_str[i] == '+')
			i++;
		else if (c_str[i] == '-') {
			sign = -1;
			i++;
		}

		while (c_str[i]) {
			char c = c_str[i];
			if (!isdigit(c))
				return sign * num;
			if ((num > INT_MAX / 10)
					|| (num == INT_MAX / 10 && (c - '0') > (INT_MAX % 10))) {
				return sign == -1 ? INT_MIN : INT_MAX;
			}
			num = num * 10 + c - '0';
			i++;
		}

		return sign * num;
	}

	string addBinary(string a, string b) {
		string result;
		int carry = 0, ai, bi, val;
		for (auto ia = a.rbegin(), ib = b.rbegin();
				ia != a.rend() || ib != b.rend();) {
			ai = ia == a.rend() ? 0 : (*ia - '0');
			bi = ib == b.rend() ? 0 : (*ib - '0');
			val = (ai + bi + carry) % 2;
			carry = (ai + bi + carry) / 2;

			result.insert(result.begin(), val + '0');
			if (ia != a.rend())
				++ia;
			if (ib != b.rend())
				++ib;

		}

		if (carry)
			result.insert(result.begin(), '1');

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
	string s = pp->addBinary("11", "1");

	ListNode np(1);
//	ListNode *pn = pp->removeNthFromEnd(&np, 1);

	int k1 = 0;
	cout << "hello" << k1 << "  ABC "<< s << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
