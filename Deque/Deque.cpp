#include <iostream>
#include <initializer_list>


///--------DECLARATION CLASS DEQUE---------------------------------------------------------------///
template <typename T>
class Deque {
	T** arrayOfPointers;

	struct First {
		size_t pointerToFirstArray;
		size_t pointerToFirstElement;
	} first;
	struct Last {
		size_t pointerToLastArray;
		size_t pointerToLastElement;
	} last;

	size_t capacity;
	size_t dequeSize;

	void resize();
public:
	Deque();
	Deque(const std::initializer_list<T>& list);
	void reset(Deque& obj);
	void push_back(T Value);
	void push_front(T Value);
	void pop_back();
	void pop_front();
	size_t size() const;
	bool empty() const;
	void clear();
	class Iterator;
	Iterator begin() const;
	Iterator end() const;
};


///------------IMPLEMENTATION OF FUNCTIONS-------------------------------------------------------///
template <typename T>
Deque<T>::Deque() {
	dequeSize = 0;
	capacity = 100;
	arrayOfPointers = new T*[1];
	arrayOfPointers[0] = new T[100]();
	first = { 0, 0 };
	last = { 0, 1 };
}

template <typename T>
Deque<T>::Deque(const std::initializer_list<T>& list) {
	dequeSize = 0;
	capacity = 100;
	arrayOfPointers = new T * [1];
	arrayOfPointers[0] = new T[100]();
	first = { 0, 0 };
	last = { 0, 1 };
	for (auto& elem : list) {
		this->push_back(elem);
	}
}

template <typename T>
void Deque<T>::reset(Deque& obj) {
	obj.dequeSize = 0;
	obj.capacity = 100;
	obj.arrayOfPointers = new T * [1];
	obj.arrayOfPointers[0] = new T[100]();
	obj.first = { 0, 0 };
	obj.last = { 0, 1 };
}

template <typename T>
void Deque<T>::resize() {
	size_t newCap = (size_t)(((capacity / 100) + 1) * 1.5);
	T** temp = new T*[newCap];
	int head = first.pointerToFirstArray;
	size_t total = capacity / 100;
	temp[0] = arrayOfPointers[head];
	for (size_t i = 0; i < total - 1; i++) {
		temp[i + 1] = arrayOfPointers[++head % total];
	}
	for (size_t i = capacity / 100; i < newCap; i++) {
		temp[i] = new T[100]();
	}
	delete[] arrayOfPointers;
	capacity = 100 * (size_t)(((capacity / 100) + 1) * 1.5);
	arrayOfPointers = temp;
}

template <typename T>
void Deque<T>::push_back(T Value) {
	dequeSize++;
	arrayOfPointers[last.pointerToLastArray][last.pointerToLastElement] = Value;
	if (last.pointerToLastElement < 99) last.pointerToLastElement++;                                            // внутри блока
	else if (first.pointerToFirstArray != 0 && last.pointerToLastArray == (capacity / 100) - 1) {               // последний блок, переключаемся на первый блок
		last.pointerToLastArray = 0;
		last.pointerToLastElement = 0;
	}
	else if (first.pointerToFirstArray != last.pointerToLastArray + 1 && last.pointerToLastArray != (capacity / 100) - 1) {   // переключаемся на следующий блок
		last.pointerToLastArray++;
		last.pointerToLastElement = 0;
	}
	else {                                                                                                      // увеличиваем и переключаемся на последний блок
		resize();
		last.pointerToLastArray++;
		last.pointerToLastElement = 0;
	}
}

template <typename T>
void Deque<T>::push_front(T Value) {
	dequeSize++;
	arrayOfPointers[first.pointerToFirstArray][first.pointerToFirstElement] = Value;
	if (first.pointerToFirstElement >= 1) first.pointerToFirstElement--;                                        // внутри блока
	else if (first.pointerToFirstArray == 0 && last.pointerToLastArray != (capacity / 100) - 1) {               // первый блок, переключаемся на послдений блок
		first.pointerToFirstArray = (capacity / 100) - 1;
		first.pointerToFirstElement = 99;
	}
	else if (first.pointerToFirstArray > 1 && first.pointerToFirstArray - 1 != last.pointerToLastArray) {       // переключаемся на предыдущий блок
		first.pointerToFirstArray--;
		first.pointerToFirstElement = 99;
	}
	else {                                                                                                      // увеличиваем и переключаемся на последний блок
		resize();
		first.pointerToFirstArray = (capacity / 100) - 1;
		first.pointerToFirstElement = 99;
	}
}

template <typename T>
void Deque<T>::pop_back() {
	if (!dequeSize) return;
	dequeSize--;
	if (last.pointerToLastElement > 0) {                                                                       // внутри блока
		last.pointerToLastElement--;
	}
	else if (last.pointerToLastArray == 0) {                                                                   // первый блок, переключаемся на послдений блок
		last.pointerToLastArray = (capacity / 100) - 1;
		last.pointerToLastElement = 99;
	}
	else {                                                                                                     // переключаемся на предыдущий блок
		last.pointerToLastArray--;
		last.pointerToLastElement = 99;
	}
}

template <typename T>
void Deque<T>::pop_front() {
	if (!dequeSize) return;
	dequeSize--;
	if (first.pointerToFirstElement < 99) {                                                                     // внутри блока
		first.pointerToFirstElement++;
	}
	else if (first.pointerToFirstArray == (capacity / 100) - 1) {                                               // последний блок, переключаемся на первый блок
		first.pointerToFirstArray = 0;
		first.pointerToFirstElement = 0;
	}
	else {                                                                                                      // переключаемся на следующий блок
		first.pointerToFirstArray++;
		first.pointerToFirstElement = 0;
	}
}

template <typename T>
size_t Deque<T>::size() const {
	return dequeSize;
}

template <typename T>
bool Deque<T>::empty() const {
	return dequeSize;
}

template <typename T>
void Deque<T>::clear() {
	for (size_t i = 0; i < capacity / 100; i++) {
		delete[] arrayOfPointers[i];
	}
	delete[] arrayOfPointers;
	reset(*this);
}


///--------DECLARATION CLASS ITERATOR---------------------------------------------------------------///
template <typename T>
class Deque<T>::Iterator : std::iterator<std::random_access_iterator_tag, T> {
	size_t array;
	size_t element;
	T** iteratorData;
	size_t* iteratorCap;
public:
	Iterator();

	~Iterator();

	Iterator(const Iterator& obj);

	explicit Iterator(size_t arr, size_t elem, T** ptr, size_t* cap);

	bool operator==(const Iterator& obj) const;

	bool operator!=(const Iterator& obj) const;

	T& operator*();

	T* operator->();

	Iterator& operator++();

	Iterator& operator--();

	Iterator operator++(int);

	Iterator operator--(int);

	Iterator operator+(int n) const;

	Iterator operator-(int n) const;

	friend typename Deque<T>::Iterator operator+(int n, const typename Deque<T>::Iterator& obj) {
		int tempA;
		int tempE;
		tempA = (obj.array + (n / 100)) % (*obj.iteratorCap / 100);
		tempA = (tempA + (obj.element + n % 100) / 100) % (*obj.iteratorCap / 100);
		tempE = (obj.element + n % 100) % 100;
		return Iterator(tempA, tempE, obj.iteratorData, (size_t*)&obj.iteratorCap);
	}

	bool operator>(const Iterator& obj);

	bool operator<(const Iterator& obj);

	bool operator>=(const Iterator& obj);

	bool operator<=(const Iterator& obj);

	T& operator[](size_t index);
};


///------------IMPLEMENTATION OF FUNCTIONS-------------------------------------------------------///
template <typename T>
Deque<T>::Iterator::Iterator() : array(0), element(0), iteratorData(nullptr) {};

template <typename T>
Deque<T>::Iterator::~Iterator() {
	iteratorData = nullptr;
}

template <typename T>
Deque<T>::Iterator::Iterator(const Iterator& obj) : array(obj.array), element(obj.element), iteratorData(obj.iteratorData), iteratorCap(obj.iteratorCap) {};

template <typename T>
Deque<T>::Iterator::Iterator(size_t arr, size_t elem, T** ptr, size_t* cap) : array(arr), element(elem), iteratorData(ptr), iteratorCap(cap) {};

template <typename T>
bool Deque<T>::Iterator::operator==(const Iterator& obj) const {
	return (this->array == obj.array && this->element == obj.element && this->iteratorData == obj.iteratorData);
}

template <typename T>
bool Deque<T>::Iterator::operator!=(const Iterator& obj) const {
	return (this->array != obj.array && this->element != obj.element && this->iteratorData != obj.iteratorData);
}

template <typename T>
T& Deque<T>::Iterator::operator*() {
	return iteratorData[array][element];
}

template <typename T>
T* Deque<T>::Iterator::operator->() {
	return *(iteratorData[array][element]);
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator++() {
	if (element + 1 < 100) element++;
	else if (array + 1 > (*iteratorCap / 100) - 1) {
		array = 0;
		element = 0;
	}
	else {
		array++;
		element = 0;
	}
	return *this;
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator--() {
	if (element > 0) {                                                                                         // внутри блока
		element--;
	}
	else if (array == 0) {                                                                                     // первый блок, переключаемся на послдений блок
		array = (*iteratorCap / 100) - 1;
		element = 99;
	}
	else {                                                                                                     // переключаемся на предыдущий блок
		array--;
		element = 99;
	}
	return *this;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator++(int) {
	Iterator temp = *this;
	if (element + 1 < 100) element++;
	else if (array + 1 > (*iteratorCap / 100) - 1) {
		array = 0;
		element = 0;
	}
	else {
		array++;
		element = 0;
	}
	return temp;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator--(int) {
	Iterator temp = *this;
	if (element > 0) {
		element--;
	}
	else if (array == 0) {
		array = (*iteratorCap / 100) - 1;
		element = 99;
	}
	else {
		array--;
		element = 99;
	}
	return temp;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator+(int n) const {
	int tempA;
	int tempE;
	tempA = (array + (n / 100)) % (*iteratorCap / 100);
	tempA = (tempA + (element + n % 100) / 100) % (*iteratorCap / 100);
	tempE = (element + n % 100) % 100;
	return Iterator(tempA, tempE, iteratorData, (size_t*)&iteratorCap);
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator-(int n) const {
	int tempA;
	int tempE;
	int tempN = n;
	if (array * 100 + element < n) {
		int temp = *iteratorCap - 100;
		tempN -= array * 100 + element;
		temp -= tempN;
		tempA = temp / 100;
		tempE = temp % 100;
	}
	else {
		int temp = array * 100 + element;
		temp -= tempN;
		tempA = temp / 100;
		tempE = temp % 100;
	}
	return Iterator(tempA, tempE, iteratorData, (size_t*)&iteratorCap);
}

template <typename T>
bool Deque<T>::Iterator::operator>(const Iterator& obj) {
	return (this->iteratorData[array][element] > obj.iteratorData[obj.array][obj.element]);
}

template <typename T>
bool Deque<T>::Iterator::operator<(const Iterator& obj) {
	return (this->iteratorData[array][element] < obj.iteratorData[obj.array][obj.element]);
}

template <typename T>
bool Deque<T>::Iterator::operator>=(const Iterator& obj) {
	return (this->iteratorData[array][element] >= obj.iteratorData[obj.array][obj.element]);
}

template <typename T>
bool Deque<T>::Iterator::operator<=(const Iterator& obj) {
	return (this->iteratorData[array][element] <= obj.iteratorData[obj.array][obj.element]);
}

template <typename T>
T& Deque<T>::Iterator::operator[](size_t index) {
	return *(*this + index);
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::begin() const {
	if (dequeSize) {
		size_t tempA = first.pointerToFirstArray;
		size_t tempE = first.pointerToFirstElement;
		if (first.pointerToFirstElement + 1 < 100) tempE++;
		else if (first.pointerToFirstArray + 1 > (capacity / 100) - 1) {
			tempA = 0;
			tempE = 0;
		}
		else {
			tempA++;
			tempE = 0;
		}
		return Iterator(tempA, tempE, arrayOfPointers, (size_t*)&capacity);
	}
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::end() const {
	return Iterator(last.pointerToLastArray, last.pointerToLastElement, arrayOfPointers, (size_t*)&capacity);
}






int main()
{
	Deque<int> pr = {23, 345, 786,2, 5,5,9,34,85,28};



	int x = 0;
	Deque<int>::Iterator it = pr.begin();
	std::cout << it[2];

	for (int i = 0; i < 120; i++) {
		pr.push_back(i);
	}



	pr.push_back(33);

	for (int i = 1; i < 2; i++) pr.push_back(i);


	pr.push_front(23);
	for (int i = 1; i < 104; i++) pr.push_front(i);
	for (int i = 1; i < 120; i++) pr.pop_back();
	

	pr.push_front(23);
	for (int i = 1; i < 100; i++) pr.push_front(i);

	pr.push_front(23);
	pr.push_front(23);
	pr.push_front(23);





	pr.push_back(999);
	pr.push_back(9);
	for (int i = 1; i < 98; i++) pr.push_back(i);
	pr.push_back(999);
	pr.push_back(9);
	pr.push_back(999);
	pr.push_back(9);
	
	pr.clear();



	return 0;
}