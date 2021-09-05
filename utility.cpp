#include "rbtree.hpp"

/**********************
 *  UTILITY FUNCTIONS  *
 **********************/
Node *create(int data)
{
	Node *n = new Node();
	n->data = data;
	n->left = NULL;
	n->right= NULL;
	n->parent= NULL;
	return n;
}


void inorder(Node *root)
{
	if (root->color == RED)
		colorString = string("RED");
	else
		colorString = string("BLACK");
	
	if (root == NULL)
		return;
	inorder(root->left);
	cout << root->data << " "<< colorString<< "   ";
	inorder(root->right);
}


inline Node *parent (Node *n)
{
	return n->parent;
}

inline Node *gparent (Node *n)
{
	return n->parent->parent;
}

inline bool isLeftChild (Node *n)
{
	return (n == parent(n)->left);
}

inline bool hasRedChild (Node *n)
{
	return ((n->left != NULL) && (n->left->color == RED)) || ((n->right != NULL) && (n->right->color == RED));
}

Node *sibling (Node *n)
{
	if (n->parent == NULL)
		return NULL;
	else if (isLeftChild(n))
		return parent(n)->right;
	//n is right child
	else 
		return parent(n)->left;
}

//Utilities for delete operations

//
//find the node without left child
Node *successor (Node *n)
{
	if (n->left != NULL)
		n = successor (n->left);

	return n;
}

void swapData (Node *x, Node *y)
{
	int temp = x->data;
	x->data = y->data;
	y->data = temp;
}
/**********************
 *  ROTATIONS  *
 **********************/

void rotateLeft (Node * root, Node *n)
{
	Node *nr = n->right;
	n->right = nr->left;

	if (n->right != NULL)
		n->right->parent = n;
	nr->parent = n->parent;

	if (n->parent == NULL)
		root = nr;
	else if ( n == n->parent->left)
		n->parent->left = nr;
	else
		n->parent->right = nr;

	nr->left = n;
	n->parent = nr;
}

void rotateRight (Node * root, Node *n)
{
	Node *nl = n->left;
	n->left = nl->right;

	if (n->left != NULL)
		n->left->parent = n;
	nl->parent = n->parent;

	if (n->parent == NULL)
		root = nl;
	else if ( n == n->parent->left)
		n->parent->left = nl;
	else
		n->parent->right = n->left;

	nl->left = n;
	n->parent = nl;

}

