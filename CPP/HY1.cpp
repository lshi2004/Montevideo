//============================================================================
// Name        : HCPP1.cpp
// Author      : HS1
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// cont/vector1.cpp
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;


template <class T>
class priqueue {
private:
	int n, maxsize;
	T *x;
	void swap(int i, int j)
	{ T t = x[i]; x[i] = x[j]; x[j] = t; }
public:
	priqueue(int m)
	{
		maxsize = m;
		n = 0;
		x = new T[maxsize + 1];
	}

	void insert(T t)
	{
		int i, p;
		x[++n] = t;
		//sift down
		for (i = n, p = i/2; i > 1 && x[p] > x[i];
				i = p, p = i/2) {
			swap(p, i);
		}
	}

	T extractmin()
	{
		int i, c;
		T t = x[1];
		x[1] = x[n--];
		//sift up
		for (i = 1, c = 2 * i; c <= n;  i = c, c = 2 * i) {
			if (c + 1 <= n && x[c+1] < x[c])
				c++;
			if (x[i] <= x[c])
				break;
			swap(c, i);
		}
		return t;
	}
};

template <class T>
void pqsort(T v[], int n)
{
	priqueue<T> pq(n);
	int i;

	for (i = 0; i < n; i++)
		pq.insert(v[i]);
	for (i = 0; i < n; i++)
		v[i] = pq.extractmin();
}

int main()
{
	// create empty vector for strings

	vector<string> sentence;

	// reserve memory for five elements to avoid reallocation
	sentence.reserve(5);

	// append some elements
	sentence.push_back("Hello,");
	sentence.insert(sentence.end(),{"how","are","you","?"});

	// print elements separated with spaces
	copy (sentence.cbegin(), sentence.cend(),
			ostream_iterator<string>(cout," "));


	cout << endl;
	// print ‘‘technical data’’
	cout << " max_size(): " << sentence.max_size() << endl;

	int *pq = new int[10] { 135,	177,	183,	186,	193,
							21,		49,		86,		92,		115
							} ;

	pqsort(pq, 10);
	cout << "Result from sorting is " << endl;
	for (int j = 0; j < 10; j++)
		cout << " \t " << pq[j];
	cout << endl << endl;


}
