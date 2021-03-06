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

	int majorityElement(vector<int> &num) {
		int times = 1;
		int last_num = num[0];

		for (int i = 1; i < num.size(); ++i) {
			if (num[i] == last_num) {
				times++;
			} else {
				if (times > 0)
					times--;
				else {
					times = 1;
					last_num = num[i];
				}
			}
		}
		return last_num;
	}

	ListNode *rotateRight(ListNode *head, int k) {
		if (head == nullptr)
			return head;

		int len = 1;
		ListNode *p = head;
		while (p->next) {
			len++;
			p = p->next;
		}

		k = len - k % len;
		p->next = head;
		for (int step = 0; step < k; step++) {
			p = p->next;
		}
		head = p->next;
		p->next = nullptr;
		return head;

	}

	ListNode *removeNthFromEnd(ListNode *head, int n) {
		if (head == nullptr)
			return head;
		ListNode dummy(-1);
		dummy.next = head;

		ListNode *p = &dummy, *q = &dummy;

		for (int i = 0; i < n; ++i) {
			p = p->next;
		}

		//find prev node of the nth node
		while (p->next) {
			p = p->next;
			q = q->next;
		}

		if (p) {
			auto tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}

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

	auto pp = new lengthSolution;
	ListNode np(1);
	ListNode *pn = pp->removeNthFromEnd(&np, 1);

	cout << "null " << pn << endl;

	int k1 = 0;
	cout << "hello" << k1 << endl;

//	for (int i = 1; i < 10; i++) {
//			string s1 = pp->countAndSay(i);
//			cout << s1 << endl;
//	}

	cout << "!!!Hello World!!! " << ptr[0] << "   " << ptr[1] << endl; // prints !!!Hello World!!!
	return 0;
}
