#include <iostream>
#include "LinkedList.h"

template<class Type>
class FifthElement : public LinkedList<Type>{
    public:
        FifthElement();
        Type getFifthElement();
        void insertNewFifthElement(const Type&v);
        void deleteFifthElement();
        void swapFourthAndFifthElement();
    private:
        shared_ptr<LinkedList<Type>> list;
};

template <class Type>
FifthElement<Type>::FifthElement() {
    list = make_shared<LinkedList<Type>>();
}

template<class Type>
Type FifthElement<Type>::getFifthElement() {
    if (count < 5) {
        throw runtime_error("Out of range.");
        return NULL;
    }

    auto node = front;
    for (int i = 0; i < 4; i++) {
        node = node->next; // first time - second element; second time - third element; third time - fourth element; fourth time - fifth element;
    }
    return node->data;
}

template<class Type>
void FifthElement<Type>::insertNewFifthElement(const Type&v) {
    if (count < 4) {
        throw runtime_error("Out of range.");
        return;
    }
    auto newNode = make_shared<Node<Type>>(v);
    auto node = front;
    for (int i = 0; i < 3; i++) {
        node = node->next; // first time - second element; second time - third element; third time - fourth element;
    }
    auto FifthNode = node->next;
    newNode->next = FifthNode;
    node->next = newNode;
}

template<class Type>
void FifthElement<Type>::deleteFifthElement() {
    if (count < 5) {
        throw runtime_error("Out of range.");
        return;
    }
    auto node = front;
    for (int i = 0; i < 3; i++) {
        node = node->next; // first time - second element; second time - third element; third time - fourth element;
    }
    node->next = node->next->next;
}

template<class Type>
void FifthElement<Type>::swapFourthAndFifthElement() {
    if (count < 5) {
        throw runtime_error("Out of range.");
        return;
    }
    auto node = front;
    for (int i = 0; i < 2; i++) {
        node = node->next; // first time - second element; second time - third element;
    }
    auto third = node; // temp is 3rd element
    node = node->next; // node now 4th element
    auto fourth = node;
    node = node->next;
    auto fifth = node;
    fourth->next = fifth->next;//fourth to sixth element
    third->next = fifth; //third to fifth element
    fifth->next = fourth; //fifth element to fourth element
    
}