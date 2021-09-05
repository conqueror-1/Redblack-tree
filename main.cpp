#include "rbtree.hpp"

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
