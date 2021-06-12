#include <iostream>
#include "Deque.h"

class A {
public:
	int x;
	A() {
		x = 55;
	}
	int show() {
		return x;
	}
};



int main()
{
	Deque<int> deq1;

	for (int i = 0; i < 32; i++) {
		deq1.push_back(i);
	}

	deq1.push_back(33);
	Deque<int>::Iterator it1 = deq1.begin();
	Deque<int>::Iterator it2 = deq1.begin();
	for (int i = 0; i < 31; i++) {
		++it1;
	}
	++it1;
	for (int i = 0; i < 32; i++) {
		deq1.push_front(i * i);
	}
	std::cout << *it1 << std::endl;
	//it2 = it2 + 5;
	std::cout << *it2 << std::endl;
	for (auto& elem : deq1) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;


	A ob;
	Deque<A> deq2;
	deq2.push_back(ob);

	Deque<A>::Iterator it3 = deq2.begin();

	std::cout << it3->show() << std::endl;
	std::cout << it1[0] << std::endl;


	return 0;
}