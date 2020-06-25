#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(Node *subRoot) const {
  if (!subRoot->left && !subRoot->right) {
    double finalproduct;
    finalproduct = std::stod(subRoot->elem);
    return finalproduct;
  } else {
    if (subRoot->elem == "+") {
      return eval(subRoot->left) + eval(subRoot->right);
    } else if (subRoot->elem == "-") {
      return eval(subRoot->left) - eval(subRoot->right);
    } else if (subRoot->elem == "*") {
      return eval(subRoot->left) * eval(subRoot->right);
    } else {
      return eval(subRoot->left) / eval(subRoot->right);
    }
  }
}
