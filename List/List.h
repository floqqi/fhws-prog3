#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "Element.h"

template<class T>
class List {
private:
    Element<T> *head = nullptr;

protected:
    Element<T> *at(int index);

public:
    void pushBack(T value);

    void removeAt(int index);

    T operator[](int index);
};


#endif //LIST_LIST_H
