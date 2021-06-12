#pragma once

#include "Map2.h"


template <typename _Ty>
class Set : public Map<_Ty, char> {
	void _show(Map<_Ty, char>::Node<_Ty, char>* subtree) {
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
};