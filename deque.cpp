#include "deque.h"

template <typename T>
Deque<T>::~Deque()
{

}

template <typename T>
void Deque<T>::addFirst(T item)
{
    List<T>* temp;
    head->prev = temp;
    temp->next = head;
    temp->prev = 0;
    temp->data = item;
    head = temp;
    ++size;
}

template <typename T>
void Deque<T>::addLast(T item)
{
    List<T>* temp;
    end->next = temp;
    temp->prev = end;
    temp->next = 0;
    temp->data = item;
    end = temp;
    ++size;
}

template <typename T>
T Deque<T>::removeFirst()
{
    List<T>* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    --size;
    return data;
}

template <typename T>
T Deque<T>::removeLast()
{
    List<T>* temp = end;
    T data = temp->data;
    end = end->prev;
    delete temp;
    --size;
    return data;
}
