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
    T* last;
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
    Deque operator = (const Deque& deq);
    Deque operator = (Deque && deq);

    friend class DequeIterator<T>;
    typedef DequeIterator<T> iterator;

};

template <class T>
Deque<T>::Deque(){
    this -> length = 0;
    this -> data = new T[alloc_memory_len];
    last = data;
}

template<class T>
Deque<T>::Deque(int len) {
    this -> length = len;
    this -> data = new T [alloc_memory_len];
    last = &data[length-1];
}

template<class T>
Deque<T>::Deque(int len, T default_value) {
    this -> length = len;
    this -> data = new T [alloc_memory_len];
    for (int i = 0; i < len; i ++){
        this -> data[i] = default_value;
    }
    last = &data[length-1];
}

template<class T>
Deque<T>::Deque(DequeIterator<T> beg, DequeIterator<T> end) {
    this -> data = new T [alloc_memory_len];
    this -> length =0;
    for (auto i = beg; i < end; i++){
        (*this).PushBack(*i);
    }
}

template<class T>
Deque<T>::Deque(initializer_list<T> values) {
    this -> length = values.size();
    this -> data = new T [alloc_memory_len];
    int idx = 0;
    for (auto i = values.begin(); i < values.end(); i++){
        this -> data[idx] = *i;
        idx++;
    }
    last = &data[length-1];
}

template<class T>
Deque<T>::Deque(const Deque &other_deque) {
    this -> length = other_deque.length;
    this -> data = new T [alloc_memory_len];
    for (int i = 0; i < this -> length; ++i) {
        this -> data[i] = other_deque.data[i];
    }
    last = &data[length-1];
}

template<class T>
Deque<T>::Deque(Deque &&deq) {
    this -> length = deq.length;
    this -> data = deq.data;
    this -> last = deq.last;
}

template<class T>
Deque<T>::~Deque() {
    delete [] this -> data;
}

template<class T>
T &Deque<T>::at(int idx) {
    if (idx >= this -> length || idx < 0) throw OutOfRangeException(idx);
    return this -> data[idx];
}

template<class T>
const T &Deque<T>::at(int idx) const {
    if (idx >= this -> length || idx < 0) throw OutOfRangeException(idx);
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
    this -> length ++;
    this -> data[this -> length-1] = elem;
    last = &data[length-1];
}

template<class T>
T Deque<T>::PopBack() {
    this -> length --;
    last = &data[length-1];
    return this -> data[this -> length];
}

template<class T>
void Deque<T>::PushFront(T elem) {
    this -> length ++;
    for (int i = this-> length-1; i > 0 ; --i) {
        this -> data[i] = this -> data[i-1];
    }
    this -> data [0] = elem;
    last = &data[length-1];
}

template<class T>
T Deque<T>::PopFront() {
    T temp = this -> data [0];
    this -> length --;
    for (int i =0; i < this -> length ; ++i) {
        this -> data[i] = this -> data[i+1];
    }
    last = &data[length-1];
    return temp;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, T elem) {
    this -> length ++;
    for (int i = this -> length-1; i > (pos.position - this->data); --i) {
        this-> data[i] = this -> data[i-1];
    }
    this->data[(pos.position-this->data)]=elem;
    last = &data[length-1];
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end) {
    int delta = (end.position - beg.position);
    this -> length += delta;
    for (int i = this -> length; i > ((pos.position - this -> data )+ delta-1); --i) {
        this -> data[i] = this-> data[i-delta];
    }
    for (int j = (pos.position - this -> data); j < ((pos.position - this -> data) + delta) ; ++j) {
        this -> data[j] = *beg;
        beg++;
    }
    last = &data[length-1];
}

template<class T>
void Deque<T>::Erase(DequeIterator<T> pos) {
    this-> length --;
    for (int i = (pos.position - this -> data); i < this -> length; ++i) {
        this -> data[i] = this -> data [i+1];
    }
    last = &data[length-1];
}

template<class T>
void Deque<T>::Resize(int num) {
    this -> length = num;
    last = &data[length-1];
}

template<class T>
bool Deque<T>::Empty() {
    return !(this -> length);
}

template<class T>
int Deque<T>::Size() const {
    return this -> length;
}

template<class T>
void Deque<T>::Clear() {
    this -> length = 0;
    delete [] this -> data;
    this -> data = new T [this -> alloc_memory_len];
    last = data;
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
Deque<T> Deque<T>::operator = (const Deque &deq) {
    return Deque<T>(deq);
}

template<class T>
Deque<T> Deque<T>::operator = (Deque &&deq) {
    return Deque<T>(deq);
}

#endif