#pragma once
#include <iostream>

template<class T>
class DynamicArray {
private:
	T* arr;
	int size;
public:

	DynamicArray() {
		arr = new T[0];
		size = 0;
	}
	~DynamicArray() {
		delete[] arr;
	}

	void setAt(int ind, T inf) {
		arr[ind] = inf;
	}

	T getAt(int ind) {
		return arr[ind];
	}


	void resize(int newSize) {
		int oldSize = size;
		size = newSize;

		T* needToDel = arr;
		arr = new T[newSize];

		int minSize = (oldSize < newSize) ? oldSize : newSize;

		for (int i = 0; i < minSize; i++) {
			arr[i] = needToDel[i];
		}
		for (int i = oldSize; i < newSize; i++) {
			arr[i] = T();
		}

		delete[] needToDel;
	}

	int getSize() {
		return size;
	}

	void remove(int ind) {
		for (int i = ind; i < size - 1; i++) {
			arr[i] = arr[i + 1];
		}
		size--;
		resize(size);
	}

	void add(T v) {
		resize(size + 1);
		setAt(getSize() - 1, v);
	}

	void clear() {
		delete[] arr;
		arr = new T[0];
		size = 0;
	}

	void print(char end = ' ', bool haveEffect = true) {
		if (haveEffect) {
			std::cout << "[";
			for (int i = 0; i < this->getSize(); i++) {
				std::cout << this->getAt(i) << ", ";
			}
			std::cout << "\b\b]" << end;
		}
		else {
			for (int i = 0; i < this->getSize(); i++) {
				std::cout << this->getAt(i) << " ";
			}
			std::cout << end;

		}
	}


};
