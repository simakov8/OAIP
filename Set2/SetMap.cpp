#include <iostream>
#include "Set2.h"
#include "Map2.h"


int main()
{
	Set<int> my;

	my.insert(0);
	my.insert(-59);
	my.insert(5);
	my.insert(22);
	my.insert(-95);
	my.insert(-4);
	my.insert(13);
	my.insert(0);
	my.insert(12);
	my.insert(856);
	my.insert(-8);


	my.show();

	std::cout << std::endl;
	std::cout << my[-4];
	std::cout << std::endl;



	my.clear();
	std::cout << my.find(14);


	my.show();
	std::cout << std::endl;
	my.erase(-4);
	my.erase(0);
	my.erase(5);
	my.erase(-59);
	my.erase(22);
	my.erase(-95);
	my.erase(-8);
	my.erase(13);
	my.erase(12);
	my.erase(856);
	my.show();



	return 0;
}