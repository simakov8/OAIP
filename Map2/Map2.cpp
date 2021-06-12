#include <iostream>
#include <map>
#include "Tree.h"


template <typename _Kty, typename _Ty>
class Map : public Tree<_Kty, _Ty> {

public:

	class Iterator {

	private:
		Tree<_Kty, _Ty>::Node<_Kty, _Ty>* currentNode;
		Map<_Kty, _Ty>* ptrToMap;
	public:
		Iterator() : currentNode(nullptr), ptrToMap(nullptr) {};
		Iterator(Map<_Kty, _Ty>* map, Tree<_Kty, _Ty>::Node<_Kty, _Ty>* currN) : currentNode(currN), ptrToMap(map) {};
		Iterator(const Iterator& obj) : currentNode(obj.currentNode), ptrToMap(obj.ptrToMap) {};
		void next() {
			currentNode = ptrToMap->next(currentNode->nodePair.first);
		}
		void prev() {
			currentNode = ptrToMap->prev(currentNode->nodePair.first);
		}
	};

	Iterator begin() {
		if (Tree<_Kty, _Ty>::size()) return Iterator(this, _begin(Tree<_Kty, _Ty>::root));
	}

	Iterator end() {
		if (Tree<_Kty, _Ty>::size()) return Iterator(this, _end(Tree<_Kty, _Ty>::root));
	}


private:
	Tree<_Kty, _Ty>::Node<_Kty, _Ty>* _begin(Tree<_Kty, _Ty>::Node<_Kty, _Ty>* subtree) {
		if (subtree) {
			if (subtree->left) return _begin(subtree->left);
			else return subtree;
		}
	}

	Tree<_Kty, _Ty>::Node<_Kty, _Ty>* _end(Tree<_Kty, _Ty>::Node<_Kty, _Ty>* subtree) {
		if (subtree) {
			if (subtree->right) return _end(subtree->right);
			else return subtree;
		}
	}
};




int main()
{
	Map<int, int> my;
	my.insert(0, 5);
	my.insert(-59, 2);
	my.insert(5, 6);
	my.insert(22, 9);
	my.insert(-95, 1);
	my.insert(-4, 4);
	my.insert(13, 8);
	my.insert(0, 45);
	my.insert(12, 7);
	my.insert(856, 10);
	my.insert(-8, 3);


	Map<int, int>::Iterator it = my.begin();

	it.next();







	return 0;
}