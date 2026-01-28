#pragma once
using namespace std;

template<class T>
class node{
    private:
        T data;
        node<T>* next = nullptr;
        node<T>* prev = nullptr;
    public:
        node(T, node<T>*, node<T>*);
        ~node();
        T getData();
        void setData(T);
        node<T>* getNext();
        void setNext (node<T>*);
        node<T>* getPrev();
        void setPrev (node<T>*);
        void print();
};

template <class T>
node<T>::node( T data, node<T>* next, node<T>* prev){
    this -> data = data;
    this -> next = next;
    this -> prev = prev;
}

template <class T>
node<T>::~node(){
    this -> next = nullptr;
    this -> prev = nullptr;
}

template <class T>
T node<T>::getData(){
    return this -> data;
}

template <class T>
void node<T>::setData(T data){
    this -> data = data;
}

template <class T>
node<T>* node<T>::getNext(){
    return this -> next;
}

template <class T>
void node<T>::setNext(node<T>* next){
    this -> next = next;
}

template <class T>
node<T>* node<T>::getPrev(){
    return this -> prev;
}

template <class T>
void node<T>::setPrev(node<T>* prev){
    this -> prev = prev;
}

template <class T>
void node<T>::print(){
    cout << this -> data << endl;
}



template<class T>
class list{
    private:
        node<T>* head = nullptr;
        node<T>* tail = nullptr;
    public:
        list();
        ~list();
        void add(T);
        T get(T);
        void remove(T);
        void next();
        void prior();
        void print();
        void last();
        void first();
        void size();
};

template<class T>
list<T>::list(){
    this -> head = nullptr;
    this -> tail = nullptr;
}

template<class T>
list<T>::~list(){
    this -> head = nullptr;
    this -> tail = nullptr;
}

template<class T>
void list<T>::add(T data){

}

template<class T>
T list<T>::get(T data){
    return T();
}

template<class T>
void list<T>::remove(T data){

}

template<class T>
void list<T>::next(){}

template<class T>
void list<T>::prior(){}


template<class T>
void list<T>::print(){
    node<T>* current = head;
    while (current){
        current -> print();
        current = current ->getNext();
    }
}

template<class T>
void list<T>::last(){
    if(!tail) throw runtime_error("La lista esta vacia");
    return tail -> getData();
}

template<class T>
void list<T>::first(){
    if(!head) throw runtime_error("La lista esta vacia");
    return head -> getData();
}

template<class T>
void list<T>::size(){
    int count = 0;
    node<T>* current = head;
    while(current){
        count++;
        current = current -> getNext();
    }

}