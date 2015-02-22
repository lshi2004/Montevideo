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

	int lengthOfLastWord(const char *s) {

		string t(s);
		auto first = t.rbegin();

		while (first != t.rend() && !isalpha(*first) )
			++first;



		cout << "first now is " << distance(first, t.rbegin()) <<endl;

		auto last = first;
		while (last != t.rend() && isalpha(*last))
			++last;

		cout << "last now is " << distance(last, t.rbegin()) <<endl;

		return distance(first, last);

#if 0

		const string str(s);
		auto first = find_if(str.rbegin(), str.rend(), ::isalpha);
		cout << "first now is " << distance(first, str.rbegin()) <<endl;
		auto last = find_if_not(first, str.rend(), ::isalpha);
		cout << "last now is " << distance(last, str.rbegin()) <<endl;

		return distance(first, last);
#endif

	}

	int lengthOfLastWordNew(const char *s) {
		if (s == nullptr)
			return 0;
		int len = 0;

		while (*s) {
			if (*s != ' ') {
				len++;
			} else {
				if (*(s + 1) && *(s + 1) != ' ')
					len = 0;
			}
			s++;
		}
		return len;
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

	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	int ssl = pp->lengthOfLastWord("        ");
	cout << "length is " << ssl << endl ;
	return 0;
}
