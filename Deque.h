#pragma once
#ifndef DEQUE
#define DEQUE

#include <iostream>
#include "DequeIterator.h"
#include "OutOfRangeException.h"

using namespace std;

template <class T> struct Node{
    T value;
    Node<T>* back;
    Node<T>* forward;
};

template <class T> class Deque {
private:
    int length;
    Node<T>* first;
    Node<T>* last;
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

template <class T>          //вроде тут что-то не то, но не факт
Deque<T>::Deque() {
    length = 0;
    first = nullptr;
    last = first;
}

template<class T>
Deque<T>::Deque(const int len) {
    for (int i = 0; i < len; ++i) {
        this -> PushBack(0);
    }
}

template<class T>
Deque<T>::Deque(int len, T default_value) {
    for (int i = 0; i < len; ++i) {
        this -> PushBack(default_value);
    }
}

template<class T>
Deque<T>::Deque(std::initializer_list<T> values) {
    this -> length = 0;
    for (auto i = values.begin(); i <values.end(); i ++) {
        this -> PushBack(*i);
    }
}

template<class T>            // вроде тут не обязательно писать this
Deque<T>::Deque(const Deque& other_deque) {
    this -> length = other_deque.length;
    this -> first = other_deque.first;
    this -> last = other_deque.last;
}

template<class T>                           // ??? переделать
Deque<T>::Deque(Deque &&other_deque) {
    this -> length = other_deque.length;
    this -> first = other_deque.first;
    this -> last = other_deque.last;
}

template<class T>
Deque<T>::Deque(DequeIterator<T> beg, DequeIterator<T> end) {
}

template <class T>
Deque<T>::~Deque() {
    for (int i = 0; i < this-> length; i++){
        Node<T>* temp = this -> first;
        delete first;
        first = temp -> forward;
    }
    //recursively delete
}

template<class T>                                // все, что закомментировано, должно находиться в мейне
T& Deque<T>::at(const int idx){
    if (idx >= this -> length || idx < 0) throw OutOfRangeException();
    Node<T>* ret = first;
    for (int i = 1; i <=idx; i++){
        ret = ret -> forward;
    }
    return ret -> value;
}

template<class T>
const T &Deque<T>::at(int idx) const {
    if (idx >= this -> length || idx < 0) throw OutOfRangeException();
    Node<T>* ret = first;
    for (int i = 1; i <=idx; i++){
        ret = ret -> forward;
    }
    return ret -> value;
}

/// ???
template<class T>                                //переделать. слишком сложно. не должно записывать в левый массив. все должно добавляться сразу
void Deque<T>::PushBack(T elem) {
    if (length == 0) {
        length = 1;
        Node<T> *node = new Node<T>;
        node->value = elem;
        node->forward = nullptr;
        node->back = nullptr;
        first = node;
        last = node;
    } else {
        length += 1;
        Node<T> *node = new Node<T>;
        node->value = elem;
        node->forward = nullptr;
        node->back = this->last;
        this->last->forward = node;
        this->last = node;
    }
}

template<class T>                        //по аналогии с предыдущим
T Deque<T>::PopBack() {
    length -=1;
    T ret = this -> last -> value;
    this -> last = this -> last -> back;
    this -> last -> forward = nullptr;
    return ret;
}

template<class T>                                  //по аналогии
void Deque<T>::PushFront(T elem) {
    if (length == 0) {
        length = 1;
        Node<T> *node = new Node<T>;
        node->value = elem;
        node->forward = nullptr;
        node->back = nullptr;
        first = node;
        last = node;
    } else {
        length += 1;
        Node<T> *node = new Node<T>;
        node->value = elem;
        node->back = nullptr;
        node->forward = this->first;
        this -> first -> back = node;
        this->first = node;
    }
}

template<class T>                               //по аналогии
T Deque<T>::PopFront() {
    length -=1;
    T ret = this -> first -> value;
    this -> first = this -> first -> forward;
    return ret;
}

template<class T>
void Deque<T>::Insert(DequeIterator<T> pos, T elem) {
    length +=1;
    Node<T> * new_node = new Node<T>;
    new_node -> back = this -> last;
    this -> last -> forward = new_node;
    this -> last = new_node;
    for (int i = this -> length-1; i > pos.index; i--){
        this -> at(i) = this -> at(i-1);
    }
    this -> at(pos.index) = elem;
}

template<class T>                         //он сказал, что эту сортировку возможно реализовать как-то проще
void Deque<T>::Insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end) {
    for (auto i = beg; i < end; i ++){
        this -> Insert(pos, *i);
        pos ++;
    }
}

template <class T>                               //что-то не то. смотри сайт cplusplus.com или любую литературу
ostream& operator <<(ostream &os, const Deque<T> &obj) {
    for (int i = 0; i < obj.length; i++) {
        os << obj.at(i) << ' ';
    }
    return os;
}

template<class U>
ostream &operator<<(ostream &os, Deque<U> &obj) {
    for (int i = 0; i < obj.length; i++) {
        os << obj.at(i) << ' ';
    }
    return os;
}

template<class T>
DequeIterator<T> Deque<T>::Begin() {
    return DequeIterator<T>(*this, 0);
}

template<class T>
DequeIterator<T> Deque<T>::End() {
    return DequeIterator<T>(*this, this->length - 1);
}

template<class T>
int Deque<T>::Size()const {
    return this->length;
}

template<class T>                             //тут он исправил, все, что закомментировано, не нужно
void Deque<T>::Resize(int num) {
    for (int i = this -> length; i < num; i++){
        length +=1;
        Node<T> * new_node = new Node<T>;
        new_node -> back = this -> last;
        this -> last -> forward = new_node;
        this -> last = new_node;
    }
}
template<class T>
void Deque<T>::Clear() {
    for (int i = 0; i < this-> length; i++){
        Node<T>* temp = this -> first;
        delete first;
        first = temp -> forward;
    }
    this -> length = 0;
    this -> first = nullptr;
    this -> last = nullptr;
}
template<class T>
bool Deque<T>::Empty() {
    return !this->length;
}

template<class T>
void Deque<T>::Erase(DequeIterator<T> pos) {
    for (int i = pos.index; i < this -> length - 1; i++){
        this -> at(i) = this -> at(i+1);
    }
    this -> last = this -> last -> back;
}

template<class T>                                //т.к. оператор индексирования должен реализовываться двумя способами (константный и нет), нужно для второго аналогичное
T &Deque<T>::operator [] (int idx) {
    return this -> at(idx);
}

template<class T>
const T &Deque<T>::operator[](int idx) const {
    return this -> at(idx);
}

/// ???
template<class T>                            //тут чего-то не хватает. см. любую литературу
Deque<T>& Deque<T>::operator=(Deque const &deq) {
    this -> length = deq.length;
    this -> first = deq.first;
    this -> last = deq.last;
}

/// ???                                         //аналогично предыдущему
template<class T>
Deque<T>& Deque<T>::operator=(Deque &&deq) {
    this -> length = deq.length;
    this -> first = deq.first;
    this -> last = deq.last;
}


#endif