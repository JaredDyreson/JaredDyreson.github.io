#include <iostream>

template <typename T>
class Node {
public:
  T key_;
  Node<T> *left_;
  Node<T> *right_;
  Node<T> *parent_;

  Node(Node<T> *parent = nullptr): parent_(parent) {
    left_ = right_ = nullptr;
  }

};

template <typename T>
class BST {
private:
  Node<T> *root_;
public:

  BST(): root_(nullptr) {}

  Node<T> *Search(const T &key) {
    Node<T> *cur = root_;
    while (cur != nullptr)
      if (key == cur->key_)
        return cur; // Found
      else if (key < cur->key_)
        cur = cur->left_;
      else
        cur = cur->right_;
    return nullptr; // Not found
  }


  void printInorder() {
    printInorderR(root_);
  }

  void printInorderR(Node<T> *ptr) {
    if (ptr == nullptr) return;
    printInorderR(ptr->left_);
    std::cout << ptr->key_ << std::endl;
    printInorderR(ptr->right_);
  }

  T sum() {
    return sumR(root_);
  }

  T sumR(Node<T> *node) {
    if (node == nullptr) return 0;
    return sumR(node->left_) + sumR(node->right_) + node->key_;
  }

  void Insert(const T &key) {
    Node<T> *node = new Node<T>;
    node->key_ = key;
    if (root_ == nullptr) {
      root_ = node;
      node->parent_ = nullptr;
      return;
    }

    Node<T> *cur = root_;
    while (cur != nullptr) {
      if (node->key_ < cur->key_) {
        if (cur->left_ == nullptr) {
          cur->left_ = node;
          node->parent_ = cur;
          cur = nullptr;
        }
        else
          cur = cur->left_;
      }
      else {
        if (cur->right_ == nullptr) {
          cur->right_ = node;
          node->parent_ = cur;
          cur = nullptr;
        }
        else
          cur = cur->right_;
      }
    } // end while
   }

   bool ReplaceChild(Node<T> *parent, Node<T> *currentChild, Node<T> *newChild) {
      if (parent->left_ != currentChild &&
          parent->right_ != currentChild)
         return false;

      if (parent->left_ == currentChild)
         parent->left_ = newChild;
      else
         parent->right_ = newChild;

      if (newChild != nullptr)
         newChild->parent_ = parent;
      return true;
   }

   void RemoveKey(const T &key) {
      Node<T> *node = Search(key);
      RemoveNode(node);
   }

   void RemoveNode(Node<T> *node) {
      if (node == nullptr)
         return;

      // Case 1: Internal node with 2 children
      if (node->left_ != nullptr && node->right_ != nullptr) {
         // Find successor
         Node<T> *succNode = node->right_;
         while (succNode->left_ != nullptr)
            succNode = succNode->left_;

         // Copy value/data from succNode to node
         node->key_ = succNode->key_;

         // Recursively remove succNode
         RemoveNode(succNode);
      }

      // Case 2: Root node (with 1 or 0 children)
      else if (node == root_) {
         if (node->left_ != nullptr)
            root_ = node->left_;
         else
            root_ = node->right_;

         // Make sure the new root, if non-null, has a null parent
         if (root_ != nullptr)
            root_->parent_ = nullptr;
      }

      // Case 3: Internal with left child only
      else if (node->left_ != nullptr)
         ReplaceChild(node->parent_, node, node->left_);

      // Case 4: Internal with right child only OR leaf
      else
         ReplaceChild(node->parent_, node, node->right_);
   }


};

