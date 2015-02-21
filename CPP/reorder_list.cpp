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
	void reorderList(ListNode *head) {
		if (!head || !head->next) return;

		ListNode *slow = head, *fast = head, *prev = nullptr;

		while (fast && fast->next) {
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		prev->next = nullptr;

		//slow is the head of second half of the linked list
		slow = reverse(slow);

		//merge the two lists
		ListNode *cur = head;
		while (cur->next) {
			ListNode *tmp = cur->next;
			cur->next = slow;
			slow = slow->next;
			cur->next->next = tmp;
			cur = tmp;
		}
		cur->next = slow;

	}


	ListNode *reverse(ListNode *head) {
		if (!head) return nullptr;

		ListNode *prev = nullptr;
		ListNode *cur = head;
		while (cur) {
			ListNode *tmp = cur->next;
			cur->next = prev;
			prev = cur;
			cur = tmp;
		}
		return prev;

	}


	ListNode *reverse_working(ListNode *head) {
	if (head == nullptr || head->next == nullptr) return head;
          ListNode *prev = head;
          for (ListNode *curr = head->next, *next = curr->next; curr;
              prev = curr, curr = next, next = next ? next->next : nullptr) {
                  curr->next = prev;
          }
          head->next = nullptr;
          return prev;

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

	bool hasCycle(ListNode *head) {
		ListNode *slow, *fast;
		slow = head;
		fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) return true;
		}
		return false;
	}

	ListNode *detectCycle(ListNode *head) {
		ListNode *slow = head, *fast = head;

		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast) {
				ListNode *slow2 = head;
				while (slow2 != slow) {
					slow2 = slow2->next;
					slow = slow->next;
				}
				return slow2;

			}
		}
		return nullptr;

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
