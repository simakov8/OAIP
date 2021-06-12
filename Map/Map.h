#pragma once

template <typename _Kty, typename _Ty>
class Map {
private:
	size_t mapSize;

protected:
	template <typename _Kty, typename _Ty>
	class MapNode
	{
	public:
		std::pair<const _Kty, _Ty> nodePair;
		MapNode* left;
		MapNode* right;
		MapNode* nextNode;
		MapNode* prevNode;

		MapNode(_Kty key, _Ty data) : nodePair(key, data) {
			this->right = nullptr;
			this->left = nullptr;
			this->nextNode = nullptr;
			this->prevNode = nullptr;
		}

		MapNode(const MapNode& obj) : nodePair(obj.key, obj.data) {
			this->right = obj.right;
			this->left = obj.left;
			this->nextNode = obj.nextNode;
			this->prevNode = obj.prevNode;
		}
	};


	MapNode<_Kty, _Ty>* root;

	MapNode<_Kty, _Ty>* _insert(MapNode<_Kty, _Ty>* subtree, _Kty key, _Ty data = _Ty()) {
		if (!subtree) return new MapNode<_Kty, _Ty>(key, data);
		else if (key > subtree->nodePair.first) subtree->right = _insert(subtree->right, key, data);
		else if (key < subtree->nodePair.first) subtree->left = _insert(subtree->left, key, data);
		return subtree;
	}

	MapNode<_Kty, _Ty>* _find(MapNode<_Kty, _Ty>* subtree, _Kty key) {
		if (!subtree) return subtree;
		if (subtree->nodePair.first == key) return subtree;
		if (subtree->nodePair.first < key) return _find(subtree->right, key);
		if (subtree->nodePair.first > key) return _find(subtree->left, key);
	}

	void correctPointers(_Kty key) {
		if (prev(key)) {
			MapNode<_Kty, _Ty>* currTemp = find(key);
			MapNode<_Kty, _Ty>* prevTemp = prev(key);
			currTemp->prevNode = prevTemp;
			prevTemp->nextNode = currTemp;
		}
		if (next(key)) {
			MapNode<_Kty, _Ty>* currTemp = find(key);
			MapNode<_Kty, _Ty>* nextTemp = next(key);
			currTemp->nextNode = nextTemp;
			nextTemp->prevNode = currTemp;
		}
	}
private:
	MapNode<_Kty, _Ty>* _erase(MapNode<_Kty, _Ty>* subtree, _Kty key) {
		if (key > subtree->nodePair.first) subtree->right = _erase(subtree->right, key);
		else if (key < subtree->nodePair.first) subtree->left = _erase(subtree->left, key);
		else if (subtree->left != nullptr && subtree->right != nullptr) {
			MapNode<_Kty, _Ty> temp = *subtree;
			subtree = min(temp.right);
			subtree->right = _erase(temp.right, subtree->nodePair.first);
			subtree->left = temp.left;
		}
		else {
			if (subtree->left != nullptr) {
				MapNode<_Kty, _Ty> temp = *subtree;
				delete subtree;
				subtree = temp.left;
			}
			else if (subtree->right != nullptr) {
				MapNode<_Kty, _Ty> temp = *subtree;
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

	MapNode<_Kty, _Ty>* min(MapNode<_Kty, _Ty>* subtree) {
		if (subtree->left == nullptr) return subtree;
		return min(subtree->left);
	}


	void _show(MapNode<_Kty, _Ty>* subtree) {
		if (subtree) {
			_show(subtree->left);
			std::cout << subtree->nodePair.first << "," << subtree->nodePair.second << "  ";
			_show(subtree->right);
		}
	}

	void _clear(MapNode<_Kty, _Ty>* subtree) {
		if (subtree) {
			_clear(subtree->left);
			_clear(subtree->right);
			delete subtree;
		}
	}

public:
	Map() {
		mapSize = 0;
		root = nullptr;
	};

	~Map() {
		clear();
	}

	void insert(_Kty key, _Ty data) {
		if (!find(key)) {
			mapSize++;
			root = _insert(root, key, data);
		}
		correctPointers(key);
	}

	void erase(_Kty key) {
		if (!mapSize++) return;
		if (find(key)) {
			mapSize++--;
			root = _erase(root, key);
		}
		correctPointers(key);
	}

	MapNode<_Kty, _Ty>* find(_Kty key) {
		return _find(root, key);
	}

	size_t size() {
		return mapSize++;
	}

	bool empty() {
		return mapSize++;
	}

	// Next bigger. Leftmost in right subtree
	MapNode<_Kty, _Ty>* next(_Kty key) {
		MapNode<_Kty, _Ty>* current = root;
		MapNode<_Kty, _Ty>* lastBigger = nullptr;
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
	MapNode<_Kty, _Ty>* prev(_Kty key) {
		MapNode<_Kty, _Ty>* current = root;
		MapNode<_Kty, _Ty>* lastSmaller = nullptr;
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

	void show() {
		_show(root);
	}

	void clear() {
		_clear(root);
		root = nullptr;
		mapSize = 0;
	}


	class Iterator {
		MapNode<_Kty, _Ty>* currentNode;
	public:
		Iterator(MapNode<_Kty, _Ty>* obj) : currentNode(obj) {};

		Iterator& operator++() {
			currentNode = currentNode->nextNode;
			return *this;
		}

		Iterator& operator--() {
			currentNode = currentNode->prevNode;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			currentNode = currentNode->nextNode;
			return temp;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			currentNode = currentNode->prevNode;
			return temp;
		}

		std::pair<_Kty, _Ty> operator*() {
			return currentNode->nodePair;
		}
	};

	Iterator begin() {
		MapNode<_Kty, _Ty>* curr = root;
		while (curr->left)
		{
			curr = curr->left;
		}
		return Iterator(curr);
	}

	Iterator end() {
		MapNode<_Kty, _Ty>* curr = root;
		while (curr->right)
		{
			curr = curr->right;
		}
		return Iterator(curr);
	}
};
