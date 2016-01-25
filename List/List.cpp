#include <stdexcept>
#include <string>
#include "List.h"

template<class T>
Element<T> *List<T>::at(int index) {
    if (this->head == nullptr) {
        throw std::invalid_argument("N/A");
    }

    int idx = 0;
    Element<T> *element = this->head;

    do {
        if (idx == index) {
            break;
        }

        element = element->getNext();
        ++idx;
    } while (element->getNext() != nullptr);

    if (idx == index) {
        return element;
    }

    throw std::invalid_argument("N/A");
}

template<class T>
void List<T>::pushBack(T value) {
    Element<T> *newElement = new Element<T>(value);

    if (this->head == nullptr) {
        this->head = newElement;
        return;
    }

    Element<T> *element = this->head;
    while (element->getNext() != nullptr) {
        element = element->getNext();
    }

    element->setNext(newElement);
}

template<class T>
void List<T>::removeAt(int index) {
    Element<T> *element = this->at(index);

    if (element == this->head) {
        Element<T> *next = element->getNext();
        delete element;
        this->head = next;
        return;
    }

    Element<T> *before = this->at(index - 1);

    Element<T> *after;
    try {
        after = this->at(index + 1);
    } catch (std::invalid_argument) {
        after = nullptr;
    }

    delete element;
    before->setNext(after);
}

template<class T>
T List<T>::operator[](int index) {
    return this->at(index)->getValue();
}

// explicit supported types
template
class List<int>;

template
class List<long>;

template
class List<long long>;

template
class List<double>;

template
class List<float>;

template
class List<std::string>;
