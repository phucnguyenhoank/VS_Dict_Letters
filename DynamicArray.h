#pragma once
#include <iostream>

template<class T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;
    void reCapacity(int newCapacity) {
        int oldCapacity = capacity;
        capacity = newCapacity;

        T* needToDel = arr;
        arr = new T[newCapacity];

        int minCapacity = (oldCapacity < newCapacity) ? oldCapacity : newCapacity;

        for (int i = 0; i < minCapacity; i++) {
            arr[i] = needToDel[i];
        }
        for (int i = oldCapacity; i < newCapacity; i++) {
            arr[i] = T();
        }

        delete[] needToDel;
    }
public:

    DynamicArray() {
        arr = new T[0];
        size = 0;
        capacity = 0;
    }

    DynamicArray(int initialCapacity) {
        arr = new T[initialCapacity];
        size = initialCapacity;
        capacity = initialCapacity;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void setAt(int ind, T inf) {
        if (ind >= 0 && ind < size) {
            arr[ind] = inf;
        }
    }

    T getAt(int ind) {
        if (ind >= 0 && ind < size) {
            return arr[ind];
        }
        return T(); // return an exception is default value
    }

    

    void resize(int newSize) {
        if (newSize > capacity) {
            int newCapacity = capacity * 2;  // Double the capacity
            if (newSize > newCapacity) {
                newCapacity = newSize;
            }
            reCapacity(newCapacity);
        }
        size = newSize;
    }


    int getSize() {
        return size;
    }
    int getCapacity() {
        return capacity;
    }

    void remove(int ind) {
        if (ind >= 0 && ind < size) {
            for (int i = ind; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }

    void add(T v) {
        resize(size + 1);
        setAt(size - 1, v);
    }

    void clear() {
        delete[] arr;
        arr = new T[0];
        size = 0;
        capacity = 0;
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
