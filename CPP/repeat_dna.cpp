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

	vector<string> findRepeatedDnaSequences(string s) {
		vector<string> out;
		if (s.size() < 10)
			return out;

		unordered_map<int, int> map;

		string temps = s.substr(0, 10);
		int temphash = stringHash(temps);

		map[temphash]++;

		for (int i = 10; i < s.size(); i++) {
			int newhash = updateHash(s, temphash, i);
			//string temps = s.substr(i - 9, 10);
			//int newhash = stringHash(temps);
			map[newhash]++;
			temphash = newhash;
		}

		for (auto it = map.begin(); it != map.end(); it++) {
			if (it->second > 1) {
				string outstring = hashToStr(it->first);
				out.push_back(outstring);
			}
		}

		return out;

	}

	int stringHash(string &s) {
		// s.size() == 10;
		int out = 0;
		for (int i = 0; i < 10; i++) {
			char c = s[i];
			if (c == 'C') {
				out |= 1;
			} else if (c == 'G') {
				out |= 2;
			} else if (c == 'T') {
				out |= 3;
			}

			out <<= 2;
		}

		out >>= 2;

		return out;
	}

	int updateHash(string &s, int oldhash, int newi) {
		int mask = ~(3 << 18);
		oldhash &= mask;
		oldhash <<= 2;

		char newc = s[newi];
		if (newc == 'C')
			oldhash |= 1;
		else if (newc == 'G')
			oldhash |= 2;
		else if (newc == 'T')
			oldhash |= 3;

		return oldhash;
	}

	string hashToStr(int hash) {
		string out = "";

		int mask = 3;
		for (int i = 0; i < 10; i++) {
			int twodigit = hash & mask;
			if (twodigit == 0) {
				out = 'A' + out;
			} else if (twodigit == 1) {
				out = 'C' + out;
			} else if (twodigit == 2) {
				out = 'G' + out;
			} else {
				out = 'T' + out;
			}

			hash >>= 2;
		}

		return out;
	}

};

//time exceeds

bool isMatch(const char *s, const char *p) {
	if (*p == '*') {
		while (*p == '*')
			++p;
		if (*p == '\0')
			return true;

		while (*s != '\0' && !isMatch(s, p))
			++s;
		return *s != '\0';
	} else if (*p == '\0' || *s == '\0')
		return *p == *s;
	else if (*p == *s || *p == '?')
		return isMatch(++s, ++p);
	else
		return false;

}

bool isMatch2(const char *s, const char *p) {
	bool star = false;
	const char *str, *ptr;
	for (str = s, ptr = p; *str != '\0'; str++, ptr++) {
		switch (*ptr) {
		case '?':
			break;
		case '*':
			star = true;
			s = str, p = ptr;
			while (*p == '*')
				p++;  //skip continuous '*'
			if (*p == '\0')
				return true;
			str = s - 1;
			ptr = p - 1;
			break;
		default:
			if (*str != *ptr) {
				if (!star)
					return false;
				s++;
				str = s - 1;
				ptr = p - 1;
			}
		}
	}
	while (*ptr == '*')
		ptr++;
	return (*ptr == '\0');

}

int hammingWeight(uint32_t n) {

	int sum = 0;
	for (int i = 0; i < sizeof(uint32_t) * 8; ++i) {
		if (n & 1)
			sum++;
		n = n >> 1;
	}
	return sum;
}

vector<string> findRepeatedDnaSequences(string s) {
	vector<string> result;
	unordered_map<string, int> mapping;

	for (int i = 0; i + 10 < s.size(); ++i) {
		string s1 = s.substr(i, 10);
		if (mapping.find(s1) != mapping.end()) {
			mapping[s1]++;
		} else {
			mapping[s1] = 1;
		}
	}

	for (auto& j : mapping) {
		if (j.second > 1) {
			result.push_back(j.first);
		}
	}

	return result;
}

string convert(string s, int nRows) {
	if (nRows <= 1 || s.size() <= 1)
		return s;
	string result;

	for (int i = 0; i < nRows; i++)
		for (int j = 0, index = i; index < s.size();
				j++, index = (2 * nRows - 2) * j + i) {
			result.append(1, s[index]);
			if (i == 0 || i == nRows - 1)
				continue;
			if (index + (nRows - i - 1) * 2 < s.size())
				result.append(1, s[index + (nRows - i - 1) * 2]);

		}
	return result;

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

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
