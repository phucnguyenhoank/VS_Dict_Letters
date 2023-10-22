#pragma once
#include <iostream>

template<class T, int N>
class NodeList {
public:
    T* arr = new T[N];

    void setAt(int n, T inf) {
        arr[n] = inf;
    }
    T getAt(int n) {
        return arr[n];
    }

};
