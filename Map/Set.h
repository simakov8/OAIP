#pragma once

#include "Map.h"

template <typename _Ty>
class Set : public Map<_Ty, char> {
	void _show(Map<_Ty, char>::MapNode<_Ty, char>* subtree) {
		if (subtree) {
			_show(subtree->left);
			std::cout << subtree->nodePair.first << " ";
			_show(subtree->right);
		}
	}
public:
	void show() {
		_show(this->root);
	}
	void insert(_Ty Value) {
		this->root = this->_insert(this->root, Value);
		this->correctPointers(Value);
	}
};