#ifndef RANDOMIZEDQUEUE_H
#define RANDOMIZEDQUEUE_H

#include <iterator>

template <class T>
class RandomizedQueue
{
public:

    struct List
    {
        List* prev;
        List* next;
        T data;
    };

    struct Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        List* p;
    public:
        Iterator(List* x) : p(x) {}
        Iterator(const Iterator& mit) : p(mit.p) {}
        Iterator& operator++() {p = p->next;return *this;}
        Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
        Iterator& operator--() {p = p->prev; return *this;}
        Iterator operator--(int) {Iterator tmp(*this); operator--(); return tmp;}
        bool operator==(const List& rhs) {return p==rhs.p;}
        bool operator!=(const List& rhs) {return p!=rhs.p;}
        T& operator*() {return p->data;}
    };

    RandomizedQueue(): head(0), end(0), _size(0){}

    ~RandomizedQueue() {

    }

    bool isEmpty() const {return _size != 0;}
    int size() const {return _size;}

    void enqueue(T item) {

    }

    T dequeue() {

    }

    T sample() {

    }

    Iterator iterator() {

    }

private:
    List* head;
    List* end;
    unsigned int _size;
};

#endif // RANDOMIZEDQUEUE_H
