#include <iostream>
#include <unordered_map>
#include "Unordered_map.h"
#include <forward_list>



int main()
{
	std::forward_list<std::pair<int, int>> map;

	std::forward_list<std::pair<int, int>>::iterator it = map.begin();



	Unordered_map<int, int> my;

	my.insert(std::pair<int, int>(1, 4));
	//my.erase(1);

	my[1] = 32;
	std::unordered_map<int, int> mapp;





	return 0;
}
