#include "rbtree.hpp"

/**********************
*  SEARCH  *
**********************/


//same as BST
//input ref :: root
void search ( Node *root, int data)
{
	//we should not corrupt root
	static Node *temp = root;
	if (data == temp->data)
	{
		cout << " found " << data << endl;
		return;
	}
	else if ( data > temp->data)
		search (root->left,data);
	else if ( data < temp->data)
		search (temp->right,data);

	//if all stack frames are called
	cout << data << " Not found " << endl;
}

//searches the node that contains the appropiate value
//To get the node to delete given the data
Node *searchNode (Node *root, int data)
{
	Node *temp = root;
	while (temp != NULL)
	{
		if (data < temp->data){
			if (temp->left == NULL)
				break;
			else
				temp = temp->left;
		}
		else if ( data == temp->data)
			break;
		else
		{
			if (temp->right == NULL)
				break;
			else 
				temp = temp->right;
		}
	}

	return temp;		
}
