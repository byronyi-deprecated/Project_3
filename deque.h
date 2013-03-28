#ifndef DEQUE_H
#define DEQUE_H

#include <list>

template <typename T>
struct List
{
    List* prev;
    List* next;
    T data;
};

/*
template <class T>
struct Iterator
{

    List* t;

    Iterator() : t(0) {}

    Iterator(const iterator& i) {t = i.t;}

    Iterator& operator=(const iterator& i) {

        t = i.t;

    }

    bool operator==(const iterator& i) {

        return t == i.t;

    }

    bool operator!=(const iterator& i) {

        return t != i.t;

    }

    Iterator operator+(const int n) {

        if(n > 0)
            for(int i = 0; i != n; i++)
                t = t->next;

        if(n < 0)
            for(int i = 0; i != (-n); i++)
                t = t->prev;

        return *this;

    }

    Iterator operator-(const int n) {

        *this = *this+(-n);
        return *this;
    }

    Iterator operator++() {

        t = t->next;
        return *this;
    }

    Iterator operator++(int) {

        temp = *this;
        t = t->next;
        return temp;
    }

    Iterator operator--() {

        t = t->prev();

    }

    Iterator operator--(int) {

        temp = *this;
        t = t->prev;
        return temp;
    }

    T operator*() {

        return t->data;
    }
};
*/

template <typename T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
  List<T>* p;
public:
  Iterator(List<T>* x) : p(x) {}
  Iterator(const Iterator& mit) : p(mit.p) {}
  Iterator& operator++() {p = p->next;return *this;}
  Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
  Iterator& operator--() {p = p->prev; return *this;}
  Iterator operator--(int) {Iterator tmp(*this); operator--(); return tmp;}
  bool operator==(const List<T>& rhs) {return p==rhs.p;}
  bool operator!=(const List<T>& rhs) {return p!=rhs.p;}
  T& operator*() {return p->data;}
};

template <typename T>
class Deque
{
public:
    Deque(): head(0), end(0), _size(0){}
    ~Deque();
    bool isEmpty() const {return size;}
    int size() const {return _size;}
    void addFirst(T);
    void addLast(T);
    T removeFirst();
    T removeLast();
    Iterator<T> iterator() {return Iterator<T>(head);}
private:
    List<T>* head;
    List<T>* end;
    unsigned int _size;
};

#endif // DEQUE_H
