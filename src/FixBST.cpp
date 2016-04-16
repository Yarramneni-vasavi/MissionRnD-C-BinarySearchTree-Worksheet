/*

Given a Binary Search Tree ,with two misplaced Node .Find those nodes and fix them .

Do not create a new tree ,Modify the original tree
Ex : In the below tree 3 and 30 is misplaced .

  5
 / \
2   3
 \
  30
When fixed 30 will be right node of 5 , and 3 will be right node of 2 .

Ex :In the below tree 1 and 20 are misplaced

         9
        / \
       4   1
      /     \
    20      30
Nodes 1 and 20 need to be fixed here .

*/
#include <stdio.h>
#include <stdlib.h>


struct node{
	struct node * left;
	int data;
	struct node *right;
};
void inorder_traversal(struct node *root, int *arr, int *index)
{
	if (root == NULL)
		return;

	inorder_traversal(root->left, arr, index);
	arr[*index] = root->data;		(*index)++;
	inorder_traversal(root->right, arr, index);
}
void get_Nodes_count(struct node *root, int *c)
{
	if (root != NULL)
	{
		(*c)++;
		get_Nodes_count(root->left, c);
		get_Nodes_count(root->right, c);
	}
}
void Find_nodes(struct node *root, struct node **x, int x_val, struct node **y, int y_val)
{
	if (root != NULL)
	{
		if (root->data == x_val)
		{
			*x = root;
		}
		if (root->data == y_val)
		{
			*y = root;
		}
		Find_nodes(root->left, x, x_val, y, y_val);
		Find_nodes(root->right, x, x_val, y, y_val);
	}
}
void swap(struct node *x, struct node *y)
{
	int temp = x->data;
	x->data = y->data;
	y->data = temp;
}
void fix_bst(struct node *root)
{
	if (root == NULL)
		return;

	int c = 0;
	get_Nodes_count(root, &c);
	int *arr = (int *)malloc(sizeof(int)*c);
	int index = 0;
	inorder_traversal(root, arr, &index);

	int x_val = 0, y_val = 0, flag = 0;
	for (int i = 1; i < c; i++)
	{
		if (arr[i] < arr[i - 1] && flag == 1)
		{
			y_val = arr[i];
			break;
		}
		if (arr[i] < arr[i - 1] && flag == 0)
		{
			x_val = arr[i - 1];
			y_val = arr[i];
			flag = 1;
		}
	}

	struct node *x = NULL, *y = NULL;
	Find_nodes(root, &x, x_val, &y, y_val);
	swap(x, y);
}

