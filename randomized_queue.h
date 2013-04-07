#ifndef RANDOMIZEDQUEUE_H
#define RANDOMIZEDQUEUE_H

#include <deque.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
using namespace std;
#define MAX 10

template <class T>
class RandomizedQueue
{
public:

    struct Iterator : public Deque<T>::Iterator
    {
        typedef Deque<T>::Iterator Itr;
    public:
        Iterator(Deque<T>::List* x) : Deque<T>::Iterator(x) {}

        Iterator& operator++()
        {

        }

    };

    RandomizedQueue(): _size(0) {

        hashtable = vector<Deque<T> > (10, Deque<T>());
    }

    ~RandomizedQueue() { }

    bool isEmpty() const {return _size != 0;}
    int size() const {return _size;}

    void enqueue(T item) {

        srand (time(NULL));
        unsigned int bucket = rand() % MAX;
        hashtable[bucket].addLast(item);

        for(unsigned int i = bucket; i != MAX - 1; ++i)
            if(hashtable[i + 1].size() != 0)
            {
                hashtable[i + 1].head->prev = hashtable[bucket].end;
                hashtable[bucket].end->next = hashtable[i + 1].head;
                break;
            }

        for(unsigned int i = bucket - 1; i != 0; --i)
            if(hashtable[i].size() != 0)
            {
                hashtable[i].end->next = hashtable[bucket].head;
                hashtable[bucket].head->prev = hashtable[i].end;
                break;
            }


/*
        if(hashtable.size() != MAX) {

            //if size < MAX, just append new
            //items into the vector

            if(_size != 0)
                //all these elements would
                //be linked when appending them
                hashtable.back()->next = temp;

            temp->data = item;
            hashtable.push_back(temp);
            temp->next = 0;

        }
        else {

            //generate a random bucket;
            //each bucket is a stack
            //put the new item on the top
            srand (time(NULL));
            bucket = rand() % MAX;

            //pass-by-value to avoid change
            //the "next" pointer of the last
            //element in the previous bucket
            temp->data = hashtable[bucket]->data;
            temp->next = hashtable[bucket]->next;
            hashtable[bucket]->data = item;
            hashtable[bucket]->next = temp;

        }
*/

        ++_size;

    }

    T dequeue() {

        //
        srand (time(NULL));
        unsigned int bucket = rand() % MAX;
        T data = hashtable[bucket]->data;
        return data;

    }

    T sample() {

    }

    Iterator iterator() {return Iterator(_head);}

private:
    vector<Deque<T> > hashtable;
    unsigned int _size;
};

#endif // RANDOMIZEDQUEUE_H
