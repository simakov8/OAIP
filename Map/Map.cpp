#include <iostream>
#include "Map.h"
#include "Set.h"




int main()
{
	Set<int> mymap;
	mymap.insert(0);
	mymap.show();

	mymap.insert(0);
	mymap.insert(-59);
	mymap.insert(5);
	mymap.insert(22);
	mymap.insert(-95);
	mymap.insert(-4);
	mymap.insert(13);
	mymap.insert(0);
	mymap.insert(12);
	mymap.insert(856);
	mymap.insert(-8);

	Set<int>::Iterator it = mymap.begin();

	std::cout << (*++it).first;


	return 0;
}