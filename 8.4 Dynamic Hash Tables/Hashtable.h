#pragma once
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

template<class Type>
struct Bucket {
    Type data;
    bool empty = true;
};


template<class Type>
class Hashtable;

template<class Type>
ostream& operator<< (ostream &, Hashtable<Type>&);


template<class Type>
class Hashtable
{
public:
    Hashtable();
    Hashtable(int);
    Hashtable(int, double);
    Hashtable(const Hashtable<Type>& other);
    Hashtable& operator=(const Hashtable<Type>& other);

    int getSize() const;
    int getCapacity() const;
    double getLoadFactorThreshold() const;
    bool empty() const;
    void insert(const Type);
    void remove(int);
    void rehash(); // TODO Check functionality
    static bool isInt(double num) { return (floor(num) == num); }
    static bool isPrime(int num) {
        if (num == 0 || num == 1) {
            return false;
        }
        double i = 2;
        double temp;
        do {
            temp = num /(double) i;
            //cout << temp << endl;
            if (isInt(temp) && temp != 1) {
                return false;
            }
            i++;
        } while (i < num);
        //cout << num << " is prime." << endl;
        return true;
    }
    static int nextPrime(int num) {
            int tempNum = num+1;
            while (!isPrime(tempNum)) {
                tempNum++;
            }
            return tempNum;
    }
    bool contains(int) const;
    int indexOf(int) const;
    void clear();
    friend ostream& operator<< <>(ostream &, Hashtable<Type>&);

private:
    int hash(Type v, int offset) const;
    int capacity;
    int size;
    double loadFactorThreashold;
    unique_ptr<Bucket<Type>[]> htable;
};

template<class Type>
void Hashtable<Type>::rehash() {
    //Double capacity then find next prime
    //cout << "Old capacity was: " << capacity << endl;
    int oldCap = capacity;
    capacity = nextPrime(capacity*2);
    //cout << "New capacity is: " << capacity << endl;
    //Take each item and assign new value to be rehashed
    auto tempTable = make_unique<Bucket<Type>[]>(capacity);
    //cout << size << endl;
    for (int i = 0; i < oldCap; i++) {
        if (!htable[i].empty) {
            const Bucket<Type>& value = htable[i];
            int j = 0;
            while (!tempTable[hash(value.data, j)].empty) {
                j++;
            }
            tempTable[hash(value.data, j)] = {value.data, false};
        }
        //cout << "Added to temp table!" << endl;
    }
    //IDEA: temp array? Unique Pointers.
    htable = move(tempTable);
    //cout << *this;
}

template<class Type>
bool Hashtable<Type>::empty() const
{
    if (size == 0) {
        return true;
    }
    return false;
}


/*
    Complete the insert method to insert the value into the hashtable.  
    Use linear probing to avoid collisions.  If the hashtable is full, return a
    runtime error
*/
template<class Type>
void Hashtable<Type>::insert(Type value)
{
    if (size+1 >= capacity*loadFactorThreashold) {
        rehash();
    }

    int i = 0;
    while (!htable[hash(value, i)].empty) {
        i++;
    }
    htable[hash(value, i)] = {value, false};
    size++;
}

/*
    Complete the remove the value from the hashtable
*/
template<class Type>
void Hashtable<Type>::remove(int value)
{

    int i = 0;
    while (htable[hash(value, i)].data != value && i < capacity) {
        i++;
    }
    if (i == capacity) {
        return;
    }
    htable[hash(value, i)] = {0, true};
    size--;

}


/*
    Complete the hash method to create a modulus division hash algorithm
*/
template<class Type>
int Hashtable<Type>::hash(Type v, int offset) const {
    return fmod(v+pow(offset, 2), capacity);
}

template<class Type>
int Hashtable<Type>::getSize() const
{
    return size;
}

template<class Type>
int Hashtable<Type>::getCapacity() const
{
    return capacity;
}

template<class Type>
double Hashtable<Type>::getLoadFactorThreshold() const {
    return loadFactorThreashold;
}


/*
    Complete the contains method to return true of the Hashtable contains the value
*/
template<class Type>
bool Hashtable<Type>::contains(int value) const {

    int i = 0;
    while (htable[hash(value, i)].data != value && i < capacity) {
        i++;
    }
    if (htable[hash(value, i)].data == value ) {
        return true;
    }
    return false;
}

template <class Type>
int Hashtable<Type>::indexOf(int value) const {
    if (!contains(value)) {
        return -1;
    }

    int i = 0;
    while (htable[hash(value, i)].data != value && i < capacity) {
        i++;
    }
    if (htable[hash(value, i)].data == value ) {
        return hash(value, i);
    }
    return false;
}



template<class Type>
void Hashtable<Type>::clear()
{
    size = 0;
    htable = make_unique<Bucket<Type>[]>(capacity);
}



template<class Type>
ostream& operator<< (ostream & out, Hashtable<Type>& h) {
    out << "\nCapacity: " << h.capacity << "\n";
    for (int i = 0; i < h.capacity; i++) {

        //if (h.htable[i].empty == false) {
            out << i << ": " << h.htable[i].data << endl;
        //}

    }
    return out;
}

template<class Type>
Hashtable<Type>::Hashtable()
{
    size = 0;
    capacity = 17;
    loadFactorThreashold = 0.65;
    htable = make_unique<Bucket<Type>[]>(capacity);
}


template<class Type>
Hashtable<Type>::Hashtable(int capacity) : capacity(capacity)
{
    size = 0;
    loadFactorThreashold = 0.65;
    htable = make_unique<Bucket<Type>[]>(capacity);
}


template<class Type>
Hashtable<Type>::Hashtable(int capacity, double loadFactorThreashold) : capacity(capacity), loadFactorThreashold(loadFactorThreashold)
{
    size = 0;
    htable = make_unique<Bucket<Type>[]>(capacity);
}



/*
    Complete the operator= to create a deep copy of the hashtable
*/
template<class Type>
Hashtable<Type>::Hashtable(const Hashtable<Type>& other)
{
    loadFactorThreashold = other.loadFactorThreashold;
    capacity = other.capacity;
    size = other.size;
    htable = make_unique<Bucket<Type>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }
}

/*
    Complete the operator= to create a deep copy of the hashtable
*/
template<class Type>
Hashtable<Type>& Hashtable<Type>::operator=(const Hashtable<Type>& other)
{
    loadFactorThreashold = other.loadFactorThreashold;
    capacity = other.capacity;
    size = other.size;
    htable = make_unique<Bucket<Type>[]>(capacity);
    for (int i = 0; i < capacity; i++) {
        htable[i] = other.htable[i];
    }

    return *this;
}
