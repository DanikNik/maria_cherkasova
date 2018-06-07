//
// Created by daniknik on 20.05.18.
//

#ifndef MARIA_CHERKASOVA_ALGORITHM_H
#define MARIA_CHERKASOVA_ALGORITHM_H
template<class T, class Pred>
T FindIf(T beg, T end, Pred pred){
    while(beg!=end){
        if(pred(*beg)) return beg;
        ++beg;
    }
    return ++end;
}

template<class T>
T MinElement(T beg, T end){
    T min = beg;
    for (auto i = beg; i < end; i++){
        if(*i<*min) min = i;
    }
    return min;
}

template <class T>
T MaxElement(T beg, T end){
    T max = beg;
    for (auto i = beg; i < end; i++){
        if(*i>*max) max = i;
    }
    return max;
}

template <class T, class Oper>
void ForEach(T beg, T end, Oper op){
    while(beg <= end) {
        *beg = op(*beg);
        ++beg;
    }
};

template <class T>
void Sort(T beg, T end){
    for (T i = end; i > beg; i--){
        for (T j = beg; j < i; j++){
            if (*j > *(j+1)){
                auto tmp = *j;
                *j = *(j+1);
                *(j+1) = tmp;
            }
        }
    }
}

template <class T, class Pred>
void CopyIf(T sourceBeg, T sourceEnd, T destBeg, Pred pred){
    while(sourceBeg != sourceEnd){
        if (pred(*sourceBeg)){
            *destBeg = *sourceBeg;
            destBeg++;
        }
        sourceBeg++;
    }
};


#endif //MARIA_CHERKASOVA_ALGORITHM_H