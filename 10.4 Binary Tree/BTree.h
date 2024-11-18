#include <iostream>
#include <memory>
using namespace std;

template <typename T> struct Node {
  T data;
  shared_ptr<Node<T>> left;
  shared_ptr<Node<T>> right;
};

template <typename T> class BTree {
public:
  void insert(const T &item);
  void remove(const T &item);
  shared_ptr<Node<T>> find(const T &item);
  bool contains(const T &item);
  shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> toFind);
  static shared_ptr<Node<T>>
  getOneBeforeFurthestRight(shared_ptr<Node<T>> ptr) {
    if (ptr && ptr->right && ptr->right->right) {
      return getOneBeforeFurthestRight(ptr->right);
    } else {
      return ptr;
    }
  }
  static shared_ptr<Node<T>> findRightMostNode(shared_ptr<Node<T>> ptr) {
    if (ptr && ptr->right) {
      return findRightMostNode(ptr->right);
    } else {
      return ptr;
    }
  }
  void preOrder();
  void inOrder();
  void postOrder();
  int nodeCount();
  int leavesCount();

private:
  void preOrder(shared_ptr<Node<T>> ptr);
  void inOrder(shared_ptr<Node<T>> ptr);
  void postOrder(shared_ptr<Node<T>> ptr);
  void insert(const T &item, shared_ptr<Node<T>> ptr);
  shared_ptr<Node<T>> find(shared_ptr<Node<T>> ptr, const T &item);
  shared_ptr<Node<T>> remove(shared_ptr<Node<T>> ptr, const T& item);
  int nodeCount(shared_ptr<Node<T>> ptr);
  int leavesCount(shared_ptr<Node<T>> ptr);
  shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> ptr,
                                 shared_ptr<Node<T>> toFind);

  shared_ptr<Node<T>> root;
};

template <typename T> void BTree<T>::insert(const T &item) {
  insert(item, root);
}

template <typename T>
void BTree<T>::insert(const T &item, shared_ptr<Node<T>> ptr) {
  if (ptr) {
    if (item < ptr->data) {
      if (ptr->left == nullptr) {
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
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> toFind) {
  return findParent(root, toFind);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> ptr, shared_ptr<Node<T>> toFind) {
  if (!ptr) {
    return nullptr;
  }
  if (ptr->right == toFind || ptr->left == toFind) {
    return ptr;
  }
  shared_ptr<Node<T>> found = nullptr;
  found = findParent(ptr->right, toFind);
  if (!found) {
    found = findParent(ptr->left, toFind);
  }
  return found;
}

template <typename T> void BTree<T>::remove(const T &item) {
  remove(root, item);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::remove(shared_ptr<Node<T>> ptr, const T& item) {
    if (ptr) {
        
        if (item < ptr->data) {
            ptr->left = remove(ptr->left, item);
        } else if (item > ptr->data) {
            ptr->right = remove(ptr->right, item);
        } else if (item == ptr->data) {
            if (!ptr->right && !ptr->left) {
                return nullptr;
            } else if (!ptr->right) {
                ptr = ptr->left;
                return ptr;
            } else if (!ptr->left) {
                ptr = ptr->right;
                return ptr;
            }
            auto temp = findRightMostNode(ptr);
            ptr->data = temp->data;
            auto tempParent = findParent(temp);
            tempParent->right = nullptr;
        }
        return ptr;
    } else {
        return nullptr;
    }
}

template <typename T> shared_ptr<Node<T>> BTree<T>::find(const T &item) {
  return find(root, item);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::find(shared_ptr<Node<T>> ptr, const T &item) {
  if (ptr) {
    if (ptr->data == item) {
      return ptr;
    }
    auto foundNode = find(ptr->left, item);
    if (!foundNode) {
      foundNode = find(ptr->right, item);
    }
    return foundNode;
  } else {
    return nullptr;
  }
}

template <typename T> bool BTree<T>::contains(const T &item) {}

template <typename T> void BTree<T>::preOrder() { preOrder(root); }

template <typename T> void BTree<T>::preOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    cout << ptr->data << " ";
    preOrder(ptr->left);
    preOrder(ptr->right);
  }
}

template <typename T> int BTree<T>::nodeCount() { return nodeCount(root); }

template <typename T> int BTree<T>::nodeCount(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
  }
  return 0;
}

template <typename T> void BTree<T>::postOrder() { postOrder(root); }

template <typename T> void BTree<T>::postOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    postOrder(ptr->left);
    postOrder(ptr->right);
    cout << ptr->data << ", ";
  }
}

template <typename T> void BTree<T>::inOrder() { inOrder(root); }

template <typename T> void BTree<T>::inOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    inOrder(ptr->left);
    cout << ptr->data << ", ";
    inOrder(ptr->right);
  }
}

template <typename T> int BTree<T>::leavesCount() { return leavesCount(root); }

template <typename T> int BTree<T>::leavesCount(shared_ptr<Node<T>> ptr) {
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
