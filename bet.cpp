// Zach Duncan

#ifndef _BET_CPP
#define _BET_CPP

#include "bet.h"
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

//-------------------------PUBLIC CLASS FUNCTINONS-----------------------------
BET::BET() // default zero-parameter constructor. Builds an empty tree.
{ root = new BinaryNode; }

BET::BET(const string& postfix) // one-parameter constructor, where parameter
  // "postfix" is string containing a postfix expression. The tree should be
  // built based on the postfix expression. Tokens in the postfix expression
  // are separated by spaces.
{
  root = new BinaryNode;
  if (! buildFromPostfix(postfix)) //If true, tree is built correctly
    cout << "Invalid postfix expression.\n";
}

BET::BET(const BET& tree) // copy constructor -- makes appropriate deep copy of the tree
{ root = clone(tree.root); }

BET::~BET() // destructor -- cleans up all dynamic space in the tree
{
  if (! empty())
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix) // parameter "postfix" is
  // string containing a postfix expression. The tree should be built based \
  // on the postfix expression. Tokens in the postfix expression are separated
  // by spaces. If the tree contains nodes before the function is called, you
  // need to first delete the existing nodes. Return true if the new tree is
  // built successfully. Return false if an error is encountered.
{
  if (! empty())
    makeEmpty(root); // clear tree first if it is not empty

  stack<BinaryNode*> stack, temp;
  string token;
  istringstream iss(postfix); // create string stream for postfix stream

  while (iss >> token) // WHILE LINE IS STILL BEING READ
  {
    if (! IsOperator(token)) // if an OPERAND
    {
      BinaryNode* operand = new BinaryNode(token); // then create node
      stack.push(operand); // and push it onto the stack
    }
    else // if an OPERATOR
    {
      if (stack.size() < 2) // If there are not two operands for an operator
      {
        while (! stack.empty())
          stack.pop();
        return false; // then there is an error, return false
      }
      else
      {
        BinaryNode* myOperator = new BinaryNode(token); // then create node
        myOperator->R = stack.top(); // set node's R child as top of stack
        //cout << stack.top()->str;
        stack.pop(); // and then pop it off stack
        myOperator->L = stack.top(); // do same for left child
        //cout << stack.top()->str;
        stack.pop();
        stack.push(myOperator); // operator is now pointing correctly to
      }                         // children nodes, push to stack
    }
  } // End of while loop

  if (stack.size() != 1) // If stack is empty OR has more than one BinaryNode*
  {                      // remainging, then there was an error
    while (! stack.empty())
      stack.pop();
    return false;
  }
  else
  {
    root = stack.top();  //else, top of stack is now root of tree,
    //cout << stack.top()->str;
    //cout << " " << stack.top()->L->str << " " << stack.top()->R->str;
    return true;         //and tree is ready to go, return true
  }
}

const BET& BET::operator=(const BET & tree) // assignment operator -- makes appropriate
  // deep copy
{
  root = clone(tree.root); // call clone
  return *this; // and return
}

void BET::printInfixExpression() const // Print out the infix expression. Should do this
  // by making use of the private (recursive) version
{
  printInfixExpression(root);
  cout << "\n";
}

void BET::printPostfixExpression() const // Print the postfix form of the expression.
  // Use the private recursive function to help
{
  printPostfixExpression(root);
  cout << "\n";
}

size_t BET::size() const // Return the number of nodes in the tree (using the private
  // recursive function)
{ return size(root); }

size_t BET::leaf_nodes() const // Return the number of leaf nodes in the tree.
  // (Use the private recursive function to help)
{ return leaf_nodes(root); }

bool BET::empty() const // return true if the tree is empty. Return false otherwise.
{
  if (root == nullptr)
    return true;
  else
    return false;
}

//-------------------------PRIVATE CLASS FUNCTINONS-----------------------------
void BET::printInfixExpression(BinaryNode *n) const // print to the standard output
  // the corresponding infix expression. Note that you may need to add
  // parentheses depending on the precedence of operators. You should not
  // have unnecessary parentheses. USE INORDER TRAVERSAL
{
  if (empty()) // if nothing to print
    cout << "";
  else if(n->L == nullptr && n->R == nullptr) // if a leaf node
    cout << n->str << " ";
  else
  {
    // if left child is of lesser or equal precdence AND child is an operator
    // AND the parent is * or /, then we need parentheses
    if ( LoE_Precedence(n, n->L) && IsOperator(n->L->str) &&
         ( n->str == "*" || n->str == "/") )
    {
      cout << "( ";
      printInfixExpression(n->L);
      cout << ") ";
    }
    else
      printInfixExpression(n->L);

    cout << n->str << " ";

    // similar on right side, but do not need to check if parent if * or /
    if ( LoE_Precedence(n, n->R) && IsOperator(n->R->str) )
    {
      cout << "( ";
      printInfixExpression(n->R);
      cout << ") ";
    }
    else
      printInfixExpression(n->R);
  }
}

void BET::makeEmpty(BinaryNode* &t) // delete all nodes in the subtree
  // pointed to by t.
{
  if (t != nullptr)
  {
    makeEmpty(t->L); // delete left tree first
    makeEmpty(t->R); // then right
    delete t;        // then vertex
  }
}

BET::BinaryNode* BET::clone(BinaryNode *t) // clone all nodes in the subtree
  // pointed to by t. Can be called by functions such as the assignment operator=.
{
  if (t == nullptr) // if t is not initialized
    return nullptr;
  else // else, copy with t as root, and making a clone of L and R children throughout tree
    return new BinaryNode(t->str, clone(t->L), clone(t->R));
}

void BET::printPostfixExpression(BinaryNode *n) const // print to the standard output
  // the corresponding postfix expression.
{
  if (empty()) // if nothing to print
    cout << "";
  else if(n->L == nullptr) // if no children, only need to check L node, binary tree
    cout << n->str << " ";
  else
  {
    printPostfixExpression(n->L); // print left first
    printPostfixExpression(n->R); // then right
    cout << n->str << " ";        // then vertex
  }
}

size_t BET::size(BinaryNode *t) const // return the number of nodes in the subtree
  // pointed to by t.
{
  if (t == nullptr) // if t is not initialized
    return 0;
  else
    return (1 + size(t->L) + size(t->R));
}

size_t BET::leaf_nodes(BinaryNode *t) const // return the number of leaf nodes in the
  // subtree pointed to by t.
{
  if (t == nullptr) // if t is not initialized
    return 0;
  else if (t->L == nullptr) // only need to check L node, as this is a binary tree
    return 1;
  else
    return (leaf_nodes(t->L) + leaf_nodes(t->R));
}

//--------------------------ADDED HELPER FUNCTINONS-----------------------------

// Return true if character is an operator, false otherwise (from my Proj3 code)
bool BET::IsOperator(const string& o) const
{
  if (o == "+" || o == "-" || o == "*" || o == "/")
    return true;
  else
    return false;
}

// Check for lesser or equal precedence in a child BinaryNode
bool BET::LoE_Precedence(BinaryNode* n, BinaryNode* n2) const // n is parent, n2 is child
{
  if (! IsOperator(n->str) && ! IsOperator(n2->str) ) // if child is not an operator
    return false;
  else if (n->str == "*" || n->str == "/") // if parent is of high precedence
    return true;
  else if (n2->str == "*" || n2->str == "/") // if cihld is of high precedence
    return false;
  else // if of same lower precedence
    return true;
}

#endif
