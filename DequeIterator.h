#pragma once
#ifndef DEQUE_ITER
#define DEQUE_ITER

#include "Deque.h"
#include "OutOfRangeException.h"
using namespace std;

template <class T> struct Node;


template <class T>
class Deque;

template <class T> class DequeIterator {
private:
    Node<T> * position;                           //тут он сказал, что нет смысла делать и позицию, и индекс, нужно оставить что-то одно
    int index;
    const Deque<T>* assigned_deque;
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
    this -> assigned_deque = nullptr;
    this -> index = 0;
}

template<class T>
DequeIterator<T>::DequeIterator(Deque<T>& deque, int index) {
    this->assigned_deque = &deque;
    this->index = index;
    this->position = deque.first;
    for (int i = 1; i <=index; i++){
        this -> position = this -> position-> forward;
    }
}

template<class T>
DequeIterator<T>::DequeIterator(const DequeIterator<T>& other_iter) {
    this->position = other_iter.position;
    this->index = other_iter.index;
    this->assigned_deque = other_iter.assigned_deque;
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator++() {
    if (index + 1 >= this->assigned_deque->Size()) {
        throw OutOfRangeException();
    }
    this->index++;
    this->position = position -> forward;
    return *this;
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator--() {
    if (index - 1 < 0) {
        throw OutOfRangeException();
    }
    this->index--;
    this->position = position -> back;
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
    return this->position->value;
}

template <class T>
DequeIterator<T>::~DequeIterator() {
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
    return (first.assigned_deque == second.assigned_deque && first.index > second.index);
}

template<class S>
bool operator<(DequeIterator<S> first, DequeIterator<S> second) {
    return second > first;
}

template<class S>
bool operator>=(DequeIterator<S> first, DequeIterator<S> second) {
    return (first.assigned_deque == second.assigned_deque && first.index >= second.index);
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
    if (this->index + a >= this->assigned_deque->Size()) throw OutOfRangeException();
    return DequeIterator<T>(*(this->assigned_deque), this->index + a);
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator-(int a) {
    if (this->index - a < 0) throw OutOfRangeException();
    return DequeIterator<T>(*(this->assigned_deque), this->index - a);
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