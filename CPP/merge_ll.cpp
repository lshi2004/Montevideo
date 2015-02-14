//============================================================================
// Name        : LM1.cpp
// Author      : HY1
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;

		ListNode dummy(10);
		ListNode *p = &dummy;

		for  (; (l1 != nullptr) && (l2 != nullptr); p = p->next) {
			if (l1->val > l2->val) {
				p->next = l2;
				l2 = l2->next;
			} else {
				p->next = l1;
				l1 = l1->next;
			}
		}

		p->next = (l1 != nullptr) ? l1 : l2;

		return dummy.next;
	}
};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
