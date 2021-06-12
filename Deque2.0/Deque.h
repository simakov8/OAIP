#pragma once

template <typename T>
class Deque {
private:
	//----CLASS BLOCK------------------------------------------------//
	class Block {
	public:
		size_t indexOfBlock;
		T* arrayOfElements;
		Block(size_t index) {
			this->indexOfBlock = index;
			arrayOfElements = new T[32]();
		}
		void change(size_t index) {
			this->indexOfBlock = index;
		}
		void setValue(T Value, size_t index) {
			this->arrayOfElements[index] = Value;
		}
		T& get(size_t index) {
			return arrayOfElements[index];
		}
		size_t getIndex() {
			return indexOfBlock;
		}
	};
	//----END CLASS BLOCK--------------------------------------------//
	Block** arrayOfBlocks;
	size_t numOfBlocks;
	size_t dequeSize;


	struct First
	{
		size_t indexOfBlock;
		size_t indexOfElement;
	} first;
	struct Last
	{
		size_t indexOfBlock;
		size_t indexOfElement;
	} last;

	void resize() {
		Block** temp = new Block * [numOfBlocks + 31];
		size_t tempIter = first.indexOfBlock;
		for (size_t i = 0; i < numOfBlocks; i++) {
			temp[i] = arrayOfBlocks[tempIter % numOfBlocks];
			arrayOfBlocks[tempIter++]->change(i);
		}
		for (size_t i = numOfBlocks; i < numOfBlocks + 31; i++) {
			temp[i] = new Block(i);
		}
		numOfBlocks += 31;
		delete[] arrayOfBlocks;
		arrayOfBlocks = temp;
	}

public:
	Deque() {
		this->arrayOfBlocks = new Block * [1];
		this->arrayOfBlocks[0] = new Block(32);
		this->numOfBlocks = 1;
		this->dequeSize = 0;
		this->first.indexOfBlock = 0;
		this->first.indexOfElement = 0;
		this->last.indexOfBlock = 0;
		this->last.indexOfElement = 1;
	}

	void push_back(T Value) {
		if (!dequeSize) {
			dequeSize++;
			arrayOfBlocks[first.indexOfBlock]->setValue(Value, first.indexOfElement);
			return;
		}
		dequeSize++;
		arrayOfBlocks[last.indexOfBlock]->setValue(Value, last.indexOfElement);
		if (last.indexOfElement < 31) last.indexOfElement++;                                                                            // внутри блока
		else if (last.indexOfBlock == numOfBlocks - 1 && first.indexOfBlock != 0) last.indexOfBlock = last.indexOfElement = 0;          // последний блок, переключаемся на первый
		else if (last.indexOfBlock + 1 != first.indexOfBlock && last.indexOfBlock != numOfBlocks - 1) {                                 // переключамся на след. блок
			last.indexOfBlock++;
			last.indexOfElement = 0;
		}
		else {
			resize();
			last.indexOfBlock++;
			last.indexOfElement = 0;
		}
	}

	void push_front(T Value) {
		if (!dequeSize) {
			dequeSize++;
			arrayOfBlocks[first.indexOfBlock]->setValue(Value, first.indexOfElement);
			return;
		}
		dequeSize++;
		if (first.indexOfElement > 0) first.indexOfElement--;                                                                           // внутри блока
		else if (first.indexOfBlock == 0 && last.indexOfBlock != numOfBlocks - 1) {                                                     // первый блок, переключаемся на последний
			first.indexOfBlock = numOfBlocks - 1;
			first.indexOfElement = 31;
		}
		else if (first.indexOfBlock - 1 != last.indexOfBlock && first.indexOfBlock != 0) {                                              // переключамся на пред. блок
			first.indexOfBlock--;
			first.indexOfElement = 31;
		}
		else {
			resize();
			first.indexOfBlock++;
			first.indexOfElement = 31;
		}
		arrayOfBlocks[first.indexOfBlock]->setValue(Value, first.indexOfElement);
	}

	void pop_back() {
		if (!dequeSize) return;
		dequeSize--;
		if (last.indexOfElement > 0) last.indexOfElement--;                                                                             // внутри блока
		else if (last.indexOfBlock == 0) {                                                                                              // первый блок, переключаемся на последний
			last.indexOfBlock = numOfBlocks - 1;
			last.indexOfElement = 31;
		}
		else {                                                                                                                          // переключамся на пред. блок
			last.indexOfBlock++;
			last.indexOfElement = 0;
		}
	}

	void pop_front() {
		if (!dequeSize) return;
		dequeSize--;
		if (first.indexOfElement < 31) first.indexOfElement++;                                                                          // внутри блока
		else if (first.indexOfBlock == numOfBlocks - 1) first.indexOfBlock = first.indexOfElement = 0;                                  // последний блок, переключаемся на первый
		else {                                                                                                                          // переключамся на след. блок
			first.indexOfBlock++;
			first.indexOfElement = 0;
		}
	}

	size_t size() {
		return dequeSize;
	}

	bool empty() {
		return dequeSize;
	}

	Block** getArr() {
		return arrayOfBlocks;
	}

	size_t getNum() {
		return numOfBlocks;
	}



	//----CLASS ITERATOR-----------------------------------------------------------//
	class Iterator : std::iterator<std::random_access_iterator_tag, T> {
	private:
		Deque* ptrToDeque;
		Block* ptrToBlock;
		size_t indexOfElement;
	public:
		Iterator() : ptrToBlock(nullptr), indexOfElement(0) {};
		Iterator(Deque* ptrD, Block* ptrB, size_t index) : ptrToDeque(ptrD), ptrToBlock(ptrB), indexOfElement(index) {}
		~Iterator() {
			ptrToBlock = nullptr;
		}
		Iterator(const Iterator& obj) {
			this->ptrToBlock = obj.ptrToBlock;
			this->indexOfElement = obj.indexOfElement;
			this->ptrToDeque = obj.ptrToDeque;
		}
		bool operator==(const Iterator& obj) const {
			return (this->ptrToBlock == obj.ptrToBlock && this->indexOfElement == obj.indexOfElement);
		}
		bool operator!=(const Iterator& obj) const {
			return !(this->ptrToBlock == obj.ptrToBlock && this->indexOfElement == obj.indexOfElement);
		}
		T& operator*() {
			return ptrToBlock->get(indexOfElement);
		}
		T* operator->() {
			return &ptrToBlock->get(indexOfElement);
		}
		Iterator& operator++() {
			if (indexOfElement < 31) indexOfElement++;
			else {
				size_t indexOfBlock = this->ptrToBlock->getIndex();
				size_t count = this->ptrToDeque->getNum();
				this->ptrToBlock = this->ptrToDeque->getArr()[(indexOfBlock + 1) % count];
				this->indexOfElement = 0;
			}
			return *this;
		}
		Iterator& operator--() {
			if (indexOfElement > 0) indexOfElement--;
			else {
				size_t indexOfBlock = this->ptrToBlock->getIndex();
				size_t count = this->ptrToDeque->getNum();
				this->ptrToBlock = (indexOfBlock - 1 >= 0) ? (this->ptrToDeque->getArr()[indexOfBlock - 1]) : (this->ptrToDeque->getArr()[count - 1]);       // присваиваем предыдущий или, если был первый блок, то присваиваем последний блок
				this->indexOfElement = 31;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			if (indexOfElement < 31) indexOfElement++;
			else {
				size_t indexOfBlock = this->ptrToBlock->getIndex();
				size_t count = this->ptrToDeque->getNum();
				this->ptrToBlock = this->ptrToDeque->getArr()[(indexOfBlock + 1) % count];
				this->indexOfElement = 0;
			}
			return temp;
		}
		Iterator operator--(int) {
			Iterator temp = *this;
			if (indexOfElement > 0) indexOfElement--;
			else {
				size_t indexOfBlock = this->ptrToBlock->getIndex();
				size_t count = this->ptrToDeque->getNum();
				this->ptrToBlock = (indexOfBlock - 1 >= 0) ? (this->ptrToDeque->getArr()[indexOfBlock - 1]) : (this->ptrToDeque->getArr()[count - 1]);       // присваиваем предыдущий или, если был первый блок, то присваиваем последний блок
				this->indexOfElement = 31;
			}
			return temp;
		}
		T& operator[](size_t index) {
			Iterator temp = *this;
			size_t indexOfBlock = this->ptrToBlock->getIndex();
			temp.ptrToBlock = this->ptrToDeque->getArr()[(indexOfBlock + index / 32) + (this->indexOfElement + index % 32) / 32];
			temp.indexOfElement = (this->indexOfElement + index % 32) % 32;
			return temp.ptrToBlock->get(temp.indexOfElement);
		}
	};
	//----END CLASS ITERATOR-----------------------------------------------------------//



	Iterator begin() {
		return Iterator(this, arrayOfBlocks[first.indexOfBlock], first.indexOfElement);
	}
	Iterator end() {
		return Iterator(this, arrayOfBlocks[last.indexOfBlock], last.indexOfElement);
	}
};
