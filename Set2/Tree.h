#pragma once

#pragma once

#include <iostream>

template <typename _Kty, typename _Ty>
class Tree {
private:
	size_t treeSize;

protected:
	template <typename _Kty, typename _Ty>
	class Node
	{
	public:
		std::pair<const _Kty, _Ty> nodePair;
		Node* left;
		Node* right;

		Node(_Kty key, _Ty data) : nodePair(key, data) {
			this->left = nullptr;
			this->right = nullptr;
		}	

		Node(const Node& obj) : nodePair(obj.nodePair) {
			this->left = obj.left;
			this->right = obj.right;
		}
	};

	Node<_Kty, _Ty>* root;


private:
	Node<_Kty, _Ty>* _insert(Node<_Kty, _Ty>* subtree, _Kty key, _Ty data) {
		if (!subtree) return new Node<_Kty, _Ty>(key, data);
		else if (key > subtree->nodePair.first) subtree->right = _insert(subtree->right, key, data);
		else if (key < subtree->nodePair.first) subtree->left = _insert(subtree->left, key, data);
		return subtree;
	}

	Node<_Kty, _Ty>* _erase(Node<_Kty, _Ty>* subtree, _Kty key) {
		if (key > subtree->nodePair.first) subtree->right = _erase(subtree->right, key);
		else if (key < subtree->nodePair.first) subtree->left = _erase(subtree->left, key);
		else if (subtree->left != nullptr && subtree->right != nullptr) {
			Node<_Kty, _Ty> temp = *subtree;
			subtree = min(temp.right);
			subtree->right = _erase(temp.right, subtree->nodePair.first);
			subtree->left = temp.left;
		}
		else {
			if (subtree->left != nullptr) {
				Node<_Kty, _Ty> temp = *subtree;
				delete subtree;
				subtree = temp.left;
			}
			else if (subtree->right != nullptr) {
				Node<_Kty, _Ty> temp = *subtree;
				delete subtree;
				subtree = temp.right;
			}
			else {
				delete subtree;
				subtree = nullptr;
			}
		}
		return subtree;
	}

	Node<_Kty, _Ty>* min(Node<_Kty, _Ty>* subtree) {
		if (subtree->left == nullptr) return subtree;
		return min(subtree->left);
	}

	void _show(Node<_Kty, _Ty>* subtree) {
		if (subtree) {
			_show(subtree->left);
			std::cout << subtree->nodePair.first << "," << subtree->nodePair.second << "  ";
			_show(subtree->right);
		}
	}

	bool _find(Node<_Kty, _Ty>* subtree, _Kty key) {
		if (!subtree) return false;
		if (subtree->nodePair.first == key) return true;
		if (subtree->nodePair.first < key) return _find(subtree->right, key);
		if (subtree->nodePair.first > key) return _find(subtree->left, key);
	}

	void _clear(Node<_Kty, _Ty>* subtree) {
		if (subtree) {
			_clear(subtree->left);
			_clear(subtree->right);
			delete subtree;
		}
	}

	_Ty& _index(Node<_Kty, _Ty>* subtree, int index) {
		if (subtree) {
			if (subtree->nodePair.first == index) return subtree->nodePair.second;
			if (subtree->nodePair.first < index) return _index(subtree->right, index);
			if (subtree->nodePair.first > index) return _index(subtree->left, index);
		}
	}

public:
	Tree() : root(nullptr), treeSize(0) {};

	~Tree() {
		clear();
	}

	void insert(_Kty key, _Ty data = _Ty()) {
		if (!find(key)) {
			treeSize++;
			root = _insert(root, key, data);
		}
	}

	void erase(_Kty key) {
		if (!treeSize) return;
		if (find(key)) {
			treeSize--;
			root = _erase(root, key);
		}
	}

	void show() {
		_show(root);
	}

	size_t size() {
		return treeSize;
	}

	bool empty() {
		return treeSize;
	}

	// Next bigger. Leftmost in right subtree
	Node<_Kty, _Ty>* next(_Kty key) {
		Node<_Kty, _Ty>* current = root;
		Node<_Kty, _Ty>* lastBigger = nullptr;
		while (current) {
			if (current->nodePair.first > key) {
				lastBigger = current;
				current = current->left;
			}
			else current = current->right;
		}
		if (lastBigger) return lastBigger;
		else return current;
	}

	// Prev. smaller. Rightmost in left subtree
	Node<_Kty, _Ty>* prev(_Kty key) {
		Node<_Kty, _Ty>* current = root;
		Node<_Kty, _Ty>* lastSmaller = nullptr;
		while (current) {
			if (current->nodePair.first < key) {
				lastSmaller = current;
				current = current->right;
			}
			else current = current->left;
		}
		if (lastSmaller) return lastSmaller;
		else return current;
	}

	void clear() {
		_clear(root);
		root = nullptr;
		treeSize = 0;
	}

	bool find(_Kty key) {
		return _find(root, key);
	}

	_Ty& operator[](int index) {
		return _index(root, index);
	}
};


