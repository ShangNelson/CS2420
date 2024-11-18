#include "ChainedHashtable.h"
#include <iostream>

using namespace std;

int main() {
    ChainedHashtable<int>ht(127);
    for (int i = 0; i < 100; i++) {
        ht.insert(rand() % 10);
    }
    cout << ht << endl;
}
