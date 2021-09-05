#include "rbtree.hpp"

//Normal BST insertion
Node *RBInsert (Node *root, Node* n)
{
	if (root == NULL)
		return n;

	if (root->data > n->data)
	{
		root->left = RBInsert(root->left,n);
		//defining parent
		root->left->parent = root;
	}
	else if (root->data < n->data)
	{
		root->right = RBInsert(root->right,n);
		root->right->parent = root;
	}

	return root;
}

//initial insertion (initial insertion to RB tree is same as that of BST)
//after that we fix all the violations
void insert (Node *root, int data)
{
	Node *n = create(data);
	root = RBInsert(root,n);
	//fix violations
	fixRBTree (root,n);
}
