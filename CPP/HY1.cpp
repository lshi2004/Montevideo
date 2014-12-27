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
#include <functional>
#include <thread>
#include <future>

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

template <class T>
void sift_down(T v[], int length)
{
	int i, c;

	for (i = 1, c = 2 * i; c <= length;
		 i = c, c = 2 * i) {
		if (c + 1 <= length && v[c+1] < v[c])
			c++;
		if (v[i] <= v[c])
				break;
		swap(v[c], v[i]);
	}
}

template <class T>
void sift_up(T v[], int mem)
{
	int i, p;
	//sift down
	for (i = mem, p = i/2; i > 1 && v[p] > v[i];
		 i = p, p = i/2) {
		swap(v[p], v[i]);
	}
}

// decreasing order, as it is extracting min
// like:
//  193 	 186 	 183 	 177 	 135 	 115 	 92 	 86 	 49 	 21
template <class T>
void heap_sort(T v[], int n)
{
	int i;

	for (i = 2; i <= n; i++)
		sift_up(v, i);

	for (i = n; i >= 2; i--) {
		swap(v[1], v[i]);
		sift_down(v, i-1);
	}
}

int t_main()
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

#if 0

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
#endif

	int *hq = new int[11] { -300,
							135,	177,	183,	186,	193,
							21,		49,		86,		92,		115
							} ;


	heap_sort(hq, 10);
	cout << "Result from sorting is " << endl;
	for (int j = 1; j < 11; j++)
		cout << " \t " << hq[j];
	cout << endl << endl;

	return 0;
}


void func(int x, int y)
{
	cout << "Inside Func  " << x << " " << y << endl;
}

int func_int(int x, int y)
{
	cout << "Inside Func  " << x << " " << y << endl;
	return 1;
}

class CC {
public:
	void memfunc(int x, int y) const {
		cout << "Insde member Func " << x << " " << y << endl;
	}
	void operator() (int x, int y) const {
		cout << "Insde operator Func " << x << " " << y << endl;
	}
};

int main()
{
	std::vector <std::function<void(int,int)>> tasks;

	auto l2 = [ ] (int x, int y) {
		cout << "Inside lamda 1 " << x <<" "<< y << endl;
	};

	tasks.push_back(func);


	tasks.push_back( [ ] (int x, int y)
		{
			cout << "Inside lamda 2 " << x << " " << y << endl;
		}
	);


	tasks.push_back(l2);

	for (auto f: tasks) {
		f(33, 66);
	}

	std::function<void(const CC&, int, int)> mf;
	mf = &CC::memfunc;
	mf(CC(), 42, 77);


	cout << "Callable objects" << endl << endl;

	CC c;
	// std::shared_ptr <CC> sp(new CC);

	std::bind(func, 77, 33)();
	std::bind(l2, 77, 33)();
	std::bind(CC(), 77, 33)();
	std::bind(&CC::memfunc, c, 77, 33)();
	//std::bind(&CC::memfunc, sp, 77, 33)();

//#if 0
	cout << "Second Callable objects" << endl << endl;
	auto result1= async([] { func_int( 42, 77);});
	std::future<void> result2(std::async([&] {l2( 90, 88);}));


	result1.wait();
	result1.get();

	result2.wait();
	result2.get();

//#endif


	return 0;
}
