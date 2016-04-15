/*

Given a Binary Search Tree ,Calculate its Inorder ,Postorder and PreOrder

Input : A BST
Output : Copy Inorder/Postorder/Preorder into the array specified .

Note : Memory for the Array is already allocated ,Dont allocate it again using malloc
->Take help of helper functions which are actually solving the problem .
->Dont Process Invalid Inputs

Bonus Task : 
->Go to the BSTTransversals Spec File ,We have left a custom test case for you ,Try to fill
it and understand how testing works .
*/

#include <stdio.h>

struct node{
	struct node * left;
	int data;
	struct node *right;
};

void inorder_call(struct node *root, int *arr, int *index)
{
	if (root == NULL)
		return;
	
	inorder_call(root->left, arr, index);
	*(arr + *index) = root->data;		(*index)++;
	inorder_call(root->right, arr, index);
}

void inorder(struct node *root, int *arr)
{
	if (root == NULL || arr == NULL)
		return;

	int index = 0;
	inorder_call(root, arr, &index);
}

void preorder_call(struct node *root, int *arr, int *index)
{
	if (root == NULL)
		return;

	arr[*index] = root->data;	(*index)++;
	preorder_call(root->left, arr, index);
	preorder_call(root->right, arr, index);
}

void preorder(struct node *root, int *arr)
{
	if (root == NULL || arr == NULL)
		return;

	int index = 0;
	preorder_call(root, arr, &index);
}

void postorder_call(struct node *root, int *arr, int *index)
{
	if (root == NULL)
		return;

	postorder_call(root->left, arr, index);
	postorder_call(root->right, arr, index);
	arr[*index] = root->data;	++*(index);
}

void postorder(struct node *root, int *arr)
{
	if (root == NULL || arr == NULL)
		return;

	int index = 0;
	postorder_call(root, arr, &index);
}

