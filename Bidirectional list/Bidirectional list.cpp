#include <iostream>
#include <initializer_list>


template <typename T>
class BidirectionalList {
private:
	class Node;
	Node* firstElement;
	Node* lastElement;
	size_t listSize;
public:
	BidirectionalList();
	BidirectionalList(const std::initializer_list<T>& list);
	~BidirectionalList();
	BidirectionalList(const BidirectionalList& obj);
	void push_back(T Value);
	void push_front(T Value);
	void pop_back();
	void pop_front();
	size_t size();
	bool empty();
	class Iterator;
	Iterator begin() const;
	Iterator end() const;
};

template <typename T>
BidirectionalList<T>::BidirectionalList() : listSize(0), firstElement(nullptr), lastElement(nullptr) {}

template <typename T>
BidirectionalList<T>::BidirectionalList(const std::initializer_list<T>& list) {
	for (auto& elem : list) {
		this->push_back(elem);
	}
}

template <typename T>
BidirectionalList<T>::~BidirectionalList() {

}

template <typename T>
BidirectionalList<T>::BidirectionalList(const BidirectionalList& obj) {
	this->listSize = obj.listSize;
	this->firstElement = obj.firstElement;
	this->lastElement = obj.lastElement;
}

template <typename T>
void BidirectionalList<T>::push_back(T Value) {
	listSize++;
	Node* temp = new Node(Value);
	if (firstElement == nullptr && lastElement == nullptr) {
		this->firstElement = temp;
		this->lastElement = temp;
		return;
	}
	temp->prevNode = lastElement;
	lastElement->nextNode = temp;
	lastElement = temp;
}

template <typename T>
void BidirectionalList<T>::push_front(T Value) {
	listSize++;
	Node* temp = new Node(Value);
	if (firstElement == nullptr && lastElement == nullptr) {
		this->firstElement = temp;
		this->lastElement = temp;
		return;
	}
	temp->nextNode = firstElement;
	firstElement->prevNode = temp;
	firstElement = temp;
}

template <typename T>
void BidirectionalList<T>::pop_back() {
	if (!listSize) return;
	listSize--;
	if (!listSize) {
		lastElement->~Node();
		lastElement = firstElement = nullptr;
		return;
	}
	lastElement = lastElement->prevNode;
	lastElement->nextNode->~Node();
	lastElement->nextNode = nullptr;
}

template <typename T>
void BidirectionalList<T>::pop_front() {
	if (!listSize) return;
	listSize--;
	if (!listSize) {
		firstElement->~Node();
		lastElement = firstElement = nullptr;
		return;
	}
	firstElement = firstElement->nextNode;
	firstElement->prevNode->~Node();
	firstElement->prevNode = nullptr;
}

template <typename T>
size_t BidirectionalList<T>::size() {
	return listSize;
}

template <typename T>
bool BidirectionalList<T>::empty() {
	return listSize;
}


template <typename T>
class BidirectionalList<T>::Node {
public:	
	T* dataNodePtr;
	Node* prevNode;
	Node* nextNode;
	Node();
	Node(T Value);
	~Node();
	Node(const Node& obj);
};

template <typename T>
BidirectionalList<T>::Node::Node() {
	this->dataNodePtr = nullptr;
	this->prevNode = nullptr;
	this->nextNode = nullptr;
}

template <typename T>
BidirectionalList<T>::Node::Node(T Value) {
	this->dataNodePtr = new T(Value);
	this->prevNode = nullptr;
	this->nextNode = nullptr;
}

template <typename T>
BidirectionalList<T>::Node::~Node() {
	delete dataNodePtr;
}

template <typename T>
BidirectionalList<T>::Node::Node(const Node& obj) {
	this->data = obj.data;
	this->nextNode = nullptr;
	this->prevNode = nullptr;
}


template <typename T>
class BidirectionalList<T>::Iterator : std::iterator<std::bidirectional_iterator_tag, T> {
private:
	Node* ptrNode;
public:
	Iterator();
	~Iterator();
	Iterator(Node& obj);
	Iterator(const Iterator& obj);
	Iterator& operator=(const Iterator& obj);
	bool operator==(const Iterator& obj) const;
	bool operator!=(const Iterator& obj) const;
	T& operator* ();
	T operator*() const;
	T* operator->();
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator++(int);
	Iterator operator--(int);
};


template <typename T>
BidirectionalList<T>::Iterator::Iterator() : ptrNode(nullptr) {}

template <typename T>
BidirectionalList<T>::Iterator::~Iterator() {
	ptrNode = nullptr;
}

template <typename T>
BidirectionalList<T>::Iterator::Iterator(const Iterator& obj) : ptrNode(obj.ptrNode) {}

template <typename T>
BidirectionalList<T>::Iterator::Iterator(Node& obj) {
	this->ptrNode = &obj;
}

template <typename T>
typename BidirectionalList<T>::Iterator& BidirectionalList<T>::Iterator::operator=(const Iterator& obj) {
	this->ptrNode = obj.ptrNode;
	return *this;
}

template <typename T>
bool BidirectionalList<T>::Iterator::operator==(const Iterator& obj) const {
	return (*this->ptrNode->dataNodePtr == *obj.ptrNode->dataNodePtr);
}

template <typename T>
bool BidirectionalList<T>::Iterator::operator!=(const Iterator& obj) const {
	return (*this->ptrNode->dataNodePtr != *obj.ptrNode->dataNodePtr);
}

template <typename T>
T& BidirectionalList<T>::Iterator::operator*() {
	return *this->ptrNode->dataNodePtr;
}

template <typename T>
T BidirectionalList<T>::Iterator::operator*() const{
	return *this->ptrNode->dataNodePtr;
}

template <typename T>
T* BidirectionalList<T>::Iterator::operator->() {
	return this->ptrNode->dataNodePtr;
}

template <typename T>
typename BidirectionalList<T>::Iterator& BidirectionalList<T>::Iterator::operator++() {
	this->ptrNode = this->ptrNode->nextNode;
	return *this;
}

template <typename T>
typename BidirectionalList<T>::Iterator& BidirectionalList<T>::Iterator::operator--() {
	this->ptrNode = this->ptrNode->prevNode;
	return *this;
}

template <typename T>
typename BidirectionalList<T>::Iterator BidirectionalList<T>::Iterator::operator++(int) {
	Iterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename BidirectionalList<T>::Iterator BidirectionalList<T>::Iterator::operator--(int) {
	Iterator temp = *this;
	--(*this);
	return temp;
}




template <typename T>
typename BidirectionalList<T>::Iterator BidirectionalList<T>::begin() const {
	return Iterator(*firstElement);
}

template <typename T>
typename BidirectionalList<T>::Iterator BidirectionalList<T>::end() const {
	return Iterator();
}





int main() {




	BidirectionalList<int> list{3,7,0,34,83,14,87,107};




	return 0;
}