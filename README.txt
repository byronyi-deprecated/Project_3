Project Description

This programming assignment is adopted from an assignment of a similar course offered at Princeton and is gratefully acknowledged.
Write a generic data type for a deque (call the header file deque.h) and a randomized queue (call it randomized_queue.h). We also provided two main programs for testing your implementation: main_deque , main_rand.cpp . The goal of this assignment is to implement elementary data structures using arrays and linked lists, and to introduce you to generics and iterators.

Dequeue. A double-ended queue or deque (pronounced "deck") is a generalization of a stack and a queue that supports inserting and removing items from either the front or the back of the data structure. Create a data type Deque that supports the following API. (Note: the following API is expressed in Java but you can easily implement it using C++ class).

public class Deque<Item> implements Iterable<Item> {
   public Deque()                    // construct an empty deque
   public boolean isEmpty()          // is the deque empty?
   public int size()                 // return the number of items on the deque
   public void addFirst(Item item)   // insert the item at the front of the queue
   public void addLast(Item item)    // insert the item at the end of the queue
   public Item removeFirst()         // delete and return the first item in queue
   public Item removeLast()          // delete and return the last item in queue
   public Iterator<Item> iterator()  // return an iterator that examines the
                                     // items in order from front to back
}
Throw a RuntimeException if the client attempts to remove an item from an empty deque. Again, if you prefer, you may alternatively use assert or if-then-else. The point is that your program should not crash if this exception occurs.

Your deque implementation should support each deque operation in constant worst-case time and use space proportional to the number of items currently in the deque. Additionally, your iterator implementation should support each iteration operation (including construction) in constant worst-case time, and use a constant amount of extra space per iterator.

Randomized queue. A randomized queue is similar to a stack or queue, except that the item removed is chosen uniformly at random from items in the data structure. Create a generic data type RandomizedQueue that supports the following API. (Again note the following API is expressed in Java but you can easily implement it using C++ class).

public class RandomizedQueue<Item> implements Iterable<Item> {
   public RandomizedQueue()          // construct an empty randomized queue
   public boolean isEmpty()          // is the queue empty?
   public int size()                 // return the number of items on the queue
   public void enqueue(Item item)    // add the item
   public Item dequeue()             // delete and return a random item
   public Item sample()              // return (but do not delete) a random item
   public Iterator<Item> iterator()  // return an iterator that returns the items in random order
}
Throw a RuntimeException if the client attempts to dequeue or sample from an empty randomized queue. If you prefer, you may alternatively use assert or if-then-else. The point is that your program should not crash if this exception occurs.

Your randomized queue implementation should support each randomized queue operation (besides creating an iterator) in constant amortized time and use space proportional to number of items currently in the queue. That is, any sequence of M randomized queue operations (starting from an empty queue) should take at most cM steps for some constant c. Additionally, your iterator implementation should support each iteration operation (besides construction) in constant worst-case time, and use a linear amount of extra space per iterator.

Clients. Write a client program to solve each of the following problems. Use one variable of either type Deque or RandomizedQueue in each client. Use generics to avoid casting in your clients.

Write a program Subset that takes a command-line argument k, reads in a sequence of strings from standard input, and prints out a subset of exactly k of them, uniformly at random. Each element from the set can appear in a subset at most once.
% echo A B C D E F G H I | Subset 3
C
G
A

% echo A B C D E F G H I | Subset 3
E
F
G
Write a program Palindrome that reads in a sequence of characters from standard input using StdIn.readChar() and determines whether that sequence represents a Watson-Crick complemented palindrome: the {A, C, T, G}-sequence equals its reverse when you replace each base with its complement: A-T, C-G). Palindromes in DNA have many important biological roles. For example, tumor cells frequently amplify their genes by forming DNA palindromes.
% echo AAAACGTTTT | Palindrome       % echo AAAACTTTT | Palindrome
true                                 false

% echo AGCTAGCT | Palindrome         % echo agctagct | Palindrome
true                                 false

% echo | Palindrome                  % echo A | Palindrome
true                                 false
Deliverables. Submit the data types RandomizedQueue and Deque. Each data type should include its own main() that thoroughly tests the associated operations. You may not call any library functions other than those in the standard library. Also submit the client programs Subset and Palindrome. Finally, submit a readme.txt file and answer the questions.

What to submit

All the source code (.cpp and .h), but not the object code or executable
Makefile and readme.txt
Zip (1) and (2) inside a file called queues.zip, and upload the file to CASS before 23:59:00 on the due date. Warning: If your submitted project fails to compile, your assignment will be treated as late (where late policy applies).
