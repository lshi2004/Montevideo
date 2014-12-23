//============================================================================
      // Name        : HY2.cpp
// Author      : HY1
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <cstdlib>
#include <cstring>
//#include <stdio.h>
//#include <string.h>


using namespace std;

class IntSetSTL {
private:
	set<int>	S;
public:
	IntSetSTL(int maxelements, int maxval) { }
	int size() { return S.size(); }
	void insert(int t) { S.insert(t);}
	void report(int *v)
	{
		int j = 0;
		for (auto elem : S) {
			v[j++] = elem;
		}
	}
};

void gen_sets(int m, int maxval)
{
	int *v = new int[m];

	IntSetSTL S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "Inserted " << k << " size ";
		cout << S.size() << endl;
		S.insert(k);
	}

	S.report(v);
	for (int i = 0; i < m; i++) {
		cout << v[i] << endl;
	}
}



class IntSetArray {
private:
	int n, *x;
	int maxelements;
public:
	IntSetArray(int maxelements, int maxval)
	{
		x = new int[1 + maxelements];
		n = 0;

		//fill_n(x, 1 + maxelements, 0);
		memset(x, 0, sizeof(int)*(1 + maxelements));
		x[0] = maxval;

		this->maxelements = maxelements;
	}

	int size() { return n; }

	void insert(int t)
	{
		int i, j;

		for (i = 0; x[i] < t; i++)
			;

		if (x[i] == t) {
			return;
		}

		if (n == maxelements) {
			return;
		}

		for (j = n; j >= i; j--) {
			x[j+1] = x[j];
 		}

		x[i] = t;
		n++;
	}

	void report(int *v)
	{
		for (int j = 0; j < n; j++)
			v[j] = x[j];
	}
};


void gen_array(int m, int maxval)
{
	int *v = new int[m];

	IntSetArray S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "Inserted " << k << " size ";
		cout << S.size() << endl;
		S.insert(k);
		S.report(v);
		for (int i = 0; i < m; i++) {
			cout << v[i] << "\t";
		}
		cout<<endl;

	}

	cout << "Final Printing " << v << " size " << S.size() << endl;
	S.report(v);
	for (int i = 0; i < m; i++) {
		cout << v[i] << "\t";
	}
	cout<<endl;

}



class IntSetList {
private:
	int n, maxelements;
	struct node {
		int val;
		node *next;
		node(int v, node *p) { val = v; next = p; }
	};
	node *head, *sentinel;
	node *rinsert(node *p, int t)
	{
		if (n == maxelements) return nullptr;

		if (p->val < t) {
			p->next = rinsert(p->next, t);
		} else {
			p = new node(t, p);
			n++;
		}
		return p;
	}
public:
	IntSetList(int maxelements, int maxval)
	{
		n = 0;
		this->maxelements = maxelements;
		sentinel = head = new node(maxval, 0);
	}

	int size() { return n; }

	void insert(int t)
	{
		head = rinsert(head, t);
	}

	void report(int *v)
	{
		int j = 0;
		for (node *p = head; p != sentinel; p = p->next) {
			 v[j++] = p->val;
		}
	}
};


void gen_list(int m, int maxval)
{
	int *v = new int[m];

	IntSetList S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "Inserted " << k << " size ";
		cout << S.size() << endl;
		S.insert(k);
		S.report(v);
		for (int i = 0; i < m; i++) {
			cout << v[i] << "\t";
		}
		cout<<endl;

	}

	cout << "Final Printing " << v << " size " << S.size() << endl;
	S.report(v);
	for (int i = 0; i < m; i++) {
		cout << v[i] << "\t";
	}
	cout<<endl;

}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

//	gen_sets(10, 100);

//	gen_array(10, 100);

	gen_list(10, 100);

	return 0;
}
