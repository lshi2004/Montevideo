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

class lengthSolution {
public:

	ListNode *partition(ListNode *head, int x) {
		ListNode left_dummy(-1);
		ListNode right_dummy(-1);

		auto left_cur = &left_dummy;
		auto right_cur = &right_dummy;

		for (ListNode *cur = head; cur; cur = cur->next) {
			if (cur->val < x) {
				left_cur->next = cur;
				left_cur = cur;
			} else {
				right_cur->next = cur;
				right_cur = cur;
			}
		}
		left_cur->next = right_dummy.next;
		right_cur->next = nullptr;

		return left_dummy.next;

	}

	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next) return head;

		ListNode *p = head->next;

		if (head->val == p->val) {
			while (p && head->val == p->val) {
				ListNode *tmp = p;
				p = p->next;
				delete tmp;
			}
			delete head;
			return deleteDuplicates(p);
		}
		head->next = deleteDuplicates(head->next);
		return head;
	}

	ListNode* deleteDuplicatesNew(ListNode* head) {
		if (head == nullptr) return head;
		ListNode dummy(INT_MIN);
		dummy.next = head;
		ListNode *prev = &dummy, *cur = head;

		while (cur != nullptr) {
			bool duplicated = false;
			while (cur->next && cur->val == cur->next->val) {
				duplicated = true;
				ListNode *temp = cur;
				cur = cur->next;
				delete temp;
			}
			if (duplicated) {
				ListNode *temp = cur;
				cur = cur->next;
				prev->next = cur;
				delete temp;
				continue;
			}
			prev->next = cur;
			prev = prev->next;
			cur = cur->next;
		}
		//prev->next = cur;
		return dummy.next;
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

//auto pp = new lengthSolution;
	int k1 = 0;
	cout << "hello" << k1 << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
