#pragma once
#ifndef DEQUE_ITER
#define DEQUE_ITER

#include "OutOfRangeException.h"
using namespace std;

template <class T> class Deque;

template <class T> class DequeIterator {
private:
    T* position;
public:
    DequeIterator();
    DequeIterator(Deque<T> &deque, int index);
    DequeIterator(const DequeIterator<T>& other_iter);

    ~DequeIterator();                         //что-то в деструкторе не устроило

    DequeIterator& operator ++();
    DequeIterator& operator --();
    DequeIterator operator ++(int);
    DequeIterator operator --(int);
    DequeIterator operator = (DequeIterator& other);

    DequeIterator<T> operator + (int a);
    DequeIterator<T> operator - (int a);
    DequeIterator<T> operator += (int a);
    DequeIterator<T> operator -= (int a);
    template <class S>
    friend bool operator ==(DequeIterator<S> first, DequeIterator<S> second);
    template <class S>
    friend bool operator != (DequeIterator<S> first, DequeIterator<S> second);
    template <class S>
    friend bool operator > (DequeIterator<S> first, DequeIterator<S> second);
    template <class S>
    friend bool operator < (DequeIterator<S> first, DequeIterator<S> second);
    template <class S>
    friend bool operator >= (DequeIterator<S> first, DequeIterator<S> second);
    template <class S>
    friend bool operator <= (DequeIterator<S> first, DequeIterator<S> second);
    T& operator *();

    friend class Deque<T>;
};



template<class T>                            //в конструкторе надо изначально выделять хоть какую-то память
DequeIterator<T>::DequeIterator() {
    this -> position = nullptr;
}

template<class T>
DequeIterator<T>::DequeIterator(Deque<T>& deque, int index) {
    this -> position = &deque.data[index];
}

template<class T>
DequeIterator<T>::DequeIterator(const DequeIterator<T>& other_iter) {
    this -> position = other_iter.position;
}

template <class T>
DequeIterator<T>::~DequeIterator() {}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator++() {
    this -> position++;
    return *this;
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator--() {
    this -> position--;
    return *this;
}

template<class T>
DequeIterator <T>DequeIterator<T>::operator++(int) {
    DequeIterator temp = *this;
    ++*this;
    return temp;
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator--(int) {
    DequeIterator temp = *this;
    --*this;
    return temp;
}

template<class T>
T& DequeIterator<T>::operator*() {
    return *(this->position);
}

template<class S>
bool operator==(DequeIterator<S> first, DequeIterator<S> second) {
    return first.position == second.position;
}

template<class S>
bool operator!=(DequeIterator<S> first, DequeIterator<S> second) {
    return !(first == second);
}

template<class S>
bool operator>(DequeIterator<S> first, DequeIterator<S> second) {
    return first.position > second.position;
}

template<class S>
bool operator<(DequeIterator<S> first, DequeIterator<S> second) {
    return second > first;
}

template<class S>
bool operator>=(DequeIterator<S> first, DequeIterator<S> second) {
    return first.position >= second.position;
}

template<class S>
bool operator<=(DequeIterator<S> first, DequeIterator<S> second) {
    return second >= first;
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator=(DequeIterator& other) {
    return DequeIterator(other);
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator+(int a) {
    this -> position += a;
    return *this;
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator-(int a) {
    this -> position -= a;
    return *this;
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator+=(int a) {
    return (*this + a);
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator-=(int a) {
    return (*this - a);
}


#endif