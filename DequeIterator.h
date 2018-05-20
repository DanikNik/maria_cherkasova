#pragma once
#ifndef DEQUE_ITER
#define DEQUE_ITER

#include "Deque.h"
#include "OutOfRangeException.h"
using namespace std;

template <class T> class Deque;

template <class T> class DequeIterator {
private:
	T * position;
	int index;
    const Deque<T>* assigned_deque;
public:
    DequeIterator();
	DequeIterator(const Deque<T>& deque, int index);
	DequeIterator(const DequeIterator& other_iter);

	~DequeIterator();

	DequeIterator& operator ++();
	DequeIterator& operator --();
	DequeIterator operator ++(int);
	DequeIterator operator --(int);
	DequeIterator& operator = (const DequeIterator other);

    DequeIterator<T> operator + (int a);
    DequeIterator<T> operator - (int a);
    DequeIterator<T> operator += (int a);
    DequeIterator<T> operator -= (int a);
    template <class S>
    friend bool operator ==(DequeIterator<S>& first, DequeIterator<S>& second);
    template <class S>
    friend bool operator != (DequeIterator<S>& first, DequeIterator<S>& second);
    template <class S>
    friend bool operator > (DequeIterator<S>& first, DequeIterator<S>& second);
    template <class S>
    friend bool operator < (DequeIterator<S>& first, DequeIterator<S>& second);
    template <class S>
    friend bool operator >= (DequeIterator<S>& first, DequeIterator<S>& second);
    template <class S>
    friend bool operator <= (DequeIterator<S>& first, DequeIterator<S>& second);
    //TODO: -> operator
	T& operator *();
};



template<class T>
DequeIterator<T>::DequeIterator() {}

template<class T>
DequeIterator<T>::DequeIterator(const Deque<T>& deque, int index){
    this -> assigned_deque = &deque;
    this -> index = index;
	this -> position = &deque.data[index];
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator++(){
    if (index+1 >= this -> assigned_deque -> Size()){
        throw OutOfRangeException();
    }
    this -> index++;
	this -> position = position + 1;
	return *this;
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator--(){
    if (index-1 < 0){
        throw OutOfRangeException();
    }
	this -> index--;
    this->position = position - 1;
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
T& DequeIterator<T>::operator*(){
	return *(this -> position);
}

template <class T>
DequeIterator<T>::~DequeIterator(){
//	cout << "destruct iter\n";
}

template<class S>
bool operator==(DequeIterator<S>& first, DequeIterator<S>& second) {
    return first.position == second.position;
}

template<class S>
bool operator!=(DequeIterator<S> &first, DequeIterator<S> &second) {
    return !(first == second);
}

template<class S>
bool operator>(DequeIterator<S> &first, DequeIterator<S> &second) {
    return (first.assigned_deque == second.assigned_deque && first.index > second.index);
}

template<class S>
bool operator<(DequeIterator<S> &first, DequeIterator<S> &second) {
    return second > first;
}

template<class S>
bool operator>=(DequeIterator<S> &first, DequeIterator<S> &second) {
    return (first.assigned_deque == second.assigned_deque && first.index >= second.index);
}

template<class S>
bool operator<=(DequeIterator<S> &first, DequeIterator<S> &second) {
    return second >= first;
}

template<class T>
DequeIterator<T>& DequeIterator<T>::operator=(const DequeIterator other) {
    this -> index = other.index;
    this -> position = other.position;
    this -> assigned_deque = other.assigned_deque;
}

template<class T>
DequeIterator<T>::DequeIterator(const DequeIterator &other_iter) {
    this -> position = other_iter.position;
    this -> index = other_iter.index;
    this -> assigned_deque = other_iter.assigned_deque;
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator+(int a) {
    if (this -> index + a >= this -> assigned_deque->Size()) throw OutOfRangeException();
    return DequeIterator<T>(*(this -> assigned_deque), this -> index + a);
}

template<class T>
DequeIterator<T> DequeIterator<T>::operator-(int a) {
    if (this -> index - a < 0) throw OutOfRangeException();
    return DequeIterator<T>(*(this -> assigned_deque), this -> index - a);
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