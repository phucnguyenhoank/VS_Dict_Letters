/*

The main aim of this array is to be used as a hash table
The capacity will be duplicated each time after the size is greater than the capacity

*/

#pragma once
#include <iostream>

template<class T>
class DynamicArray {
private:
    T* arr;         // the pointer will point to a stored data area
    int size;       // the number of elements
    int capacity;   // the largest numbers of elements the array can store

    // keep old values
    // if new capacity is larger than old capacity, the new elements will be set to default values
    void reCapacity(int newCapacity) {
        int oldCapacity = capacity;
        capacity = newCapacity;

        T* needToDel = arr;
        arr = new T[newCapacity];

        int minCapacity = (oldCapacity < newCapacity) ? oldCapacity : newCapacity;

        for (int i = 0; i < minCapacity; i++) {
            arr[i] = needToDel[i];
        }
        //if newCapacity > oldCapacity
        for (int i = oldCapacity; i < newCapacity; i++) {
            arr[i] = T();
        }

        delete[] needToDel;
    }
public:

    // create an array with 0 elements
    DynamicArray() {
        arr = new T[0];
        size = 0;
        capacity = 0;
    }

    // create an array with initalCapacity(>0) elements
    DynamicArray(int initialCapacity) {
        arr = new T[initialCapacity];
        for (int i = 0; i < initialCapacity; i++) arr[i] = T();
        size = initialCapacity;
        capacity = initialCapacity;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    // if ind is not valid, do nothing
    void setAt(int ind, T inf) {
        if (ind >= 0 && ind < size) {
            arr[ind] = inf;
        }
    }

    // if ind is not valid, do nothing
    T getAt(int ind) {
        if (ind >= 0 && ind < size) {
            return arr[ind];
        }
        return T(); // return an exception which is the default value
    }

    // keep old values
    // if new size is larger than old size, the new elements will be set to default values
    void resize(int newSize) {
        if (newSize > capacity) {
            int newCapacity = capacity * 2;  // Double the capacity
            if (newSize > newCapacity) {
                newCapacity = newSize;
            }
            reCapacity(newCapacity);
        }
        for (int i = size; i < newSize; i++) arr[i] = T();
        size = newSize;
    }


    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    // remove an element at ind postion
    // if ind is not valid, do nothing
    void remove(int ind) {
        if (ind >= 0 && ind < size) {
            for (int i = ind; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }

    // add an element with value v to the back of the array
    void add(T v) {
        resize(size + 1);
        setAt(size - 1, v);
    }

    // clear all data and set size, capacity to 0
    void clear() {
        delete[] arr;
        arr = new T[0];
        size = 0;
        capacity = 0;
    }

    // end = the last element will be added after the array have been printed
    // haveEffect = have square brackets and commas
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
