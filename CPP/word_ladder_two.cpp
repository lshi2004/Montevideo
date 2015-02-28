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

public:
	vector<vector<string>> ladderLength(const string& start, const string &end,
			const unordered_set<string> &dict) {
		unordered_set<string> current, next;
		unordered_set<string> visited;
		unordered_map<string, vector<string>> father;

		int level = 0;
		bool found = false;

		auto state_is_target = [&] (const string &s) {
			return s == end;
		};

		auto state_extend =
				[&] (const string &s) {
					unordered_set<string> result;

					for (size_t i = 0; i < s.size(); ++i) {
						string new_word(s);
						for (char c = 'a'; c <= 'z'; c++) {
							if (c == new_word[i]) continue;

							swap(c, new_word[i]);

							if ((dict.count(new_word) > 0 || new_word == end) &&
									!visited.count(new_word)) {
								result.insert(new_word);
							}
							swap(c, new_word[i]);
						}
					}

					return result;
				};

		current.insert(start);
		while (!current.empty() && !found) {
			++level;
			for (const auto& word : current)
				visited.insert(word);
#if 0
			while (!current.empty() && !found) {
				const string str = current.front();
				current.pop();

				const auto & new_states = state_extend(str);
				for (const auto & state : new_states) {
					next.push(state);
					if (state_is_target(state)) {
						found = true;
						break;
					}
				}
			}
#endif
			for (const auto & word : current) {
				const auto new_states = state_extend(word);
				for (const auto & state : new_states) {
					if (state_is_target(state)) found = true;
					next.insert(state);
					father[state].push_back(word);
				}

			}
			current.clear();
			swap(next, current);
		}

		vector<vector<string>> result;
		if (found) {
			vector<string> path;
			gen_path(father, path, start, end, result);
		}
		return result;
	}

	void gen_path(unordered_map<string, vector<string>> &father,
				vector<string> &path, const string &start, const string &word,
				vector<vector<string>> &result) {
		path.push_back(word);
		if (word == start) {
			result.push_back(path);
			reverse(result.back().begin(), result.back().end());
		} else {
			for (const auto & f: father[word]) {
				gen_path(father, path, start, f, result);
			}
		}
		path.pop_back();
	}


};

void printPreOrder(TreeNode *root) {
	if (!root)
		return;
	cout << root->val << "\t";
	if (root->left)
		printPreOrder(root->left);
	if (root->right)
		printPreOrder(root->right);
}

void printInOrder(TreeNode *root) {
	if (!root)
		return;
	if (root->left)
		printPreOrder(root->left);
	cout << root->val << "\t";
	if (root->right)
		printPreOrder(root->right);
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

	auto pp = new LRUCache(100);
#if 0
	vector<int> S {1, 2, 3};
	auto result = pp->subsets(S);

	for (auto i: result) {
		for (auto j: i)
		cout << j << "\t";
		cout << endl << "one more result " << endl << endl;
	}
#endif
	cout << endl << endl << endl;
	string ts1 = "aa";
	cout << "size of aa is " << ts1.size() << endl;

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!

	return 0;
}
