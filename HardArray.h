#pragma once

template<class T, int N>
class HardArray {
private:
	T* arr = new T[N];
	int size = N;
public:
	void setAt(int ind, T inf) {
		arr[ind] = inf;
	}
	T getAt(int ind) {
		return arr[ind];
	}

	HardArray() {
		for (int i = 0; i < N; i++) {
			arr[i] = T();
		}
	}
	~HardArray() {
		delete[] arr;
	}

	void resize(int newSize) {
		int oldSize = this->size;
		this->size = newSize;

		T* needToDel = arr;
		arr = new T[newSize];


		if (newSize < oldSize) {
			for (int i = 0; i < newSize; i++) {
				arr[i] = needToDel[i];
			}
		}
		else {
			for (int i = 0; i < oldSize; i++) {
				arr[i] = needToDel[i];
			}
			for (int i = oldSize; i < newSize; i++) {
				arr[i] = T();
			}
		}

		delete[] needToDel;
	}

	int getSize() {
		return size;
	}

	void add(T v) {
		resize(this->size + 1);
		this->setAt(this->getSize() - 1, v);
	}
	

};
