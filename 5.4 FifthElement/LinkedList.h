#pragma once

using std::make_shared;
using std::ostream;
using std::shared_ptr;
using std::runtime_error;

template<class Type>
struct Node {
    Type data;
    shared_ptr<Node<Type>> next;

    Node(Type data) {
        this->data = data;
    }
};
template <class Type>
class LinkedList;

template <class Type>
ostream& operator<< (ostream& out, const LinkedList<Type>& list);

template<class Type>
class LinkedList{
    public:
        void pointerPractice(Type, Type);
        LinkedList(): front(nullptr), back(nullptr), count(0) {}// Default constructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
        //~LinkedList();           //Destructor for the LinkedList.  Creates an empty list by setting front and back of the list to nulllptr
        void insert(Type data);  //Adds to the back of the list
        Type peek(int ndx)const ;//Looks at an element at the given ndx value
        void remove(int ndx);    //Removes an element at the given ndx position
        friend ostream& operator<< <>(ostream& out, const LinkedList<Type>& list);// Returns an output stream for displaying the LinkedList
    protected:
        shared_ptr<Node<Type>> front;
        shared_ptr<Node<Type>> back;
        int count;
};

template<class Type>
void LinkedList<Type>::pointerPractice(Type toInsert, Type toRemove)
{
	auto newNode = make_shared< Node<Type>>();
	newNode->data = toInsert;
}


template <class Type>
void LinkedList<Type>::insert(Type givenData) {
    //std::cout << front ? "Front exists" : "Front does not exist";
    if (front && count >= 2) {
        auto newNode = make_shared<Node<Type>>(givenData);
        auto curr = front;
        while (curr->next && curr->next->data < givenData) {
            curr = curr->next;
        }
        //std::cout << curr->data;
        newNode->next = curr->next;
        curr->next = newNode;
        count++;
    } else {
        auto temp = make_shared<Node<Type>>(givenData);
        //temp->data = givenData;
        //temp->next = nullptr;
        if (!front) {
            front = temp;
            back = temp;
        } else {
            back->next = temp;
            back = temp;
        }
        count++;
    }
}

template <class Type>
Type LinkedList<Type>::peek(int ndx) const {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of Range");
    }
    int currNodeNum = 0;
    auto currNode = front;

    while (currNodeNum < ndx) {
        currNodeNum++;
        currNode = currNode->next;
    }

    return currNode->data;
}

template <class Type>
void LinkedList<Type>::remove(int ndx) {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of Range");
    }

    if (ndx == 0) {
        auto toDelete = front; 
        front = toDelete->next;
        return;
    }

    int currNodeNum = 0;
    auto currNode = front;

    while (currNodeNum < ndx - 1) {
        currNodeNum++;
        currNode = currNode->next;
    }

    auto toDelete = currNode->next;

    if (toDelete->next) {
        currNode->next = toDelete->next;
    } else {
        currNode->next = nullptr;
        back = currNode;
    }
    count--;
}

template <class Type>
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