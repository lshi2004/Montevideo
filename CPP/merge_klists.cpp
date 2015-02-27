//============================================================================
// Name        : LM1.cpp
// Author      : HY1
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:

	struct cmp {
		bool operator ()(const ListNode *a, const ListNode *b) {
			return a->val > b->val;
		}
	};

	ListNode *mergeKNewLists(vector<ListNode *> &lists) {
		int n = lists.size();
		if (n == 0) return nullptr;
		ListNode node(0), *res = &node;

		priority_queue<ListNode *, vector<ListNode *>, cmp> que;
		for (int i = 0; i < n; i++)
			if (lists[i])
				que.push(lists[i]);

		while (!que.empty()) {
			ListNode *p = que.top();
			que.pop();
			res->next = p;
			res = p;

			if (p->next)
				que.push(p->next);
		}
		return node.next;

	}

	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;

		ListNode dummy(10);
		ListNode *p = &dummy;

		for (; (l1 != nullptr) && (l2 != nullptr); p = p->next) {
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

	ListNode *mergeKLists(vector<ListNode *> &lists) {
		int n = lists.size();
		if (n == 0)
			return nullptr;

		while (n > 1) {
			int k = (n + 1) / 2;
			for (int i = 0; i < n / 2; i++)
				lists[i] = merge2Lists(lists[i], lists[i + k]);
			n = k;
		}
		return lists[0];

#if 0
		// timeout
		ListNode *p = lists[0];
		for (int i = 1; i < lists.size(); i++) {
			p = merge2Lists(p, lists[i]);
		}
		return p;
#endif
	}

private:
	ListNode *merge2Lists(ListNode *l1, ListNode *l2) {
		ListNode head(-1);

		for (ListNode *p = &head; l1 != nullptr || l2 != nullptr; p = p->next) {
			int val1 = (l1 == nullptr) ? INT_MAX : l1->val;
			int val2 = (l2 == nullptr) ? INT_MAX : l2->val;

			if (val1 <= val2) {
				p->next = l1;
				l1 = l1->next;
			} else {
				p->next = l2;
				l2 = l2->next;
			}
		}

		return head.next;
	}

};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
