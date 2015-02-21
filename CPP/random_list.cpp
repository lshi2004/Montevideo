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
public:

	ListNode *reverse(ListNode *prev, ListNode *begin, ListNode *end) {
		if (!end)
			return nullptr;
		ListNode *end_next = end->next;
		for (ListNode *p = begin, *cur = p->next, *next = cur->next;
				cur != end_next;
				p = cur, cur = next, next = next ? next->next : nullptr) {
			cur->next = p;
		}
		begin->next = end_next;
		prev->next = end;
		return begin;
	}

	RandomListNode *copyRandomList(RandomListNode *head) {
		if (!head)
			return nullptr;

		// duplicate the linked list in original list
		for (auto *ptr = head; ptr;) {
			auto *p = new RandomListNode(ptr->label);
			p->next = ptr->next;
			ptr->next = p;
			ptr = p->next;
		}

		//copy random pointers
		for (auto *ptr = head; ptr; ptr = ptr->next->next) {
			if (ptr->random)
				ptr->next->random = ptr->random->next;
		}

		RandomListNode *h2 = head->next;
		for (auto *p1 = head, *p2 = h2; p1;) {
			p1->next = p1->next->next;
			p1 = p1->next;
			p2->next = p1 ? p1->next : nullptr;
			p2 = p2->next;
		}

		return h2;
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

	auto pp = new lengthSolution;
	ListNode np(1);
//	ListNode *pn = pp->removeNthFromEnd(&np, 1);

	int k1 = 0;
	cout << "hello" << k1 << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
