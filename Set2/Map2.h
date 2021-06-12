#pragma once

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

		std::pair<_Kty, _Ty> operator*() {
			return this->currentNode->nodePair;
		}
	};

	Iterator begin() {
		if (Tree<_Kty, _Ty>::size()) return Iterator(this, _begin(Tree<_Kty, _Ty>::root));
	}

	Iterator end() {
		if (Tree<_Kty, _Ty>::size()) return Iterator(this, _end(Tree<_Kty, _Ty>::root));
	}

	Map<_Kty, _Ty>() : Tree<_Kty, _Ty>() {};

	~Map<_Kty, _Ty>() {
		this->clear();
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