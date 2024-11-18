#pragma once


#include <iostream>
#include <memory>
#include <cmath>

using std::ostream;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

template<class Type>
struct Node {
    Type data;
    //Node<Type> *next;
    shared_ptr <Node<Type> > next;

    void operator=(Node<Type>& node) {
        data = node->data;
    }
};


/*
    LinkedListIterator is used for writing the test cases for the merge sort.  Do not remove.
*/
template<typename Type>
class LinkedListIterator {
public:
    LinkedListIterator(shared_ptr<Node <Type> > ptr) : current(ptr) {}
    LinkedListIterator<Type>& operator++() { current = current->next; return *this; }
    Type operator*() { return current->data; }
    bool operator==(const LinkedListIterator<Type>& rhs) const { return current == rhs.current; }
    bool operator!=(const LinkedListIterator<Type>& rhs) const { return current != rhs.current; }
    shared_ptr<Node <Type> > getNode() { return current; }

private:
    shared_ptr < Node<Type> >  current;
};


template<class Type>
class LinkedList;

template<class Type>
ostream& operator<< (ostream& out, const LinkedList<Type>& list);


template<class Type>
class LinkedList {
public:
    LinkedList() : front(nullptr), back(nullptr), count(0) {}// Default constructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
    //~LinkedList();           //Destructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
    void insert(Type data);  //Adds to the back of the list
    Type peek(int ndx)const;//Looks at an element at the given ndx value
    void remove(int ndx);    //Removes an element at the given ndx position
    friend ostream& operator<< <>(ostream& out, const LinkedList<Type>& list);// Returns an output stream for displaying the LinkedList


    void mergeSort();
    LinkedListIterator<Type> begin() { return LinkedListIterator<Type>(front); }

    void mergeSort(shared_ptr<Node <Type> > &head);
    shared_ptr<Node <Type> >  getMiddle(shared_ptr<Node <Type> > head);
    shared_ptr<Node <Type> > mergeInOrder(shared_ptr<Node <Type> > a, shared_ptr<Node <Type> > b);


protected:
    shared_ptr <Node<Type> > front;
    shared_ptr <Node<Type> > back;
    int count;//Number of nodes in list
};

template<class Type>
void LinkedList<Type>::insert(Type data) {
    auto temp = make_shared<Node<Type>>();
    temp->data = data;
    temp->next = nullptr;
    if (!front) {
        front = temp;
        back = temp;
    }
    else {
        back->next = temp;
        back = temp;
    }
    count++;
}
template<class Type>
Type LinkedList<Type>::peek(int ndx)const {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of range");
    }

    int currNodeNum = 0;
    auto currentNode = front;

    while (currNodeNum < ndx) {
        currNodeNum++;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template<class Type>
void  LinkedList<Type>::remove(int ndx) {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of range");
    }

    //If removing the front
    if (ndx == 0) {
        auto toDelete = front;
        front = toDelete->next;
        //delete toDelete;
        return;
    }//end if
    int currNodeNum = 0;
    auto currentNode = front;

    while (currNodeNum < ndx - 1) {
        currNodeNum++;
        currentNode = currentNode->next;
    }
    auto toDelete = currentNode->next;
    //Deleting from middle
    if (toDelete->next) {
        currentNode->next = toDelete->next;
    }
    //Delete last node
    else {
        currentNode->next = nullptr;
        back = currentNode;
    }
    count--;
    //delete toDelete;
}//end remove

template<class Type>
ostream& operator<< (ostream& out, const LinkedList<Type>& list) {
    auto curr = list.front;

    while (curr) {
        out << curr->data;
        if (curr->next) {
            out << " ";
        }
        curr = curr->next;
    }
    return out;
}





template<class Type>
void  LinkedList<Type>::mergeSort() {
    mergeSort(front);
}

template<class Type>
void  LinkedList<Type>::mergeSort(shared_ptr<Node <Type> > &head) {
    if (head->next == nullptr || head == nullptr) {
        return;
    }
    auto middle = getMiddle(head); // Get center(ish) node
    auto right = middle->next; // Set the starting point for the right branch to be the next node after the middle
    middle->next = nullptr; // Sever the 2 sides of the list
    mergeSort(head);
    mergeSort(right);
    head = mergeInOrder(head, right);
}

template<class Type>
shared_ptr<Node <Type> > LinkedList<Type>::getMiddle(shared_ptr<Node <Type> > head) {
    if ( head-> next == nullptr) {
        return head;
    } 
    int localCount = 1;
    auto temp = head;
    do {
        localCount++;
        temp = temp->next;
    } while (temp->next != nullptr);
    int positionToGoTo = floor(localCount/2);
    if ( localCount % 2 == 0 ) {
        positionToGoTo -= 1;
    }
    for (int i = 0; i < positionToGoTo; i++) {
        head = head->next;
    }
    return head;
}

template<class Type>
shared_ptr<Node <Type> > LinkedList<Type>::mergeInOrder(shared_ptr<Node <Type> > a, shared_ptr<Node <Type> > b) {

    if (!a) {
        return b;
    } else if (!b) {
        return a;
    }
    
    auto finalList = make_shared<Node<Type>>();
    auto temp = finalList;

    while (a && b) {
        if (a->data <= b->data) {
            temp->next = a;
            a = a->next;
        } else {
            temp->next = b;
            b = b->next;
        }
        temp = temp->next;
    }

    temp->next = a ? a : b;

    return finalList->next;
}

