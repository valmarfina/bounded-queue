#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <exception>
#include <ostream>
#include "stackArray.hpp"
#include "QueueArray.hpp"

template<class T>
class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree<T> &scr) = delete;
  BinarySearchTree(BinarySearchTree<T> &&scr) noexcept;
  BinarySearchTree<T> &operator=(const BinarySearchTree<T> &src) = delete;
  BinarySearchTree<T> &operator=(BinarySearchTree<T> &&src) noexcept;
  virtual ~BinarySearchTree();

  bool iterativeSearch(const T &key) const;
  bool insert(const T &key);
  bool deleteKey(const T &key);
  int getCount() const;
  int getHeight() const;
  bool isSimilar(BinarySearchTree<T> &other) const;

  void printPreorderRecurs(std::ostream &out) const; //прямой рекурсивный
  void printInorderRecurs(std::ostream &out) const;  //инфиксный рекурсивный
  void printInorderIterative(std::ostream &out) const;  //инфиксный итеративный
  void printIterativeInWidth(std::ostream &) const;  //в ширину итеративный

  bool operator==(const BinarySearchTree<T> &src);

private:
  template<class H>
  struct Node {
    H key_;
    Node<H> *left_;
    Node<H> *right_;
    Node<H> *p_;

    explicit Node(H key, Node<H> *left = nullptr, Node<H> *right = nullptr, Node<H> *p = nullptr) :
        key_(key), left_(left), right_(right), p_(p) {}
  };

  Node<T> *root_;

  void deleteSubtree(Node<T> *node);
  Node<T> *searchNode(const T &key) const;
  Node<T> *minimum(Node<T> *node) const;
  Node<T> *maximum(Node<T> *node) const;

  bool isSimilarInOrder(Node<T> *, BinarySearchTree<T> &) const;
  void printNodeInOrder(std::ostream &out, Node<T> *root, int counter) const;
  void printNodePreorder(std::ostream &out, Node<T> *root) const;

  int getCountSubtree(const Node<T> *node) const;
  int getHeightSubTree(Node<T> *node) const;
  bool isEqual(Node<T> *, Node<T> *) const;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree():
    root_(nullptr) {}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &&scr) noexcept:
    root_(scr.root_) {
  scr.root_ = nullptr;
}

template<class T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(BinarySearchTree<T> &&src) noexcept {
  std::swap(this, src);
  return *this;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
  deleteSubtree(root_);
}

template<class T>
void BinarySearchTree<T>::deleteSubtree(Node<T> *node) {
  if (node == nullptr) {
    return;
  }
  deleteSubtree(node->left_);
  deleteSubtree(node->right_);
  delete node;
}

template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T &key) const {
  return (searchNode(key) != nullptr);
}

template<class T>
class BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::searchNode(const T &key) const {
  Node<T> *temp = root_;
  while (temp != nullptr && temp->key_ != key) {
    if (temp->key_ > key) {
      temp = temp->left_;
    } else {
      temp = temp->right_;
    }
  }
  return temp;
}

template<class T>
bool BinarySearchTree<T>::insert(const T &key) {
  if (root_ == nullptr) //пустое дерево
  {
    root_ = new Node<T>(key);
    return true;
  }
  Node<T> *temp = root_;
  while (key != temp->key_) {
    if (key < temp->key_ && temp->left_ != nullptr) //ключ меньше, и есть левый наследник
    {
      temp = temp->left_;
    } else if (key > temp->key_ && temp->right_ != nullptr) //ключ больше, и есть правый наследник
    {
      temp = temp->right_;
    }
    if (temp->left_ == nullptr && key < temp->key_) //если нашли лист и ключ меньше него
    {
      temp->left_ = new Node<T>(key, nullptr, nullptr, temp);
      return true;
    }
    if (temp->right_ == nullptr && key > temp->key_) //если нашли лист и ключ больше него
    {
      temp->right_ = new Node<T>(key, nullptr, nullptr, temp);
      return true;
    }
  }
  return false; //если такой узел уже есть
}

template<class T>
bool BinarySearchTree<T>::deleteKey(const T &key) {
  Node<T> *temp = searchNode(key);
  if (temp == nullptr) //если не найден узел с таким ключом
  {
    return false;
  }
  Node<T> *tempP = temp->p_;
  //лист
  if (temp->left_ == nullptr && temp->right_ == nullptr) {
    if (temp->p_ == nullptr) //рассматриваемый узел - корень(1 элемент в дереве)
    {
      root_ = nullptr;
      delete temp;
      return true;
    }
    if (tempP->key_ > temp->key_) //рассматриваемый узел - левый для родителя
    {
      tempP->left_ = nullptr;
    }
    if (tempP->key_ < temp->key_) //рассматриваемый узел - правый для родителя
    {
      tempP->right_ = nullptr;
    }
    delete temp;
    return true;
  }
  // 2 наследника
  if (temp->left_ != nullptr && temp->right_ != nullptr) {
    Node<T> *min = minimum(temp->right_);
    int tempValue = min->key_;
    deleteKey(min->key_);
    temp->key_ = tempValue;
    return true;
  }
  // 1 наследник
  if (tempP == nullptr)   //рассматриваемый узел - корень
  {
    if (temp->left_ == nullptr) {
      root_ = temp->right_;
    } else {
      root_ = temp->left_;
    }
    delete temp;
    root_->p_ = nullptr;
    return true;
  }
  if (temp->left_ != nullptr) {
    temp = temp->left_;
  } else {
    temp = temp->right_;
  }
  delete temp->p_;
  temp->p_ = tempP;
  if (tempP->key_ > temp->key_) {
    tempP->left_ = temp;
  } else {
    tempP->right_ = temp;
  }
  return true;
}

template<class T>
void BinarySearchTree<T>::printPreorderRecurs(std::ostream &out) const {
  printNodePreorder(out, root_);
  out << "\n";
}

template<class T>
void BinarySearchTree<T>::printInorderRecurs(std::ostream &out) const {
  printNodeInOrder(out, root_, 0);
  out << "\n";
}

template<class T>
void BinarySearchTree<T>::printNodeInOrder(std::ostream &out, Node<T> *root, int counter) const {
  if (root != nullptr) {
    printNodeInOrder(out, root->left_, counter + 1);

    out << ' ';                             //Вывод узла
    for (int i = 0; i < counter; i++) {
      out << '(';
    }
    out << root->key_;
    for (int i = 0; i < counter; i++) {
      out << ')';
    }
    out << ' ';

    printNodeInOrder(out, root->right_, counter + 1);
  }
}

template<class T>
void BinarySearchTree<T>::printNodePreorder(std::ostream &out, Node<T> *root) const {
  out << '(';
  if (root != nullptr) {
    out << root->key_;
    printNodePreorder(out, root->left_);
    printNodePreorder(out, root->right_);
  }
  out << ')';
}

template<class T>
int BinarySearchTree<T>::getCount() const {
  return getCountSubtree(this->root_);
}

template<class T>
int BinarySearchTree<T>::getCountSubtree(const Node<T> *node) const {
  if (node == nullptr) {
    return 0;
  }
  return 1 + getCountSubtree(node->left_) + getCountSubtree(node->right_);
}

template<class T>
int BinarySearchTree<T>::getHeight() const {
  if (!this->root_) {
    return 0;
  }
  return getHeightSubTree(root_);
}

template<class T>
int BinarySearchTree<T>::getHeightSubTree(Node<T> *node) const {
  if (!(node->left_ || node->right_)) //Узел не имеет наследников: высота = 1
  {
    return 1;
  }
  if (node->left_ && node->right_) //2 наследника
  {
    int leftHeight = getHeightSubTree(node->left_);
    int rightHeight = getHeightSubTree(node->right_);
    if (leftHeight > rightHeight) {
      return leftHeight + 1;
    } else {
      return rightHeight + 1;
    }
  }
  if (node->left_)    //только левый наследник
  {
    return getHeightSubTree(node->left_) + 1;
  }
  if (node->right_)   //только правый наследник
  {
    return getHeightSubTree(node->right_) + 1;
  }
  return 0;
}

template<class T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<T> &src) {
  return isEqual(this->root_, src.root_);
}

template<class T>
bool BinarySearchTree<T>::isEqual(BinarySearchTree::Node<T> *node1, BinarySearchTree::Node<T> *node2) const {
  //левая ветка
  if (node1->left_ && node2->left_)          //оба узла имеют левых наследников
  {
    if (!isEqual(node1->left_, node2->left_)) //метод сравнения для узлов
    {
      return false;
    }
  } else if (node1->left_ || node2->left_)    //только один из узлов имеет левого наследника
  {
    return false;
  }

  if (node1->key_ != node2->key_)           //сравниваем ключи
  {
    return false;
  }
  //правая ветка
  if (node1->right_ && node2->right_)     //оба узла имеют правых наследников
  {
    if (!isEqual(node1->right_, node2->right_)) {
      return false;
    }
  } else if (node1->right_ || node2->right_)  //только один из узлов имеет правых наследника
  {
    return false;
  }
  return true;
}

template<class T>
class BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::minimum(Node<T> *node) const {
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template<class T>
class BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::maximum(BinarySearchTree::Node<T> *node) const {
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template<class T>
void BinarySearchTree<T>::printInorderIterative(std::ostream &out) const {
  StackArray<Node<T> *> stack;
  Node<T> *node = root_;
  while (!stack.isEmpty() || node != nullptr) {
    if (node != nullptr) //заносим в стек и спускаемся влево
    {
      stack.push(node);
      node = node->left_;
    } else //поднимаемся к родителю, выводим его ключ и спускаемся вправо
    {
      node = stack.pop();
      out << node->key_ << ' ';
      node = node->right_;
    }
  }
  out << "\n";
}

template<class T>
void BinarySearchTree<T>::printIterativeInWidth(std::ostream &out) const {
  int countOfNodes = getCount();
  QueueArray<Node<T> *> queue(countOfNodes);
  if (countOfNodes == 0) {
    out << "\n";
    return;
  }
  Node<T> *node;
  queue.push(root_);
  while (!queue.isEmpty()) {
    node = queue.getHead();
    queue.pop();
    out << node->key_ << ' ';
    if (node->left_) {
      queue.push(node->left_);
    }
    if (node->right_) {
      queue.push(node->right_);
    }
  }
  out << "\n";
}

template<class T>
bool BinarySearchTree<T>::isSimilarInOrder(Node<T> *root, BinarySearchTree<T> &other) const{
  if (root != nullptr) {
    if (isSimilarInOrder(root->left_, other))
      if (other.iterativeSearch(root->key_))
        if (isSimilarInOrder(root->right_, other))
          return true;
    return false;
  }
  return true;
}

template<class T>
bool BinarySearchTree<T>::isSimilar(BinarySearchTree<T> &other) const {
  if (root_ == nullptr) {
    if (other.root_ == nullptr) {
      return true;
    } else {
      return false;
    }
  }
  if (other.root_ == nullptr || getCount() != other.getCount())
    return false;

  return isSimilarInOrder(root_, other);
}

#endif //BINARY_SEARCH_TREE_H
