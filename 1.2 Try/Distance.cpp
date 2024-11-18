#include <iostream>
#include "Distance.h"

using namespace std;

int main() {
    Distance d1;
    cout << "Distance 1: " << d1 << endl;
    Distance d2(1, 15);
    cout << "Distance 2: " << d2 << endl;
    Distance d3(5);
    cout << "Distance 3: " << d3 << endl;
    Distance d4 = d2 + d3;
  	cout << "Distance 4: " << d4 << endl;
    Distance d5 = d2 - d3;
    cout << "Distance 5: " << d5 << endl;
    return 0;
}