#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node {
  T data;
  shared_ptr<Node<T>> left;
  shared_ptr<Node<T>> right;
};

template <typename T>
class BTree {
public:

  void insert(const T& item);
  void remove(const T& item);
  shared_ptr<Node<T>> find(const T& item);
  bool contains(const T& item);
  void preOrder();
  void inOrder();
  void postOrder();
  int nodeCount();
  int leavesCount();


private:
  void preOrder(shared_ptr<Node<T>> ptr);
  void inOrder(shared_ptr<Node<T>> ptr);
  void postOrder(shared_ptr<Node<T>> ptr);
  void insert(const T& item,  shared_ptr<Node<T>> ptr);
  shared_ptr<Node<T>> find(shared_ptr<Node<T>> ptr, const T& item);
  void remove(const T& item,  shared_ptr<Node<T>> ptr);
  int nodeCount(shared_ptr<Node<T>> ptr);
  int leavesCount(shared_ptr<Node<T>> ptr);
  
  static shared_ptr<Node<T>> getOneBeforeFurthestRight(shared_ptr<Node<T>> ptr) {
    if (ptr && ptr->right && ptr->right->right) {
      return getOneBeforeFurthestRight(ptr->right);
    } else {
      return ptr;
    }
  }
  
  shared_ptr<Node<T>> root;
};

template <typename T>
void BTree<T>::insert(const T& item) {
  insert(item, root);
}

template <typename T>
void BTree<T>::insert(const T& item, shared_ptr<Node<T>> ptr) {
  if (ptr) {
    if ( item < ptr->data ) {
      if( ptr->left == nullptr ) {
        auto newNode = make_shared<Node<T>>();
        newNode->data = item;
        ptr->left = move(newNode);
      } else {
        insert(item, ptr->left);
      }
    } else {
      if (ptr->right == nullptr) {
        auto newNode = make_shared<Node<T>>();
        newNode->data = item;
        ptr->right = move(newNode);
      } else {
        insert(item, ptr->right);
      }
    }
  } else {
    auto newNode = make_shared<Node<T>>();
    newNode->data = item;
    root = move(newNode);  
  }
}

template <typename T>
void BTree<T>::remove(const T& item) {
  remove(item, root);
}


template <typename T>
void BTree<T>::remove(const T& item, shared_ptr<Node<T>> ptr) {
  if (item == ptr->data) {
    auto rightNode = getOneBeforeFurthestRight(ptr->left);
    ptr->data = rightNode->right->data;
    rightNode->right = nullptr;
  }
  if ( item < ptr->data ) {
    if( ptr->left == nullptr ) {
      throw runtime_error("Item Not Found.");
      return;
    } else {
      insert(item, ptr->left);
    }
  } else {
    if (ptr->right == nullptr) {
      throw runtime_error("Item Not Found.");
    } else {
      insert(item, ptr->right);
    }
  }
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::find(const T& item) {
  return find(root, item);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::find(shared_ptr<Node<T>> ptr, const T& item) {
  if (ptr->data = item) {
    return ptr;
  }
  auto foundNode = nullptr;
  foundNode = find(ptr->right, item);
  if(!foundNode) {
    find(ptr->left, item);
  }
  return foundNode;
}

template <typename T>
bool BTree<T>::contains(const T& item) {
  
}

template <typename T>
void BTree<T>::preOrder() {
  preOrder(root);
}

template <typename T>
void BTree<T>::preOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    cout << ptr->data << " ";
    preOrder(ptr->left);
    preOrder(ptr->right);
  }
}


template <typename T>
int BTree<T>::nodeCount() {
  return nodeCount(root);
}

template <typename T>
int BTree<T>::nodeCount(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
  }
  return 0;
}

template <typename T>
void BTree<T>::postOrder() {
  postOrder(root);
}

template <typename T>
void BTree<T>::postOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    postOrder(ptr->left);
    postOrder(ptr->right);
    cout << ptr->data << ", ";
  }
}

template <typename T>
void BTree<T>::inOrder() {
  inOrder(root);
}

template <typename T>
void BTree<T>::inOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    inOrder(ptr->left);
    cout << ptr->data << ", ";
    inOrder(ptr->right);
  }
}

template <typename T>
int BTree<T>::leavesCount() {
  return leavesCount(root);
}

template <typename T>
int BTree<T>::leavesCount(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    if (!ptr->left && !ptr->right) {
      return 1;
    } else {
      return leavesCount(ptr->left) + leavesCount(ptr->right);
    }
  } else {
    return 0;
  }
}
