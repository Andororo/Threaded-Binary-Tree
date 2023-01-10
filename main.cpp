/**
 * @file main.cpp
 * @brief Driver file for threaded binary tree for tree class
 * @author Braxton Goss & Andrew Pham
 */
#include "tree.h"
#include "treeNode.h"
#include <iostream>

using namespace std;

// used within main driver to validate user entry
// to make sure that entry is only >1, non-negative, and whole numbers.
bool isValidEntry(string userInput) {
  bool isValid = true;
  // check for decimal or negative
  for (int i = 0; i < userInput.length(); i++) {
    if (userInput[i] == '.' || userInput[i] == '-') {
      isValid = false;
      break;
    }
  }
  // check for zero input or less
  if (stoi(userInput) < 1) {
    isValid = false;
  }
  return isValid;
}

// Driver Program
int main() {
  string userEntry;
  cout << "Enter Tree Size: ";
  cin >> userEntry;
  while (!isValidEntry(userEntry)) {
    cout << "Invalid Entry, Non-Negative and Whole Numbers are only accepted."
         << endl;
    cin.clear();
    cin.ignore(100, '\n');
    cout << "Enter Tree Size: ";
    cin >> userEntry;
  }
  Tree tree1(stoi(userEntry));

  cout << "-----Tree1-----" << endl;
  // display original tree1
  tree1.printInOrder(tree1.getRoot());

  // // copy constructor
  cout << "\nCreating copy of Tree1...." << endl;
  Tree tree2(tree1);

  cout << "\n-----Testing deep copies-----" << endl;
  cout << "Memory Address of tree1: " << &tree1 << endl;
  cout << "Memory Address of tree2: " << &tree2 << endl;
  if (&tree1 != &tree2) {
    cout << "Tree1 and Tree2 are deep copies" << endl;
  } else {
    // should never reach this line due to our implementation
    cout << "Tree1 and Tree2 are shallow copies" << endl;
  }

  cout << "\n-----Tree2-----" << endl;
  tree2.printInOrder(tree2.getRoot()); // print tree2

  // removing even numbers
  cout << "\nRemoving Evens from Tree2...." << endl;
  tree2.removeEvens(stoi(userEntry));

  // tree1 should not be modified
  cout << "\n-----Tree1 is not modified-----" << endl;
  tree1.printInOrder(
      tree1.getRoot()); // display tree 1 after tree 2 was modified
  cout << "\n-----Tree2 is modified-----" << endl;
  tree2.printInOrder(tree2.getRoot());
  cout << "\n";

  return 0;
}