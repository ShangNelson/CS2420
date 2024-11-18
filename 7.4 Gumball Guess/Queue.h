#include <iostream>
#include <memory>

using namespace std;

template <class T>
struct Node {
  T data;
  shared_ptr<Node<T>> next;

  Node() : data(), next(nullptr){};

  Node(T data) : data(data), next(nullptr){};
};

template <class T>
class Queue;

template <class T>
ostream &operator<<(ostream &out, const Queue<T> &queue);

template <class T>
class Queue {
public:
  Queue() : front(nullptr), back(nullptr), size(0){};
  Queue(const Queue<T> &);
  Queue<T> operator=(const Queue<T> &);
  void enqueue(T);
  T peek() const;
  void dequeue();
  bool isEmpty() const;
  void clear();
  int getSize() const;
  friend ostream &operator<< <>(ostream &out, const Queue<T> &queue);

private:
  shared_ptr<Node<T>> front;
  shared_ptr<Node<T>> back;
  int size;
};

template <class T>
Queue<T>::Queue(const Queue<T> &instance) {
    auto temp = instance.front;
    size = 0;
    while (temp != nullptr) {
        enqueue(temp->data);
        size++;
        temp = temp->next;
    }
}

template <class T>
T Queue<T>::peek() const { 
    if (front == nullptr || size == 0) {
        throw runtime_error("Empty Queue");
    }
    return front->data; 
}

template <class T>
bool Queue<T>::isEmpty() const { 
    return (size == 0 || front == nullptr);
}

template <class T>
void Queue<T>::clear() {
    front = nullptr;
    back = nullptr;
    size = 0;    
}

template <class T>
void Queue<T>::enqueue(T data) {
    auto newNode = make_shared<Node<T>>(data);
    if (front) {
        back->next = newNode;
        back = newNode;
    } else {
        front = newNode;
        back = newNode;
    } 
    size++; 
}

template <class T>
void Queue<T>::dequeue() {
    if (!front) {
        throw runtime_error("Empty Queue.");
    }
    front = front->next;
    size--;
}

template <class T>
ostream &operator<<(ostream &out, const Queue<T> &queue) {
  if (queue.isEmpty()) {
    return out;
  }
  auto temp = queue.front;
  while (temp != nullptr) {
    out << temp->data;
    if (temp->next != nullptr) {
      out << "; ";
    }
    temp = temp->next;
  }
  return out;
}

template <class T>
Queue<T> Queue<T>::operator= (const Queue<T>& queue) {
    clear();
    Queue<T> newQueue(queue);
    return newQueue;
    /*front = make_shared<Node<T>>(newQueue.peek());
    back = front;
    while (!newQueue.isEmpty()) {
        enqueue(newQueue.peek());
        newQueue.dequeue();
    }
    return *this;*/
}