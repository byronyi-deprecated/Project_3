#ifndef RANDOMIZEDQUEUE_H
#define RANDOMIZEDQUEUE_H

#include <deque.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
using namespace std;
#define MAX 1

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

                if(p->next == 0)
                    throw -1;

                p = p->next;
                return *this;

            }
            catch(int) {

                cerr << "Iterator cannot move beyond the end" << endl;

            }

        }

        Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}

        Iterator& operator--() {

            try {

                if(p->prev == 0)
                    throw -1;

                p = p->prev;
                return *this;
            }
                catch(int) {

                    cerr << "Iterator cannot move beyond the head" << endl;

                }

            }

        Iterator operator--(int) {Iterator tmp(*this); operator--(); return tmp;}

        bool operator==(const List& rhs) {return p==rhs.p;}
        bool operator!=(const List& rhs) {return p!=rhs.p;}

        T& operator*() {
            try {

                if(p->next == 0)
                    throw -1;

                return p->data;
            }
            catch(int) {

                cerr << "Cannot dereference a beyond-the-end iterator" << endl;

            }
        }
    };

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

            cout << "Build a new queue" << endl;
            temp->next = temp;
            temp->prev = temp;
            head = temp;

            List* newBucket = new List;
            newBucket = head;
            buckets.push_back(newBucket);
        }

        else if(_size < MAX) {

            cout << "Buckets aren't filled" << endl;
            int num = rand() % buckets.size();

            temp->next = buckets[num];
            temp->next->prev = temp;
            temp->prev = buckets[num]->prev;
            temp->prev->next = temp;

            List* newBucket = temp;
            buckets.insert(buckets.begin() + num, 1, newBucket);
        }
        else {
            cout << "Buckets filled" << endl;
            int num = rand() % MAX;

            temp->next = buckets[num];
            temp->next->prev = temp;
            temp->prev = buckets[num]->prev;
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
                cout << "dequeue from one element queue" << endl;
                data = head->data;
                buckets.clear();
                delete head;
            }
            else {
                cout << "Dequeue" << endl;
                unsigned int num = rand() % buckets.size();
                List* temp = buckets[num].begin;
                data = temp->data;
                temp->prev = temp->next->prev;
                temp->next = temp->prev->next;
                if(!num) {
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
                delete temp;
            }
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
            T data = buckets[num].begin->data;
            return data;

        }
        catch(int) {
            cerr << "Cannot sample from an empty queue" << endl;
        }
    }

    Iterator iterator() {

        unsigned int num = rand() % buckets.size();
        return Iterator(buckets[0].begin);

    }
private:
    unsigned int _size;
    List* head;
    vector<List*> buckets;
};





/*
template <class T>
class RandomizedQueue
{
public:
    struct List
    {
        List* next;
        T data;
    };

    struct Iterator : public std::iterator<std::forward_iterator_tag, T>
    {
        List* p;
    public:
        Iterator(List* x) : p(x) {}
        Iterator(const Iterator& mit) : p(mit.p) {}

        Iterator& operator++() {

            try {

                if(p == 0)
                    throw -1;

                p = p->next;
                return *this;

            }
            catch(int) {

                cerr << "Iterator cannot move beyond the end" << endl;

            }

        }

        Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}

        T& operator*() {return p->data;}
    };

    RandomizedQueue(): _size(0) {

        srand(time(NULL));

    }

    ~RandomizedQueue() {

        List* head = heads[0];
        while(_size)
        {
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

        if(heads.size() != MAX) {

            if(heads.empty()) {

                heads.push_back(temp);

            }
            else if(rand() % 2) {
                //insert the new item in the back
                temp->next = heads[0];
                heads.push_back(temp);
                ends.push_back(temp);
                heads[heads.size() - 2]->next = heads.back();

            }
            else {
                //insert the new item in the front
                heads.insert(heads.begin(), 1, temp);
                ends.insert(ends.begin(), 1, temp);
                heads.back()->next = heads[0];

            }

            delete temp;

        }
        else {
            unsigned int bucket = rand() % MAX;
            temp->next = heads[bucket];
            heads[bucket] = temp;
            if(bucket != 0)
                ends[bucket - 1]->next = heads[bucket];
            else
                ends.back()->next = heads[0];
        }

        ++_size;

    }

    T dequeue() {

        try {

            if(heads.empty())
                throw -1;

            unsigned int bucket = rand() % heads.size();

            T data = heads[bucket]->data;

            if(heads.size() != MAX) {

                if(bucket != 0) {
                    ends[bucket - 1]->next = heads[bucket + 1];
                }
                delete heads[bucket];
                heads.erase(heads.begin() + bucket);
                ends.erase(ends.begin() + bucket);
            }
            else {
                List* temp = heads[bucket];
                heads[bucket] = heads[bucket]->next;
                ends.back()->next = heads[0];
                delete temp;
            }

            --_size;

            return data;

        }
        catch(int) {
            cerr << "Cannot dequeue from an empty container" << endl;
        }

    }

    T sample() {
        try {

            if(heads.empty())
                throw -1;

            unsigned int bucket = rand() % heads.size();
            T data = heads[bucket]->data;
            return data;

        }
        catch(int) {
            cerr << "Cannot sample from an empty container" << endl;
        }
    }

    Iterator iterator() {

        unsigned int bucket = rand() % heads.size();
        return Iterator(heads[bucket]);

    }

private:
    vector<List* > heads;
    vector<List* > ends;
    unsigned int _size;
};
*/
#endif // RANDOMIZEDQUEUE_H
