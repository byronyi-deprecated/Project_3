#ifndef DEQUE_H
#define DEQUE_H

#include <iterator>
#include <iostream>
using namespace std;

template <class T>
class Deque
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

        Iterator& operator++() {

            try {
                if(p == 0) throw 0;
                if(p->next == 0) throw -1;

                p = p->next;
                return *this;

            }
            catch(int err) {

                if(err == 0)
                    cerr << "The iterator incrementing is un-defined" << endl;
                if(err == -1)
                    cerr << "Iterator cannot move beyond the end" << endl;

            }

        }

        Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}

        Iterator& operator--() {

            try {

                if(p == 0) throw 0;
                if(p->prev == 0) throw -1;

                p = p->prev;
                return *this;
            }
            catch(int err) {
                if(err == 0)
                    cerr << "The iterator decrementing is un-defined" << endl;
                if(err == -1)
                    cerr << "Iterator cannot move beyond the head" << endl;

            }

        }

        Iterator operator--(int) {Iterator tmp(*this); operator--(); return tmp;}

        bool operator==(const List& rhs) {return p==rhs.p;}
        bool operator!=(const List& rhs) {return p!=rhs.p;}

        T& operator*() {
            try {

                if(p == 0) throw 0;
                if(p->next == 0) throw -1;

                return p->data;
            }
            catch(int err) {

                if(err == 0)
                    cerr << "The iterator dereferencing is un-defined" << endl;
                if(err == -1)
                    cerr << "Cannot dereference a beyond-the-end iterator" << endl;

            }
        }
    };

    Deque(): _size(0) {

        _end = new List;
        _end->prev = 0;
        _end->next = 0;
        _head = _end;

    }

    ~Deque(){

        while(_size)
            removeFirst();
        delete _end;

    }

    bool isEmpty() const {return _size == 0;}
    int size() const {return _size;}

    void addFirst(const T& item) {

        List* temp = new List;
        temp->data = item;
        temp->prev = 0;
        temp->next = _head;
        _head->prev = temp;
        _head = temp;
        ++_size;

    }

    void addLast(const T& item) {

        List* temp = new List;
        temp->data = item;
        temp->prev = _end->prev;
        temp->next = _end;
        if(_size == 0)
            _head->next = temp;
        else _end->prev->next = temp;
        _end->prev = temp;
        ++_size;

    }


    T removeFirst() {
        try {

            if(_size == 0)
                throw -1;

            List* temp = _head;
            T data = temp->data;
            _head = _head->next;
            delete temp;
            --_size;
            return data;

        }
        catch(int) {

            cerr << "Cannot delete element from empty deque" << endl;

        }

    }

    T removeLast() {
        try {

            if(_size == 0)
                throw -1;

            List* temp = _end->prev;
            T data = temp->data;
            _end->prev = temp->prev;
            delete temp;
            --_size;
            return data;

        }
        catch(int) {

            cerr << "Cannot delete element from empty deque" << endl;

        }

    }

    Iterator iterator() {return Iterator(_head);}

    Iterator end() const {return _end;}
private:
    List* _head;
    List* _end;
    unsigned int _size;
};

#endif // DEQUE_H
