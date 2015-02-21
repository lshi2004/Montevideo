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

	ListNode *swapPairs(ListNode *head) {
		if (!head || !head->next) return head;

		ListNode dummy(-1);
		dummy.next = head;

		for (ListNode *prev = &dummy, *cur = prev->next, *next = cur->next;
				next;
				prev = cur, cur = cur->next, next = cur ? cur->next : nullptr) {
			prev->next = next;
			cur->next = next->next;
			next->next = cur;
		}
		return dummy.next;
	}

	ListNode *reverseKGroup(ListNode *head, int k) {
		if (head == nullptr || head->next == nullptr || k < 2)
			return head;

		ListNode dummy(-1);
		dummy.next = head;

		for (ListNode *prev = &dummy, *end = head; end; end = prev->next) {
			for (int i = 1; i < k && end; i++)
				end = end->next;
			if (end == nullptr) break;
			prev = reverse(prev, prev->next, end);


		}
		return dummy.next;

	}

	ListNode *reverse(ListNode *prev, ListNode *begin, ListNode *end) {
		if (!end) return nullptr;
		ListNode *end_next = end->next;
		for (ListNode *p = begin, *cur = p->next, *next = cur->next;
				cur != end_next;
				p = cur, cur = next, next = next ? next->next : nullptr) {
			cur->next = p;
		}
		begin->next = end_next;
		prev-next = end;
		return begin;
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
