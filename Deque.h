#pragma once
#ifndef DEQUE
#define DEQUE

#include <iostream>
#include "DequeIterator.h"
#include "OutOfRangeException.h"
using namespace std;

template <class T> class Deque {
private:
	int length;
	T* data;
public:
	Deque();							//default
	Deque(int len);							//with len
	Deque(int len, T default_value);		//with len and default
    Deque(DequeIterator<T> beg, DequeIterator<T> end);
	Deque(std::initializer_list<T> values);	//init_list
	Deque(const Deque& other_deque);		//copy constructor
    Deque(Deque && deq);
	~Deque();

	T at(int idx) const;
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
    T& operator [](int idx);
    Deque& operator = (const Deque& deq);
    Deque& operator = (Deque && deq);

    friend class DequeIterator<T>;
    typedef DequeIterator<T> iterator;

};

template <class T>
Deque<T>::Deque(){
    cout << "pure constructor\n";
    this -> length = 0;
    this -> data = nullptr;
}

template<class T>
Deque<T>::Deque(const int len) {
    this->length = len;
    this->data = new T[len];
    for (int i = 0; i < this -> length; i++){
        this -> data [i] = 0;
    }
}

template<class T>
Deque<T>::Deque(int len, T default_value){
    this->length = len;
    this->data = new T[len];
    for (int i = 0; i < len; i++) {
        this -> data[i] = default_value;
    }
}

template<class T>
Deque<T>::Deque(std::initializer_list<T> values) {
	this->length = values.size();
	this -> data = new T [this -> length];
	int a = 0;
	for (auto i = values.begin(); i != values.end(); i++) {
		this->data[a] = *i;
		a++;
	}
}

template<class T>
Deque<T>::Deque(const Deque& other_deque){
	this->length = other_deque.Size();
	this->data = new T[this->length];
	for (int i = 0; i < this->length; i++) {
		this->data[i] = other_deque.at(i);
	}
}

template<class T>
Deque<T>::Deque(Deque &&deq) {
    *this = move(deq);
}

template <class T>
Deque<T>::~Deque() {
    delete [] data;
//    cout << "destruct deque" << endl;
}

template<class T>
T Deque<T>::at(const int idx) const {
    try {
        if (idx < 0 || idx >= this->length) {
            throw OutOfRangeException(idx);
        }
            return data[idx];
    }
    catch(OutOfRangeException){
        cout << "Ooops. OutOfRangeException " << idx << endl;
        return data[0];
    }
}

template<class T>
void Deque<T>::PushBack(T elem) {
    if (this->length == 0) {
        this -> length += 1;
        this->data = new T;
        *data = elem;
    }
    else {
        T *temp = new T[this->length];
        for (int i = 0; i < this->length; i++) {
            temp[i] = this->data[i];
        }
        delete [] this->data;
        this->length += 1;
        this->data = new T[this->length];
        for (int i = 0; i < this->length - 1; ++i) {
            this->data[i] = temp[i];
        }
        this->data[this -> length-1] = elem;
        delete[] temp;
    }
}

template<class T>
T Deque<T>::PopBack() {
    this -> length -= 1;
    T temp_data;
    temp_data = this -> data[this -> length];
    T* temp = new T [this->length];
    for (int i = 0; i < this->length; i++){
        temp[i] = this -> data[i];
    }
    delete [] this -> data;
    this -> data = new T [this->length];
    for (int i = 0; i < this->length; i++){
        this -> data[i] = temp[i];
    }
    delete [] temp;
    return temp_data;
}

template<class T>
void Deque<T>::PushFront(T elem) {
    if (this->length == 0){
        this->length = 1;
        this -> data = new T;
        this -> data[0] = elem;
    }
    else{
        this->length += 1;
        T* temp = new T [this->length];
        for (int i = 1; i < this->length; i++){
            temp[i] = this -> data[i-1];
        }
        temp[0] = elem;
        delete [] this -> data;
        this -> data = new T [this->length];
        for (int i = 0; i < this->length; i++){
            this -> data[i] = temp[i];
        }
        delete [] temp;
    }
}

template<class T>
T Deque<T>::PopFront() {
    this -> length -= 1;
    T temp_data;
    temp_data = this -> data[0];
    T* temp = new T [this->length];
    for (int i = 1; i < this->length; i++){
        temp[i] = this -> data[i-1];
    }
    delete [] this -> data;
    this -> data = new T [this->length];
    for (int i = 0; i < this->length; i++){
        this -> data[i] = temp[i];
    }
    delete [] temp;
    return temp_data;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, T elem) {
    this -> length +=1;
    for (DequeIterator<T> i = this -> End(); i > pos; i--){
        *i = *(i - 1);
    }
    *pos = elem;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end) {
    T * temp = new T [this ->length];
    for (int i = 0; i < this -> length; ++i) {
        temp [i] = this -> data[i];
    }
    int delta = end.index - beg.index;
    delete [] this -> data;
    this -> length += delta;
    this -> data = new T [ this -> length];
    for (int j = 0; j < pos.index; ++j) {
        this -> data [j] = temp [j];
    }
    for (int k = pos.index; k < pos.index + delta; ++k) {
        data [k] = *beg;
        beg++;
    }
    for (int l = pos.index + delta; l < this -> length; ++l) {
        data[l] = temp [l-delta];
    }
}

template <class T>
ostream& operator <<(ostream &os, const Deque<T> &obj) {
    for (int i = 0; i < obj.length; i++) {
        os << obj.data[i] << ' ';
    }
    return os;
}

template<class T>
DequeIterator<T> Deque<T>::Begin() {
    return DequeIterator<T>(*this, 0);
}

template<class T>
DequeIterator<T> Deque<T>::End() {
    return DequeIterator<T>(*this, this -> length-1);
}

template<class T>
int Deque<T>::Size()const {
    return this -> length;
}

template<class T>
void Deque<T>::Clear() {
    this -> length = 0;
    delete [] this -> data;
}

template<class T>
bool Deque<T>::Empty() {
    return !this->length;
}

template<class T>
void Deque<T>::Erase(DequeIterator<T> pos) {
    for (DequeIterator<T> i = pos; i < this -> End(); i++){
        *i = *(++pos);
    }
    this -> length -= 1;
}

template<class T>
T &Deque<T>::operator [] (int idx) {
    try {
        if (idx < 0 || idx >= this->length) {
            throw OutOfRangeException(idx);
        }
        return data[idx];
    }
    catch(OutOfRangeException){
        cout << "Ooops. OutOfRangeException " << idx << endl;
        return data[0];
    }
}

template<class T>
Deque<T>& Deque<T>::operator=(Deque const &deq) {
    this -> length = deq.length;
    delete [] this -> data;
    this -> data = new T [this -> length];
    for (int i = 0; i < this -> length; ++i) {
        this -> data[i] = deq.data[i];
    }
}

template<class T>
Deque<T>& Deque<T>::operator=(Deque &&deq) {
    *this = move(deq);
    return *this;
}

template<class T>
void Deque<T>::Resize(int num) {
    T* temp = new T [this -> length];
    for (int j = 0; j < this -> length; ++j) {
        temp[j] = this -> data[j];
    }
    delete [] this -> data;
    this -> data = new T [num];
    for (int i = 0; i < this->length; ++i) {
        this -> data[i] = temp[i];
    }
    for (int k = this -> length; k < num; ++k) {
        this -> data[k] = 0;
    }
    this -> length = num;
}

template<class T>
Deque<T>::Deque(DequeIterator<T> beg, DequeIterator<T> end) {
    this -> length = 0;
    while (beg != end){
        this -> PushBack(*beg);
        beg++;
    }
}


#endif