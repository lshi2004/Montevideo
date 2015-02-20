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
      ListNode(int x) : val(x), next(NULL) {}
};


class lengthSolution {
public:

	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode dummy(-1);
		ListNode *p1, *p2, *previous;
		int carry;

		previous = &dummy;
		carry = 0;
		for (p1 = l1, p2 = l2; p1 != nullptr || p2 != nullptr;
				previous = previous->next) {
			int a1, a2, c;
			a1 = p1 == nullptr ? 0 : p1->val;
			a2 = p2 == nullptr ? 0 : p2->val;
			c = a1 + a2 + carry;
			carry = c / 10;
			c = c % 10;
			previous->next = new ListNode(c);
			if (p1) p1 = p1->next;
			if (p2) p2 = p2->next;

		}

		if (carry) previous->next = new ListNode(carry);
		return dummy.next;
	}



	ListNode *deleteDuplicates(ListNode *head) {
		if (head == nullptr) return head;

		ListNode dummy(head->val + 1);
		dummy.next = head;

		ListNode *prev = &dummy;
		ListNode *cur = head;

		while (cur != nullptr) {
			if (cur->val == prev->val) {
				prev->next = cur->next;
				ListNode *tmp = cur;
				cur = cur->next;
				delete tmp;
			} else {
				prev = cur;
				cur = cur->next;
			}
		}
		return dummy.next;


	}


	ListNode *deleteDuplicates2(ListNode *head) {
			if (head == nullptr) return head;

			ListNode *prev = head;
			ListNode *cur = head->next;


			for (prev = head, cur = prev->next; cur ; ) {
				if (cur->val == prev->val) {
					prev->next = cur->next;
					ListNode *tmp = cur;
					cur = cur->next;
					delete tmp;
				} else {
					prev = cur;
					cur = cur->next;
				}
			}

			return head;

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
