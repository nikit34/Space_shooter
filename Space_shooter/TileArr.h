#pragma once

#include"Tile.h" 


template<typename T>
class TileArr {
public:
	TileArr(unsigned cap);
	TileArr(const TileArr& obj);
	virtual~TileArr();

	T& operator[](const unsigned index);
	void operator=(const TileArr& obj);

	inline unsigned size() const { return this->cap; }
	inline unsigned getNrOfTiles() const { return this->nrOfTiles; }
	bool isNull(const unsigned index);
	void push(const T tile, const unsigned index);
	void remove(const unsigned index);
private:
	unsigned cap;
	unsigned nrOfTiles;
	T** tiles;
	void initialize(unsigned from);
};

template<typename T>
TileArr<T>::TileArr(unsigned cap) {
	this->cap = cap;
	this->nrOfTiles = 0;
	this->tiles = new T * [this->cap];
	this->initialize(0);
}

template<typename T>
TileArr<T>::TileArr(const TileArr& obj) {
	this->cap = obj.cap;
	this->nrOfTiles = obj.nrOfTiles;

	this->tiles = new T * [this->cap];

	for (size_t i = 0; i < this->cap; i++) {
		if (obj.tiles[i] != nullptr)
			this->tiles[i] = new Tile(*obj.tiles[i]);
		else
			this->tiles[i] = nullptr;
	}
}

template<typename T>
TileArr<T>::~TileArr() {
	for (size_t i = 0; i < this->cap; i++) {
		delete this->tiles[i];
	}
	delete[] this->tiles;
}

template<typename T>
T& TileArr<T>::operator[](const unsigned index) {
	if (index < 0 || index >= this->cap)
		throw"OUT OF DOUNDS OPERATOR[] TILEARR.";
	
	return *this->tiles[index];
}

template<typename T>
void TileArr<T>::operator=(const TileArr& obj) {
	for (size_t i = 0; i < this->cap; i++) {
		delete this->tiles[i];
	}
	delete[] this->tiles;

	this->cap = obj.cap;
	this->nrOfTiles = obj.nrOfTiles;
	this->tiles = new Tile * [this->cap];
	for (size_t i = 0; i < this->cap; i++) {
		if (obj.tiles[i] != nullptr)
			this->tiles[i] = new Tile(*obj.tiles[i]);
		else
			this->tiles[i] = nullptr;
	}
}

template<typename T>
void TileArr<T>::initialize(unsigned from) {
	for (size_t i = from; i < this->cap; i++) {
		this->tiles[i] = nullptr;
	}
}

template<typename T>
bool TileArr<T>::isNull(const unsigned index) {
	if (index < 0 || index >= this->cap)
		throw"OUT OF DOUNDS TILEARR ISNULL.";
	return this->tiles[index] == nullptr;
}

template<typename T>
void TileArr<T>::push(const T tile, const unsigned index) {
	if (index < 0 || index >= this->cap)
		throw"OUT OF DOUNDS TILEARR PUSH.";

	this->tiles[index] = new T(tile);
	this->nrOfTiles++;
}

template<typename T>
void TileArr<T>::remove(const unsigned index) {
	if (index < 0 || index >= this->cap)
		throw"OUT OF DOUNDS TILEARR REMOVE.";

	delete this->tiles[index];
	this->tiles[index] = nullptr;
	this->nrOfTiles--;
}

// Resize