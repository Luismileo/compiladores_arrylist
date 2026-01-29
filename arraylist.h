#pragma once
#include <iostream>

using namespace std;

template<class T>
class list {
private:
    node<T>* head = nullptr;
    node<T>* tail = nullptr;
    node<T>* current_pos = nullptr;

public:
    list() : head(nullptr), tail(nullptr), current_pos(nullptr) {}
    ~list();
    void add(T);
    T get(T);
    void remove(T);
    void print();
    T first();
    T last();
    int size();
    void reset_cursor() { current_pos = head; }
    T next();
    T prior();
};

template<class T>
list<T>::~list() {
    node<T>* current = head;
    while (current) {
        node<T>* next = current->getNext();
        delete current;
        current = next;
    }
}

template<class T>
void list<T>::add(T data) {
    node<T>* newnode = new node<T>(data);
    if (!head) {
        head = tail = current_pos = newnode;
    } else {
        tail->setNext(newnode);
        newnode->setPrev(tail);
        tail = newnode;
    }
}

template<class T>
T list<T>::get(T data) {
    node<T>* current = head;
    while (current) {
        if (current->getData() == data) return current->getData();
        current = current->getNext();
    }
    throw runtime_error("Elemento no encontrado");
}

template<class T>
void list<T>::remove(T data) {
    node<T>* current = head;
    while (current) {
        if (current->getData() == data) {
            if (current->getPrev()) current->getPrev()->setNext(current->getNext());
            else head = current->getNext();

            if (current->getNext()) current->getNext()->setPrev(current->getPrev());
            else tail = current->getPrev();

            if (current == current_pos) current_pos = head;
            
            delete current;
            return;
        }
        current = current->getNext();
    }
}

template<class T>
T list<T>::next() {
    if (!current_pos) throw runtime_error("Cursor no valido");
    T data = current_pos->getData();
    if (current_pos->getNext()) current_pos = current_pos->getNext();
    return data;
}

template<class T>
T list<T>::prior() {
    if (!current_pos) throw runtime_error("Cursor no valido");
    T data = current_pos->getData();
    if (current_pos->getPrev()) current_pos = current_pos->getPrev();
    return data;
}

template<class T>
void list<T>::print() {
    node<T>* curr = head;
    while (curr) {
        curr->print();
        curr = curr->getNext();
    }
    cout << endl;
}

template<class T>
T list<T>::first() {
    if (!head) throw runtime_error("Lista vacia");
    return head->getData();
}

template<class T>
T list<T>::last() {
    if (!tail) throw runtime_error("Lista vacia");
    return tail->getData();
}

template<class T>
int list<T>::size() {
    int count = 0;
    node<T>* curr = head;
    while (curr) {
        count++;
        curr = curr->getNext();
    }
    return count;
}