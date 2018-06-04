#pragma once
#ifndef DEQUE
#define DEQUE

#include <cstdlib>
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
    int alloc_memory_len = 10;
    int first_index= 4, last_index= 5;
    void reallocate();
public:
    Deque();
    Deque(int len);
    Deque(int len, T default_value);
    Deque(DequeIterator<T> beg, DequeIterator<T> end);
    Deque(std::initializer_list<T> values);
    Deque(const Deque& other_deque);
    Deque(Deque && deq);
    ~Deque();

    T& at(int idx);
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


    T& operator [](int idx);
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
    alloc_memory_len = length;
    this -> data = new T [alloc_memory_len];
}

template<class T>
Deque<T>::Deque(int len, T default_value) {
    this -> length = len;
    alloc_memory_len = length;
    first_index = alloc_memory_len/2 -1;
    last_index = alloc_memory_len/2;
    this -> data = new T [alloc_memory_len];
    for (int i = first_index; i < last_index; i ++){
        this -> data[i] = default_value;
    }
}

template<class T>
Deque<T>::Deque(DequeIterator<T> beg, DequeIterator<T> end) {
    this -> data = new T [alloc_memory_len];
    this -> length =0;
    for (auto i = beg; i < end; i++){
       this -> PushBack(*i);
    }
}

template<class T>
Deque<T>::Deque(initializer_list<T> values) {
    this -> length = 0;
    this -> data = new T [alloc_memory_len];
    for (auto i = values.begin(); i < values.end(); i++){
        this -> PushBack(*i);
    }
}

template<class T>
Deque<T>::Deque(const Deque &other_deque) {
    this -> alloc_memory_len = other_deque.alloc_memory_len;
    this -> first_index = other_deque.first_index;
    this -> last_index = other_deque.last_index;
    this -> data = new T [alloc_memory_len];
    for (int i = other_deque.first_index; i < other_deque.last_index;++i) {
        this -> PushBack(other_deque.data[i]);
    }
}

template<class T>
Deque<T>::Deque(Deque &&deq) {
    this -> length = deq.length;
    this -> data = deq.data;
    deq.data = nullptr;
    this -> first_index = deq.first_index;
    this -> last_index = deq.last_index;
}

template<class T>
Deque<T>::~Deque() {
    delete [] this -> data;
}

template<class T>
T &Deque<T>::at(int idx) {
    if (idx >= this -> length || idx < 0) throw OutOfRangeException(idx);
    return this -> data[idx+first_index];
}

template<class T>
const T &Deque<T>::at(int idx) const {
    if (idx >= this -> length || idx < 0) throw OutOfRangeException(idx);
    return this -> data[idx+first_index];
}

template<class T>
DequeIterator<T> Deque<T>::Begin() {
    return DequeIterator<T>(*this, 0);
}

template<class T>
DequeIterator<T> Deque<T>::End() {
    return DequeIterator<T>(*this, this -> length -1);
}

template<class T>
void Deque<T>::PushBack(T elem) {
    if(last_index > alloc_memory_len){
        this -> reallocate();
    }
    this -> length ++;
    this -> data[this -> last_index-1] = elem;
    this -> last_index ++;
}

template<class T>
T Deque<T>::PopBack() {
    this -> length --;
    this -> last_index --;
    return this -> data[this -> last_index-1];
}

template<class T>
void Deque<T>::PushFront(T elem) {
    if(this -> first_index - 1 < 0){
        this -> reallocate();
        for (int i = first_index; i < last_index; ++i) {
            data[i+100] = data[i];
        }
        first_index+=100;
        last_index += 100;
    }
    this -> length++;
    data[--first_index] = elem;
}

template<class T>
T Deque<T>::PopFront() {
    this -> length --;
    return this -> data[first_index++];
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, T elem) {
    if(this -> length + 1 > alloc_memory_len){
        this -> reallocate();
    }
    this -> length ++;
    for (int i = this -> length-1; i > (pos.position - this->data); --i) {
        this-> data[i] = this -> data[i-1];
    }
    this->data[(pos.position-this->data)]=elem;
    this -> last_index ++;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end) {
    int delta = (int)(end.position - beg.position);
    if(this -> first_index + length + delta > alloc_memory_len){
        this -> reallocate();
    }
    this -> length += delta;
    this -> last_index += delta;
    for (int i = first_index + this -> length; i > first_index + ((pos.position - this -> data )+ delta-1); --i) {
        this -> data[i] = this-> data[i-delta];
    }
    for (int j = first_index + (pos.position - this -> data); j < first_index + ((pos.position - this -> data) + delta) ; ++j) {
        this -> data[j] = *beg;
        beg++;
    }
}

template<class T>
void Deque<T>::Erase(DequeIterator<T> pos) {
    this-> length --;
    for (int i =(int) (first_index + (pos.position - this -> data)); i < first_index + this -> length; ++i) {
        this -> data[i] = this -> data [i+1];
    }
    last_index --;
}

template<class T>
void Deque<T>::Resize(int num) {
    while(num > alloc_memory_len){
        this -> reallocate();
    }
    this -> last_index = first_index + num;
    this -> length = num;
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
    this -> first_index = alloc_memory_len/2-1;
    this -> last_index = alloc_memory_len/2;
}


template<class T>
T &Deque<T>::operator[](int idx) {
    return this -> data[first_index + idx];
}

template<class T>
const T &Deque<T>::operator[](int idx) const {
    return this -> data[first_index + idx];
}

template<class T>
Deque<T>& Deque<T>::operator = (const Deque &deq) {
    this -> alloc_memory_len = deq.alloc_memory_len;
    this -> data = new T [alloc_memory_len];
    for (int i = deq.first_index; i < deq.last_index;++i) {
        this -> PushBack(deq.data[i]);
    }
    return *this;
}

template<class T>
Deque<T>& Deque<T>::operator = (Deque &&deq){
    this -> length = deq.length;
    this -> data = deq.data;
    deq.data = nullptr; // формально в этом и заключается перенос типа я в указатель данных из одной деки присваиваю указатель другой я хз, честно, говори с преподом
    this -> alloc_memory_len = deq.alloc_memory_len;
    this -> first_index = deq.first_index;
    this -> last_index = deq.last_index;
    return *this;
}

template<class T>
void Deque<T>::reallocate() {
    this -> alloc_memory_len +=1;
    this -> data = (T*)(realloc(this -> data, this -> alloc_memory_len*sizeof(T)));
}

#endif