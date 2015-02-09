//============================================================================
// Name        : JC1.cpp
// Author      : HSD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

struct Base {
	Base() {
		std::cout << "  Base::Base()\n";
	}
	// Note: non-virtual destructor is OK here
	~Base() {
		std::cout << "  Base::~Base()\n";
	}
};


struct Derived: public Base {
	Derived() {
		std::cout << "  Derived::Derived()\n";
	}
	~Derived() {
		std::cout << "  Derived::~Derived()\n";
	}
};

void thr(std::shared_ptr<Base> p) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the
								  // shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard < std::mutex > lk(io_mutex);
		std::cout << "local pointer in a thread:\n" << "  lp.get() = "
				<< lp.get() << ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

int main() {

	std::shared_ptr<Base> p = std::make_shared<Derived>();


	std::cout << "Created a shared Derived (as a pointer to Base)\n"
			<< "  p.get() = " << p.get() << ", p.use_count() = "
			<< p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
			<< "ownership from main:\n" << "  p.get() = " << p.get()
			<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
}

#if 0

#include <iostream>
#include <memory>

using namespace std;

struct Foo
{
	Foo() {std::cout << "Foo::Foo\n";}
	~Foo() {std::cout << "Foo::~Foo\n";}
	void bar() {std::cout << "Foo::bar\n";}
};

void f(const Foo &)
{
	std::cout << "f(const Foo&)\n";
}

int main()
{
	std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
	if (p1) p1->bar();

	{
		std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
		f(*p2);

		p1 = std::move(p2);// ownership returns to p1
		std::cout << "destroying p2...\n";
	}

	if (p1) p1->bar();

	// Foo instance is destroyed when p1 goes out of scope

	cout << "!!!Hello World!!!" << endl;// prints !!!Hello World!!!
	return 0;
}

#endif
