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



class IntSetBST {
private:
	int n, maxelements;
	int *v, vn;

	struct node {
		int val;
		node *left, *right;
		node(int v) { val = v; left = right = 0; }
	};

	node *root;
	node *rinsert(node *p, int t)
	{
		if (n == maxelements) return nullptr;

		if (p == 0) {
			p = new node(t);
			n++;
		} else if (t < p->val) {
			p->left = rinsert(p->left, t);
		} else if (t > p->val) {
			p->right = rinsert(p->right, t);
		} // do nothing if p->val == t

		return p;
	}

	void traverse(node *p)
	{
		if (p == 0) {
			return;
		}
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}
public:
	IntSetBST(int maxelements, int maxval)
	{
		n = 0;
		vn = 0;
		v = 0;
		this->maxelements = maxelements;
		root = 0;
	}

	int size() { return n; }

	void insert(int t)
	{
		root = rinsert(root, t);
	}

	void report(int *v)
	{
		this->v = v;
		vn = 0;
		traverse(root);
	}
};



void gen_bst (int m, int maxval)
{
	int *v = new int[m];

	IntSetBST S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "KK Inserted " << k << " size ";
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


class IntSetBIN {

private:
	int n, bins, maxelements;
	struct node {
		int val;
		node *next;
		node(int v, node *p) { val = v; next = p; }
	};
	node **bin, *sentinel;
	int maxval;

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
	IntSetBIN(int maxelements, int maxval)
	{
		n = 0;
		this->maxelements = maxelements;
		this->maxval = maxval;
		bins = maxelements;
		bin = new node *[bins];
		sentinel = new node(maxval, 0);
		for (int i = 0; i < bins; i++) {
			bin[i] = sentinel;
		}
	}

	int size() { return n; }

	void insert(int t)
	{
		int i = t / (1 + maxval/bins);
		bin[i] = rinsert(bin[i], t);
	}

	void report(int *v)
	{
		int j = 0;
		for (int i = 0; i < bins; i++) {
			for (node *p = bin[i]; p != sentinel; p = p->next) {
				 v[j++] = p->val;
			}
		}
	}
};



void gen_bin (int m, int maxval)
{
	int *v = new int[m];

	IntSetBIN S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "KK1 Inserted " << k << " size ";
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


class IntSetVEC {
private:
	enum { BITSPERWORD = 32, SHIFT = 5, MASK = 0x1F};
	int n, hi, *x;
	void set (int i) { x[i>>SHIFT] |= (1 << (i & MASK)); }
	void clr (int i) { x[i>>SHIFT] &= ~(1 << (i & MASK)); }
	int test(int i) { return x[i>>SHIFT] & (1 << (i & MASK)); }
public:
	IntSetVEC(int maxelements, int maxval)
	{
		hi = maxval;
		x = new int[1 + hi/BITSPERWORD];
		for (int i = 0; i < hi; i++)
			clr(i);
		n = 0;
	}
	int size() { return n; }
	void insert(int t) {
		if (test(t)) {
			return;
		}
		set(t);
		n++;
	}
	void report(int *v)
	{
		int j = 0;
		for (int i = 0; i < hi; i++) {
			if (test(i)) {
				v[j++] = i;
			}
		}
	}
};


void gen_vec (int m, int maxval)
{
	int *v = new int[m];

	IntSetBIN S(m, maxval);

	while (S.size() < m) {
		int k = rand() % maxval;
		cout << "KK2 Inserted " << k << " size ";
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

//	gen_list(10, 100);

	gen_vec(10, 200);

	return 0;
}
