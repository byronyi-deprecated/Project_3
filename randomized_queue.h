#ifndef RANDOMIZEDQUEUE_H
#define RANDOMIZEDQUEUE_H

#include <deque.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
using namespace std;
#define MAX 20

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
                return p->data;
            }
            catch(int) {

                cerr << "The iterator dereferencing is un-defined" << endl;

            }
        }
    };

    void Print(List* item)
    {
        cout << item->data << endl;
    }

    RandomizedQueue() : _size(0) {
        srand(time(NULL));
    }
    ~RandomizedQueue() {

        while(_size) {
            List* temp = head;
            head = head->next;
            delete temp;
            --_size;
        }
    }
    bool isEmpty() const {return _size == 0;}
    int size() const {return _size;}

    void enqueue(T item) {

        List* temp = new List;
        temp->data = item;

        if(!_size) {

            temp->next = temp;
            temp->prev = temp;
            head = temp;

            buckets.push_back(temp);
        }

        else if(buckets.size() < MAX) {

            int num = rand() % buckets.size();
            num = 0;
            temp->next = buckets[num];
            temp->prev = buckets[num]->prev;
            temp->prev->next = temp;
            buckets[num]->prev = temp;

            buckets.insert(buckets.begin() + num, 1, temp);

        }
        else {
            int num = rand() % MAX;
            temp->next = buckets[num];
            temp->prev = buckets[num]->prev;
            buckets[num]->prev = temp;
            temp->prev->next = temp;
            buckets[num] = temp;
        }
        ++_size;
    }

    T dequeue() {

        try {

            if(isEmpty())
                throw -1;

            T data;
            if(_size == 1) {
                data = head->data;
                buckets.clear();
                delete head;
                cout << "dequeue from one element queue" << endl;
            }
            else {
                cout << "Dequeue" << endl;
                unsigned int num = rand() % buckets.size();
                List* temp = buckets[num];
                data = temp->data;
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                if(num == MAX - 1) {
                    if(buckets[num]->next = buckets[0])
                        buckets.pop_back();
                    else
                        buckets[num] = buckets[num]->next;
                }
                else {
                    if(buckets[num]->next = buckets[num + 1])
                        buckets.erase(buckets.begin() + num);
                    else
                        buckets[num] = buckets[num]->next;
                }

                /*                if(!num) {
                    buckets.back().end->next = buckets[1].begin;
                    buckets[1].begin->prev = buckets.back().end;
                }
                else if(num == MAX - 1){
                    buckets[num - 1].end->next = buckets[0].begin;
                    buckets[0].begin->prev = buckets[num - 1].end;
                }
                else {
                    buckets[num - 1].end->next = buckets[num + 1].begin;
                    buckets[num + 1].begin->prev = buckets[num - 1].end;
                }
                if(buckets[num].begin == buckets[num].end)
                    buckets.erase(buckets.begin() + num);
*/

                delete temp;
            }
            --_size;
            return data;
        }

        catch(int) {
            cerr << "Cannot dequeue from an empty queue" << endl;
        }
    }

    T sample() {
        try {

            if(isEmpty())
                throw -1;

            unsigned int num = rand() % buckets.size();
            T data = buckets[num]->data;
            return data;

        }
        catch(int) {
            cerr << "Cannot sample from an empty queue" << endl;
        }
    }

    Iterator iterator() {

        if(isEmpty())
            return 0;
        unsigned int num = rand() % buckets.size();
        return Iterator(buckets[num]);
    }
private:
    unsigned int _size;
    List* head;
    vector<List*> buckets;
};
#endif // RANDOMIZEDQUEUE_H
