#include "rbtree.hpp"

/**********************
 *  DELETIONS  *
 **********************/

Node *replaceNode (Node *n)
{
	if (n->left != NULL && n->right != NULL)
		return successor (n->right);
	if (n->left == NULL and n->right == NULL)
		return NULL;

	if (n->left != NULL)
		return n->left;
	else 
		return n->right;

}

//Give root of tree as input to method ie the node
//instiantiated first using constructor.
void deleteNode (Node *root,Node *x)
{
	Node *y = replaceNode(x);
	Node *pa = parent (x);

	//Check if both x and y are black

	bool doubleBlack = ((x == NULL || x->color == BLACK) &&(y->color == BLACK));

	if (y == NULL)
	{
		//if y is NULL x is leaf or x is root 
		if (x == root)
		{
			root = NULL;
		}
		else{
			if (doubleBlack)
			{
				fixBlackBlack(root,x);
			}
			else if (sibling(x) != NULL)
				sibling(x)->color = RED;
			if (isLeftChild(x))
				pa->left = NULL;
			else
				pa->right=NULL;
		}
		delete x;
		return;
	}

	if (x->left == NULL || x->right == NULL)
	{
		if ( x == root)
		{
			x->data = y->data;
			x->left = NULL;
			y->right = NULL;
			delete y;
		}
		else 
		{
			if (isLeftChild(x))
				pa->left = y;
			else
				pa->right = y;

			delete x;
			y->parent = pa;//reference is saved and debugged

			if (doubleBlack)
			{
				fixBlackBlack (root,y);
			}
			else
				y->color = BLACK;
		}

		return;
	}
	//swap values of x and y
	deleteNode(root, y);

}
