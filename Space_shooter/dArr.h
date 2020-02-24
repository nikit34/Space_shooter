#pragma once


template<typename T>
class dArr {
private:
	unsigned cap;
	unsigned nrOfEl;
	T** arr;

	void initialize(unsigned from);
	void expand();
public:
	dArr(unsigned size = 5);
	~dArr();

	T& operator[](int index);

	void add(const T element);
	void remove(int index);
	unsigned getSize() const;
	void clear();
};

template<typename T>
dArr<T>::dArr(unsigned cap) {
	this->cap = cap;
	this->nrOfEl = 0;

	this->arr = new T * [this->cap];

	this->initialize(0);
}

template<typename T>
dArr<T>::~dArr() {
	for (size_t i = 0; i < this->nrOfEl; i++) {
		delete this->arr[i];
	}
	delete[] this->arr;
}

template<typename T>
T& dArr<T>::operator[](int index) {
	if (index < 0 || index >= this->nrOfEl)
		throw("OUT OF BOUNDS EXEPTION!");
	return *this->arr[index];
}

template<typename T>
void dArr<T>::initialize(unsigned from) {
	for (size_t i = from; i < this->cap; i++) {
		this->arr[i] = nullptr;
	}
}

template<typename T>
void dArr<T>::expand() {
	this->cap *= 2;
	T** tempArr = new T * [this->cap];
	for (size_t i = 0; i < this->nrOfEl; i++) {
		tempArr[i] = this->arr[i];
	}
	delete[] this->arr;
	this->arr = tempArr;
	initialize(this->nrOfEl);
}

template<typename T>
void dArr<T>::add(const T element) {
	if (this->nrOfEl >= this->cap)
		this->expand();

	this->arr[this->nrOfEl++] = new T(element);
}

template<typename T>
void dArr<T>::remove(int index) {
	if (index < 0 || index >= this->nrOfEl)
		throw("OUT OF BOUNDS EXEPTION!");
	delete this->arr[index];
	for (size_t i = index; i < this->nrOfEl - 1; i++) {
		this->arr[i] = this->arr[i + 1];
	}
	this->arr[nrOfEl--] = nullptr;
}

template<typename T>
unsigned dArr<T>::getSize() const {
	return this->nrOfEl;
}

template<typename T>
void dArr<T>::clear() {
	for (size_t i = 0; i < this->nrOfEl; i++) {
		delete this->arr[i];
	}
	initialize(0);
	this->nrOfEl = 0;
}