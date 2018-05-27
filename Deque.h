#pragma once
#ifndef DEQUE
#define DEQUE

#include <iostream>
#include "DequeIterator.h"
#include "OutOfRangeException.h"

using namespace std;

//template <class T> struct Node{
//    T value;
//    Node<T>* back;
//    Node<T>* forward;
//};

template <class T> class Deque {
private:
    int length;
    T* data;
    const int alloc_memory_len = 100;
public:
    Deque();							//default
    Deque(int len);							//with len
    Deque(int len, T default_value);		//with len and default
    Deque(DequeIterator<T> beg, DequeIterator<T> end);
    Deque(std::initializer_list<T> values);	//init_list
    Deque(const Deque& other_deque);		//copy constructor
    Deque(Deque && deq);
    ~Deque();

    T& at(int idx);           //должно быть реализовано двумя способами (константный и нет). смотри сайт cplusplus.com
    const T& at (int idx) const;
    DequeIterator<T> Begin();
    DequeIterator<T> End();
    void PushBack(T elem);
    T PopBack();
    void PushFront(T elem);
    T PopFront();
    void Insert(DequeIterator<T> pos, T elem);
    void Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end);
    void Erase(DequeIterator<T> pos);
    void Resize(int num);
    bool Empty();
    int Size()const;
    void Clear();

    template <class U>
    friend ostream& operator << (ostream &os, const Deque<U> &obj);

    template <class U>
    friend ostream& operator << (ostream &os, Deque<U> &obj);

    T& operator [](int idx);          //должно быть реализовано двумя способами (константный и нет). смотри сайт cplusplus.com
    const T& operator[](int idx) const;
    Deque& operator = (const Deque& deq);
    Deque& operator = (Deque && deq);

    friend class DequeIterator<T>;
    typedef DequeIterator<T> iterator;

};

template <class T>
Deque<T>::Deque(){
    this -> length = 0;
    this -> data = new T[alloc_memory_len];
}

template<class T>
Deque<T>::Deque(int len) {
    this -> length = len;
    this -> data = new T [alloc_memory_len];
}

template<class T>
Deque<T>::Deque(int len, T default_value) {
    this -> length = len;
    this -> data = new T [alloc_memory_len];
    for (int i = 0; i < len; i ++){
        this -> data[i] = default_value;
    }
}

template<class T>
Deque<T>::Deque(DequeIterator<T> beg, DequeIterator<T> end) {

}

template<class T>
Deque<T>::Deque(initializer_list<T> values) {
    this -> length = values.size();
    this -> data = new T [alloc_memory_len];
    for (auto i = values.begin(); i != values.end(); i++){
        static int idx = 0;
        this -> data[idx] = *i;
        idx++;
    }
}

template<class T>
Deque<T>::Deque(const Deque &other_deque) {

}

template<class T>
Deque<T>::Deque(Deque &&deq) {

}

template<class T>
Deque<T>::~Deque() {
    delete [] this -> data;
}

template<class T>
T &Deque<T>::at(int idx) {
    return this -> data[idx];
}

template<class T>
const T &Deque<T>::at(int idx) const {
    return this -> data[idx];
}

template<class T>
DequeIterator<T> Deque<T>::Begin() {
    return DequeIterator<T>(*this, 0);
}

template<class T>
DequeIterator<T> Deque<T>::End() {
    return DequeIterator<T>(*this, this -> length - 1);
}

template<class T>
void Deque<T>::PushBack(T elem) {
    this -> length += 1;
    this -> data[this -> length -1] = elem;
}

template<class T>
T Deque<T>::PopBack() {
    this -> length --;
    return this -> data[this -> length];
}

template<class T>
void Deque<T>::PushFront(T elem) {
    this -> length ++;
    for (int i = this-> length-1; i > 0 ; --i) {
        this -> data[i] = this -> data[i-1];
    }
    this -> data [0] = elem;
}

template<class T>
T Deque<T>::PopFront() {
    T temp = this -> data [0];
    this -> length --;
    for (int i =0; i < this -> length ; ++i) {
        this -> data[i] = this -> data[i+1];
    }
    return temp;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, T elem) {

}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end) {

}

template<class T>
void Deque<T>::Erase(DequeIterator<T> pos) {
    this -> length --;
    for (auto i = pos; i < this -> End();) {
        *i = *(++i);
    }
}

template<class T>
void Deque<T>::Resize(int num) {

}

template<class T>
bool Deque<T>::Empty() {
    return false;
}

template<class T>
int Deque<T>::Size() const {
    return 0;
}

template<class T>
void Deque<T>::Clear() {

}

template<class U>
ostream &operator<<(ostream &os, const Deque<U> &obj) {
    for (int i = 0; i < obj.length; i++) {
        os << obj.data[i] << ' ';
    }
    return os;
}

template<class U>
ostream &operator<<(ostream &os, Deque<U> &obj) {
    for (int i = 0; i < obj.length; i++) {
        os << obj.data[i] << ' ';
    }
    return os;
}

template<class T>
T &Deque<T>::operator[](int idx) {
    return this -> at(idx);
}

template<class T>
const T &Deque<T>::operator[](int idx) const {
    return this -> at(idx);
}

template<class T>
Deque<T> &Deque<T>::operator=(const Deque &deq) {

}

template<class T>
Deque<T> &Deque<T>::operator=(Deque &&deq) {

}

#endif