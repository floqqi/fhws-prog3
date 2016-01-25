#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H


template<class T>
class Element {
private:
    T value;
    Element *next;
public:
    Element(T value);

    void setNext(Element *next);

    Element *getNext();

    T getValue();
};


#endif //LIST_ELEMENT_H
