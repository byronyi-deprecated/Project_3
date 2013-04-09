#include <iostream>
#include "randomized_queue.h"

using namespace std;

int main(int argc, char ** argv){

    if(argc != 2)
        cerr << "Usage: give a non-negative integer for " << argv[0] << endl;

    RandomizedQueue<char> a;
    char input;
    while(cin >> input)
        a.enqueue(input);
    RandomizedQueue<char>::Iterator itr = a.iterator();
    for(int i = 0; i != static_cast<int>(*argv[1] - '0'); ++i)
        cout << *itr++;
    return 0;
}
