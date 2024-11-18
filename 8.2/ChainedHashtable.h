#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>

using namespace std;

template<class Type>
struct Node {
	Node(Type data): data(data), next(nullptr){}

	Type data;
	shared_ptr <Node<Type>> next;
};

template<class Type>
class ChainedHashtable;

template<class Type>
ostream& operator<<(ostream& out, const ChainedHashtable<Type> &t);

template<class Type>
class ChainedHashtable {
protected:
	int sz;			//Number of elements in table
	int capacity;   //Table size
	unique_ptr<shared_ptr<Node<Type>>[]> htable;  //An Array of LinkedList Node Headers

public:
	ChainedHashtable(int capacity = 21) :
		sz(0), capacity(capacity), htable(new shared_ptr<Node<Type>>[capacity]) {}
	void insert(Type);		//Inserts the element in the table
	bool remove(Type);		//Removes an element from the table
	bool contains(Type);		//Returns true if the value exists
	bool empty() { return sz == 0; }	//Returns true if the list is empty
	int size() { return sz; }			//Returns the number of elements in the table
	int getHash(Type data) { return data % capacity; }  //Hash based upon mod division
	friend ostream& operator<< <>(ostream& out, const ChainedHashtable<Type> &t); //Displays the Hashtable
};

template<class Type>
void ChainedHashtable<Type>::ChainedHashtable::insert(Type data) {
	int h = getHash(data);

	if (htable[h]) {
		auto temp = make_shared<Node<Type>>(data);
		temp->next = htable[h];
		htable[h] = temp;
	}
	else {
		htable[h] = make_shared<Node<Type>>(data);
	}
	sz++;
}

template<class Type>
bool ChainedHashtable<Type>::remove(Type data) {
	if (empty()) {
		throw runtime_error("Table is empty");
	}
	int t = getHash(data);

	//If the node is the first item in the list
	if (htable[t] == nullptr) { 
		return false;
	}
	if (htable[t]->data == data) {
		htable[t] = htable[t]->next;
		sz--;
		return true;
	}

	auto curr = htable[t]->next;
	auto prev = htable[t];
	while (curr) {
		if (curr->data == data) {
			prev->next = curr->next;
			sz--;
			return true;
		}
		curr = curr->next;
		prev = prev-> next;
	}
	
	return false;
}

template<class Type>
bool ChainedHashtable<Type>::contains(Type data) {
	int t = getHash(data);

	auto curr = htable[t];
	while (curr) {
		if (curr->data == data) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template<class Type>
ostream& operator<<(ostream& out, const ChainedHashtable<Type> &t) {
	for (int i = 0; i < t.capacity; i++) {
		out << std::setw(8) << i << ": ";

		auto curr = t.htable[i];
		while (curr) {
			out << curr->data << " ";
			if (curr->next) out << "-> ";
			curr = curr->next;
		}
		out << endl;
	}
	return out;
}
