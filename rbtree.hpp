#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iostream"
#include "string"
using namespace std;

#define RED true
#define BLACK false

struct Node {
	int data;
	bool color;
	struct Node *left, *right, *parent;
};
string colorString;

#define struct Node Node

//constructor
Node *create (int);
void inorder(Node *root);
Node *RBInsert (Node *root, Node* n);
inline Node *parent (Node *n);
inline Node *gparent (Node *n);
inline bool isLeftChild (Node *n);
inline bool hasRedChild (Node *n);
Node *sibling (Node *n);
Node *successor (Node *n);
void swapData (Node *x, Node *y);
void rotateLeft (Node * root, Node *n);
void rotateRight (Node * root, Node *n);
void fixBlackBlack(Node *, Node *);
Node *replaceNode (Node *n);
void deleteNode (Node *root,Node *x);
void fixRBTree(Node *root, Node *n);
void fixBlackBlack (Node *root,Node *n);
void search ( Node *root, int data);
Node *searchNode (Node *root, int data);
void insert (Node *root, int data);
Node *RBInsert (Node *root, Node* n);
void fixRBTree(Node *root, Node *n);
void fixBlackBlack (Node *root,Node *n);
#endif
