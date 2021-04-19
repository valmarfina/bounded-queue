#include <iostream>

#include "QueueArray.hpp"
#include "BinarySearchTree.hpp"

void testOfQueue();
void testOfTreeWalk();
void testOfComparisonOfTrees();
template<typename T>
void printTree(std::ostream &out, BinarySearchTree<T> &tree);

int main()
{
  try
  {
    testOfQueue();
    testOfTreeWalk();
    testOfComparisonOfTrees();
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what() << "\n";
  }
  return 0;
}

void testOfQueue()
{
  QueueArray<int> queue1(4);
  std::cout << "add 1 2 3 4 to queue1\n";
  queue1.push(1);
  queue1.push(2);
  queue1.push(3);
  queue1.push(4);

  std::cout << "queue1: ";
  std::cout << queue1;
  std::cout << "queue1 empty? ";
  std::cout << (queue1.isEmpty() ? "Yes" : "No") << "\n";

  std::cout << "delete element from queue1.\n";
  queue1.pop();
  std::cout << "queue1: ";
  std::cout << queue1;
  std::cout << "queue1 empty? ";
  std::cout << (queue1.isEmpty() ? "Yes" : "No") << "\n";

  std::cout << "Delete one element from queue1.\n";
  queue1.pop();
  std::cout << "queue1: ";
  std::cout << queue1;
  std::cout << "Delete one element from queue1.\n";
  queue1.pop();
  std::cout << "queue1: ";
  std::cout << queue1;
  std::cout << "delete one element from queue1.\n";
  queue1.pop();
  std::cout << "queue1: ";
  std::cout << queue1;
  std::cout << "queue1 empty? ";
  std::cout << (queue1.isEmpty() ? "Yes" : "No") << "\n";
  std::cout << "\n";

  QueueArray<int> queue2(5);
  std::cout << "Add 4 5 6 7 to queue2.\n";
  queue2.push(4);
  queue2.push(5);
  queue2.push(6);
  queue2.push(7);
  queue2.push(8);

  std::cout << "queue2: ";
  std::cout << queue2;
  std::cout << "Is queue2 empty: ";
  std::cout << (queue2.isEmpty() ? "Yes" : "No") << "\n";

  std::cout << "Delete one element from queue2.\n";
  queue2.pop();
  std::cout << queue2;
  std::cout << "Delete one element from queue2.\n";
  queue2.pop();
  std::cout << "queue2: ";
  std::cout << queue2;
  std::cout << "Is queue2 empty: ";
  std::cout << (queue2.isEmpty() ? "Yes" : "No") << "\n";

  std::cout << "Add 8 9 10 to queue2.\n";
  queue2.push(9);
  queue2.push(10);
  std::cout << "queue2: ";
  std::cout << queue2;
  std::cout << "Is queue2 empty: ";
  std::cout << (queue2.isEmpty() ? "Yes" : "No") << "\n";
  std::cout << queue2.pop() << '\n';
  std::cout << queue2.pop() << '\n';
  std::cout << queue2.pop() << '\n';
  std::cout << queue2.pop() << '\n';
  std::cout << queue2.pop() << '\n';
  std::cout << queue2;
}

void testOfTreeWalk()
{
  std::cout << "===================================================================\n";
  BinarySearchTree<int> tree;
  std::cout << "Tree: add 5 1 8 0 3 6 9 2 4 7\n";
  tree.insert(5);
  tree.insert(1);
  tree.insert(8);
  tree.insert(0);
  tree.insert(3);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(9);
  tree.insert(7);
  printTree(std::cout, tree);

  BinarySearchTree<int> tree1;
  std::cout << "Tree1: add 3 4 6 7 8 90 100";
  tree1.insert(3);
  tree1.insert(4);
  tree1.insert(6);
  tree1.insert(7);
  tree1.insert(8);
  tree1.insert(90);
  tree1.insert(100);
  printTree(std::cout, tree1);

  BinarySearchTree<int> tree2;
  std::cout << "Tree2: add 9 8 7 6 5 4 3\n";
  tree2.insert(9);
  tree2.insert(8);
  tree2.insert(7);
  tree2.insert(6);
  tree2.insert(5);
  tree2.insert(4);
  tree2.insert(3);
  printTree(std::cout, tree2);

  BinarySearchTree<int> tree3;
  std::cout << "Tree3: empty\n";
  printTree(std::cout, tree3);
}

void testOfComparisonOfTrees()
{
  std::cout << "===================================================================\n";
  BinarySearchTree<int> tree1;
  std::cout << "Tree1: add 99 88 77 66 55 44 33\n";
  tree1.insert(99);
  tree1.insert(88);
  tree1.insert(77);
  tree1.insert(66);
  tree1.insert(55);
  tree1.insert(44);
  tree1.insert(33);
  printTree(std::cout, tree1);

  BinarySearchTree<int> tree2;
  std::cout << "Tree2: add 66 88 33 99 55 77 44\n";
  tree2.insert(66);
  tree2.insert(88);
  tree2.insert(33);
  tree2.insert(99);
  tree2.insert(55);
  tree2.insert(77);
  tree2.insert(44);
  printTree(std::cout, tree2);

  std::cout << "Is tree1 and tree2 similar: ";
  std::cout << (tree1.isSimilar(tree2) ? "Yes\n" : "No\n");

  BinarySearchTree<int> tree3;
  std::cout << "\n\nTree3: add 66 88 33 99 55 77 \n";
  tree3.insert(66);
  tree3.insert(88);
  tree3.insert(33);
  tree3.insert(99);
  tree3.insert(55);
  tree3.insert(77);
  tree3.insert(44);
  tree3.insert(22);
  printTree(std::cout, tree3);

  std::cout << "Is tree2 and tree3 similar: ";
  std::cout << (tree2.isSimilar(tree3) ? "Yes\n" : "No\n");

  BinarySearchTree<int> tree4;
  std::cout << "\n\nTree4:\n";
  printTree(std::cout, tree4);

  std::cout << "Is tree4 and tree3 similar: ";
  std::cout << (tree4.isSimilar(tree3) ? "Yes\n" : "No\n");

  std::cout << "Is tree3 and tree4 similar: ";
  std::cout << (tree3.isSimilar(tree4) ? "Yes\n" : "No\n");

  std::cout << "Is tree4 and tree4 similar: ";
  std::cout << (tree4.isSimilar(tree4) ? "Yes\n" : "No\n");

  std::cout << "Is tree3 and tree3 similar: ";
  std::cout << (tree3.isSimilar(tree3) ? "Yes\n" : "No\n");
}

template<typename T>
void printTree(std::ostream &out, BinarySearchTree<T> &tree)
{
  std::cout << "\nIn width walk (iterative):\n";
  tree.printIterativeInWidth(out);
  std::cout << "\nInfix walk (iterative)\n";
  tree.printInorderIterative(out);
  std::cout << "\n\n";
}
