#include <iostream>
#include "Person.h"


using namespace std;


int main() {
    Person bt("Bart", 10);
    Person hm("Homer", 42);
    Person mg("Marge", 42);


    //Comparing using >
    if (hm > bt) {
        cout << "Older: " << hm << endl;
        cout << "Younger: " << bt << endl;
    }
    //Comparing using ==
    if(hm == mg){
        cout << "Same Age: " << endl;
        cout << hm << endl;
        cout << mg << endl;
    }

    if (bt < 21) {
        cout << bt << "  too young for Moes" << endl;
    }
    
    if (21 > bt) {
		cout << bt << " less than 21" << endl;
	}


}
