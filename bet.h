// Zach Duncan

#ifndef _BET_H
#define _BET_H

#include <string>
using std::string;

class BET{
  private:
    // nested Node class
    struct BinaryNode {
      string str; // operator or operand
      BinaryNode* L; // left child
      BinaryNode* R; // right child

      BinaryNode(const string& s = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
          : str{s}, L{l}, R{r} {}
      BinaryNode(string&& s, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
          : str{std::move(s)}, L{l}, R{r} {}
    };

  public:
    BET(); // default zero-parameter constructor. Builds an empty tree.
    BET(const string& postfix); // one-parameter constructor, where parameter
      // "postfix" is string containing a postfix expression. The tree should be
      //built based on the postfix expression. Tokens in the postfix expression
      //are separated by spaces.
    BET(const BET&); // copy constructor -- makes appropriate deep copy of the tree
    ~BET(); // destructor -- cleans up all dynamic space in the tree
    bool buildFromPostfix(const string& postfix); // parameter "postfix" is
      // string containing a postfix expression. The tree should be built based \
      // on the postfix expression. Tokens in the postfix expression are separated
      // by spaces. If the tree contains nodes before the function is called, you
      // need to first delete the existing nodes. Return true if the new tree is
      // built successfully. Return false if an error is encountered.
    const BET & operator= (const BET &); // assignment operator -- makes appropriate
      // deep copy
    void printInfixExpression() const; // Print out the infix expression. Should do this
      // by making use of the private (recursive) version
    void printPostfixExpression() const; // Print the postfix form of the expression.
      // Use the private recursive function to help
    size_t size() const; // Return the number of nodes in the tree (using the private
      // recursive function)
    size_t leaf_nodes() const; // Return the number of leaf nodes in the tree.
      // (Use the private recursive function to help)
    bool empty() const; // return true if the tree is empty. Return false otherwise.

  private:
    void printInfixExpression(BinaryNode *n) const; // print to the standard output
      // the corresponding infix expression. Note that you may need to add
      // parentheses depending on the precedence of operators. You should not
      // have unnecessary parentheses.
    void makeEmpty(BinaryNode* &t); // delete all nodes in the subtree
      // pointed to by t.
    BinaryNode * clone(BinaryNode *t); // clone all nodes in the subtree
      // pointed to by t. Can be called by functions such as the assignment operator=.
    void printPostfixExpression(BinaryNode *n) const; // print to the standard output
      // the corresponding postfix expression.
    size_t size(BinaryNode *t) const; // return the number of nodes in the subtree
      // pointed to by t.
    size_t leaf_nodes(BinaryNode *t) const; // return the number of leaf nodes in the
      // subtree pointed to by t.

    // HELPER FUNCTIONS
    bool IsOperator(const string& o) const; // Took this from my code in Proj3
    bool LoE_Precedence(BinaryNode* n, BinaryNode* n2) const;
      // Check for lesser or equal precedence in a child BinaryNode

    BinaryNode* root;
};

#endif
