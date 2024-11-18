#include <iostream>
#include "Collection.h"

using namespace std;
template <typename Item>
class SortedCollection;

template <typename Item>
class SortedCollection : public Collection<Item> {
    public:

        SortedCollection();
        SortedCollection(int size);
        SortedCollection(SortedCollection<Item>& collection);
        SortedCollection<Item>& operator+(const Item&);
        SortedCollection<Item>& operator<<(const Item&);
        void print();
};

template <typename Item>
SortedCollection<Item>::SortedCollection() {
    capacity = INITIAL_CAPACITY;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}

template <typename Item>
SortedCollection<Item>::SortedCollection(int size) {
    capacity = size;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}

template <typename Item>
SortedCollection<Item>::SortedCollection(SortedCollection<Item>& collection) {
    capacity = collection.capacity;
    curSize = collection.curSize;
    elements = make_unique<Item[]>(capacity);
    for (int i = 0; i < curSize; i++) {
        elements[i] = collection.elements[i];
    }
}

template<typename Item>
SortedCollection<Item>& SortedCollection<Item>::operator+(const Item& item) {
    //cout << "Adding: " << item << "; Size before: " << curSize << "; Capacity: " << capacity << endl;
    if (curSize+1 == capacity) {
      expand();
    }
    int pos = 0;
    while (pos < curSize && elements[pos] < item) {
        pos++;
    }
    
    for (int i = 0; i < curSize-pos+1; i++) {
        elements[curSize-i+1] = elements[curSize-i];
    }
    elements[pos] = item;
    curSize++;
    //print();
    return *this;
}

template <typename Item>
SortedCollection<Item>& SortedCollection<Item>::operator<<(const Item& item) {
    //cout << "Adding: " << item << "; Size before: " << curSize << "; Capacity: " << capacity << endl;
    if (curSize+1 == capacity) {
      expand();
    }
    int pos = 0;
    while (pos < curSize && elements[pos] < item) {
        pos++;
    }
    
    for (int i = 0; i < curSize-pos+1; i++) {
        elements[curSize-i+1] = elements[curSize-i];
    }
    elements[pos] = item;
    curSize++;
    //print();
    return *this;
}

template <typename Item>
void SortedCollection<Item>::print() {
    cout << "Full List: ";
    for (int i = 0; i < curSize; i++) {
        cout << elements[i] << " ";
    }
    cout << endl;
}