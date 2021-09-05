#include "iostream"
using namespace std;

#define RED true
#define BLACK false

struct Node {
	int data;
	bool color;
	struct Node *left, *right, *parent;
};

#define struct Node Node

//constructor
Node *create(int data)
{
	Node *n = new Node();
	n->data = data;
	n->left = NULL;
	n->right= NULL;
	n->parent= NULL;
	return n;
}

//inorder traversal (As this gives sorted data it is easy to debug)
void inorder(Node *root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

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

/**********************
 *  UTILITY FUNCTIONS  *
 **********************/


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

/**********************
 *  DELETIONS  *
 **********************/
void fixBlackBlack(Node *, Node *);

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







/**********************
 *  VIOLATIONS  *
 **********************/

void fixRBTree(Node *root, Node *n)
{
	while ((n != root) && (n->color != BLACK) && (parent(n)->color == RED)  )
	{
		Node *pa = parent (n);
		Node *gpa = gparent (n);

		if (pa == gpa->left)
		{
			Node *uncle = gpa->right;

			if (uncle != NULL && uncle->color == RED)
			{
				gpa->color = RED;
				pa->color = BLACK;
				uncle->color = BLACK;
				n = gpa;
			}
			//pa->color = BLACK;
			//uncle->color = BLACK;
			//n = gpa;


			else
			{
				if (n == pa->right)
				{
					rotateLeft ( root, pa);
					n = pa;
					pa = pa->parent;
				}


				rotateRight ( root, gpa);
				swap (pa->color, gpa->color);
				n = pa;
			}
		}
		else 
		{
			Node *uncle = gpa->left;

			if (uncle != NULL && uncle->color == RED)
			{
				gpa->color = RED;
				pa->color = BLACK;
				uncle->color = BLACK;
				n = gpa;
			}


			else
			{
				if (n == pa->left)
				{
					rotateRight ( root, pa);
					n = pa;
					pa = pa->parent;
				}


				rotateLeft ( root, gpa);
				swap (pa->color, gpa->color);
				n = pa;
			}

		}
	}

	//At the ending 
	root->color = BLACK;

}

void fixBlackBlack (Node *root,Node *n)
{
	if (n == root)
		return;

	Node *sib = sibling(n);
	Node *pa = parent (n);

	if (sib == NULL)
		fixBlackBlack (root,pa);
	else
	{
		if (sib->color == RED)
		{
			pa->color = RED;
			sib->color = BLACK;
			if (isLeftChild(sib))
				rotateRight (root, pa);
			else
				rotateLeft (root,pa);	
			fixBlackBlack(root, n);
		}
		else
		{
			if (hasRedChild(sib))
			{
				if (sib->left != NULL && sib->left->color == RED)
				{
					if (isLeftChild(sib))
					{
						sib->left->color = sib->color;
						sib->color = pa->color;
						rotateRight(root, pa);
					}
					else 
					{
						sib->right->color = sib->color;
						sib->color = pa->color;
						rotateLeft(root,pa);

					}
				}
				pa->color = BLACK;
			}
			else
			{
				sib->color = RED;
				if (pa->color == BLACK)
					fixBlackBlack(root,pa);
				else
					pa->color = BLACK;
			}
		}
	}
}

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
//initial insertion (initial insertion to RB tree is same as that of BST)
//after that we fix all the violations
void insert (Node *root, int data)
{
	Node *n = create(data);
	root = RBInsert(root,n);
	//fix violations
	fixRBTree (root,n);
}
int main ()
{
	Node *root = create (7);
	insert (root,3);
	insert (root,18);
	insert (root,18);
	insert (root,10);
	insert (root,22);
	insert (root,8);
	insert (root,11);
	insert (root,26);
	insert (root,2);
	insert (root,6);
	insert (root,13);
	
	//inorder (root);
	Node *f = searchNode (root,3);
	deleteNode(root, f);
	inorder (root);
	return 0;
}
