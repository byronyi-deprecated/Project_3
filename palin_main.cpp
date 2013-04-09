#include<deque.h>
#include<iostream>
using namespace std;

int main(int argc, char** argv)
{
    Deque<char> a;
    char base_pair;
    while(cin >> base_pair)
        a.addLast(base_pair);
    while(!a.isEmpty()) {
        if(a.size() == 1) {
            cout << "false" << endl;
            return 0;
        }
        char first = a.removeFirst();
        char last = a.removeLast();
        switch(first) {
        case 'A':
            if(last != 'T')
            {
                cout << "false" << endl;
                return 0;
            }
            continue;
        case 'T':
            if(last != 'A')
            {
                cout << "false" << endl;
                return 0;
            }
            continue;
        case 'C':
            if(last != 'G')
            {
                cout << "false" << endl;
                return 0;
            }
            continue;
        case 'G':
            if(last != 'C')
            {
                cout << "false" << endl;
                return 0;
            }
            continue;
        default:
            cout << "false" << endl;
            return 0;
        }
    }
    cout << "true" << endl;
    return 0;
}
