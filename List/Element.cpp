#include <string>
#include "Element.h"

template<class T>
Element<T>::Element(T value) : next(nullptr) {
    this->value = value;
}

template<class T>
void Element<T>::setNext(Element *next) {
    this->next = next;
}

template<class T>
Element<T> *Element<T>::getNext() {
    return this->next;
}

template<class T>
T Element<T>::getValue() {
    return this->value;
}

// explicit supported types
template
class Element<int>;

template
class Element<long>;

template
class Element<long long>;

template
class Element<double>;

template
class Element<float>;

template
class Element<std::string>;
