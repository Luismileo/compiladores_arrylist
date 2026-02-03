#pragma once
#include <iostream>
using namespace std;

template<class T>
class node {
private:
    T data;
    node<T>* next = nullptr;
    node<T>* prev = nullptr;
public:
    node(T data, node<T>* next = nullptr, node<T>* prev = nullptr) : data(data), next(next), prev(prev) {}
    ~node() {}
    T getData() { return data; }
    void setData(T d) { data = d; }
    node<T>* getNext() { return next; }
    void setNext(node<T>* n) { next = n; }
    node<T>* getPrev() { return prev; }
    void setPrev(node<T>* p) { prev = p; }
    void print() { cout << data << " "; }
};