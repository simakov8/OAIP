#include <iostream>
#include <iterator>
#include <initializer_list>


///--------DECLARATION CLASS VECTOR---------------------------------------------------------------///
template <typename T>
class Vector {

  T* array;

  size_t vecCapacity;
  size_t vecSize;

public:
  Vector(size_t size = 0);

  Vector(const std::initializer_list<T>& list);

  Vector(const Vector& obj);

  ~Vector();

  size_t size();

  size_t capacity();

  void resize(size_t Newsize);

  bool empty() const;

  void push_back(const T& Val);

  void pop_back();

  T& operator[](size_t index);

  Vector& operator=(const Vector& obj);

  class Iterator;

  Iterator begin() const;

  Iterator end() const;
};

///------------IMPLEMENTATION OF FUNCTIONS--------------------------------------------------------///
template <typename T>
Vector<T>::Vector(size_t size) {
  array = new T[size];
  vecCapacity = size;
  vecSize = size;
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
  size_t i = 0;
  for (auto& elem : list) {
    array[i++] = elem;
  }
}

template <typename T>
Vector<T>::Vector(const Vector& obj) {
  this->vecCapacity = obj.vecCapacity;
  this->vecSize = obj.vecSize;
  this->array = new T[obj.vecCapacity];
  for (size_t i = 0; i < obj.vecSize; i++) {
    this->array[i] = obj.array[i];
  }
}

template <typename T>
Vector<T>::~Vector() {
  delete[] array;
}

template <typename T>
size_t Vector<T>::size() {
  return vecSize;
}

template <typename T>
size_t Vector<T>::capacity() {
  return vecCapacity;
}

template <typename T>
void Vector<T>::resize(size_t Newsize) {
  if (Newsize < 0 || Newsize > 1073741823) return;

  vecCapacity = Newsize;

  T* temparr = new T[Newsize];

  for (size_t i = 0; i < vecSize && i < Newsize; i++) {
    temparr[i] = array[i];
  }

  delete[] array;
  array = temparr;
}

template <typename T>
bool Vector<T>::empty() const {
  return vecSize;
}

template <typename T>
void Vector<T>::push_back(const T& Val) {
  if (vecSize == vecCapacity) resize((size_t)((vecCapacity + 1) * 1.5));
  array[vecSize++] = Val;
}

template <typename T>
void Vector<T>::pop_back() {
  vecSize--;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
  return array[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& obj) {
  delete[] this->array;
  this->vecCapacity = obj.vecCapacity;
  this->vecSize = obj.vecSize;
  this->array = new T[obj.vecCapacity];
  for (size_t i = 0; i < obj.vecSize; i++) {
    this->array[i] = obj.array[i];
  }
  return *this;
}

///--------DECLARATION CLASS ITERATOR-------------------------------------------------------------///
template <typename T>
class Vector<T>::Iterator : std::iterator<std::random_access_iterator_tag, T> {
private:

  T* ptr;

public:
  Iterator();

  ~Iterator();

  Iterator(const Iterator& obj);

  explicit Iterator(T* value);

  Iterator& operator=(const Iterator& obj);

  bool operator==(const Iterator& obj) const;

  bool operator!=(const Iterator& obj) const;

  //T operator*() const; 
  T& operator*();

  T* operator->();

  Iterator& operator++();

  Iterator& operator--();

  Iterator operator++(int);

  Iterator operator--(int);

  Iterator operator+(int n) const;

  Iterator operator-(int n) const;

  friend typename Vector<T>::Iterator operator+(int n, const typename Vector<T>::Iterator& obj) {
    typename Vector<T>::Iterator temp;
    temp.ptr += n;
    return temp;
  }

  bool operator>(const Iterator& obj);

  bool operator<(const Iterator& obj);

  bool operator>=(const Iterator& obj);

  bool operator<=(const Iterator& obj);

  Iterator operator+=(int n);

  Iterator operator-=(int n);

  T& operator[](size_t index);
};


///------------IMPLEMENTATION OF FUNCTIONS--------------------------------------------------------///
template <typename T>
Vector<T>::Iterator::Iterator() : ptr(nullptr) {}

template <typename T>
Vector<T>::Iterator::~Iterator() {
  this->ptr = nullptr;
}

template <typename T>
Vector<T>::Iterator::Iterator(const Iterator& obj) : ptr(obj.ptr) { }

template <typename T>
Vector<T>::Iterator::Iterator(T* value) : ptr(value) {}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& obj)
{
  this->ptr = obj.ptr;
  return *this;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& obj) const {
  return this->ptr == obj.ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& obj) const {
  return this->ptr != obj.ptr;
}

template <typename T>
T& Vector<T>::Iterator::operator*() {
  return *ptr;
}

template <typename T>
T* Vector<T>::Iterator::operator->()
{
  return ptr;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
  this->ptr++;
  return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
  this->ptr--;
  return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
  Iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int n) const {
  return Iterator(this->ptr + n);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int n) const {
  return Iterator(this->ptr - n);
}

template <typename T>
bool Vector<T>::Iterator::operator>(const Iterator& obj) {
  return (*(this->ptr) > *obj.ptr);
}

template <typename T>
bool Vector<T>::Iterator::operator<(const Iterator& obj) {
  return (*(this->ptr) < *obj.ptr);
}

template <typename T>
bool Vector<T>::Iterator::operator>=(const Iterator& obj) {
  return (*(this->ptr) >= *obj.ptr);
}

template <typename T>
bool Vector<T>::Iterator::operator<=(const Iterator& obj) {
  return (*(this->ptr) <= *obj.ptr);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+=(int n) {
  this->ptr += n;
  return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-=(int n) {
  this->ptr -= n;
  return *this;
}

template <typename T>
T& Vector<T>::Iterator::operator[](size_t index) {
  return *(this->ptr + index);
}


template<typename T>
typename Vector<T>::Iterator Vector<T>::begin() const {
  return Iterator(&array[0]);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::end() const {
  return Iterator(&array[vecSize]);
}



class A {
public:
  int x;
};


int main()
{

  Vector<int> arr = { 5, 4, 9, 45, 23, 89, 142};

  Vector<int>::Iterator it(arr.begin());

  Vector<int>::Iterator itt = it++;



  for (auto i : arr) {
    std::cout << i << " ";
  }


  A d;
  d.x = 3;

  Vector<A> vec;
  vec.push_back(d);
  Vector<A>::Iterator iter = vec.begin();




  it += 3;
  it -= 2;
  it[3] = 10000;
  std::cout << *(it += 3);




  return 0;
}