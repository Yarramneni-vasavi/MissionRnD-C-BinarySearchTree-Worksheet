/*
Given a Binary Search Tree ,Copy All Elements in BST into a Array in horizontal row by row fashion where
each row is copied from Right to Left.

First copy the Frist row ,Next the second row etc .
Ex : If Bst is 
    6                        <-- Copy this first 
   / \
  4  10                      <-- Copy this row next from 10 and next 4 ..
 / \   \
1   5   15                   <-- Order her is 15 ,5 ,1 
          \
          17

Output will be a array consisting of [6,10,4,15,5,1,17];

Input : BST head node ;
Output :Return An array which has All the elements in row by row order (R->L) .

Note : Return -1 for Invalid Cases .
*/

#include <stdlib.h>
#include <stdio.h>

struct node{
	struct node * left;
	int data;
	struct node *right;
};

void CountNodes(struct node *root, int *c)
{
	if (root != NULL)
	{
		(*c)++;
		CountNodes(root->left, c);
		CountNodes(root->right, c);
	}
}

void level_order(struct node *temp, int *arr, int *index, int i)
{
	if (temp == NULL)
		return;

	if (i == 0)
	{
		arr[(*index)++] = temp->data;
	}
	level_order(temp->right, arr, index, i - 1);
	level_order(temp->left, arr, index, i - 1);
}
int get_treeHeight(struct node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lefth = get_treeHeight(node->left);
		int righth = get_treeHeight(node->right);
		if (lefth > righth){
			return 1 + lefth;
		}

		return 1 + righth;
	}
}

int* BSTRighttoLeftRows(struct node* root)
{
	if (root == NULL)
		return NULL;

	int c = 0;
	CountNodes(root, &c);
	int *arr = (int *)malloc(sizeof(int)*c);
	c = 0;

	int height = get_treeHeight(root);
	for (int i = 0; i < height; i++)
	{
		level_order(root, arr, &c, i);
	}
	return arr;
}
