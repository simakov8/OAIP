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
    size_t size() const; // REVIEW const
    bool empty() const; // const
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
};

template <typename T>
BidirectionalList<T>::BidirectionalList() : listSize(0), firstElement(nullptr) {
  lastElement = new Node();
}

template <typename T>
BidirectionalList<T>::BidirectionalList(const std::initializer_list<T>& list) {
    lastElement = new Node();
    for (auto& elem : list) {
        this->push_back(elem);
    }
}

template <typename T>
BidirectionalList<T>::~BidirectionalList() {
  for (size_t i = 0; i < listSize; i++) {
    this->pop_back();
  }
  this->firstElement = nullptr;
}

template <typename T>
BidirectionalList<T>::BidirectionalList(const BidirectionalList& obj) {
    this->listSize = 0;
    this->firstElement = nullptr;
    this->lastElement = new Node();
    for (auto item : obj) {
      this->push_back(item);
    }
}

template <typename T>
void BidirectionalList<T>::push_back(T Value) {
    listSize++;
    Node* temp = new Node(Value);
    temp->prevNode = lastElement->prevNode;
    temp->nextNode = lastElement;
    lastElement->prevNode = temp;
    if (temp->prevNode) temp->prevNode->nextNode = temp;
    if (firstElement == nullptr) {
      firstElement = temp;
    }
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
    Node* temp = lastElement->prevNode;
    lastElement->prevNode = lastElement->prevNode->prevNode;
    delete temp;
    if (!listSize) {
      firstElement = nullptr;
      return;
    }
    lastElement->prevNode->nextNode = lastElement;
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
size_t BidirectionalList<T>::size() const {
    return listSize;
}

template <typename T>
bool BidirectionalList<T>::empty() const {
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
    Iterator operator++(int) const; // REVIEW const
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
    if (this->ptrNode->dataNodePtr == nullptr && obj.ptrNode->dataNodePtr == nullptr) return false;
    else if (this->ptrNode->dataNodePtr != nullptr && obj.ptrNode->dataNodePtr == nullptr) return true;
    else if (this->ptrNode->dataNodePtr == nullptr && obj.ptrNode->dataNodePtr != nullptr) return true;
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
typename BidirectionalList<T>::Iterator BidirectionalList<T>::Iterator::operator++(int) const {
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
    return Iterator(*lastElement);
}

/* REVIEW
 * очень качественная работа в целом, хоть и тестирующий код не запускается, что нужно поправить
 * будут бонусы за: топовые итераторы, шаблоны, если по итогу память будет очищаться (вроде очищается)
 * нужно немного дописать, чтоб тесты проходили
 */