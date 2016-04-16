/*
Given a Sorted Array of integers .Create a new Balanced Binary Search Tree from the Array
and return the head of the new BST .

Ex : Input : [1,6,10]
Output : A new BST which structure is as follows 
  6
 / \
1  10

A BST is said to be balanced ,when it satisifes the following property 

Every node's Difference of Left subtree height and right-subtree height is not more than 1 .

Below Tree is Not a Balanced BST ,as 1's left subtree has height of 0 ,but 
right subtree height is 2 
(Diff >1)

  1
   \
    3
   / \
  10  5

Note : Return head of newly created BST
Note : Return Null for invalid Inputs
Note : Donot create a new BST .
*/
#include <stdlib.h>
struct node{
	struct node * left;
	int data;
	struct node *right;
};

struct node * new_node(int data){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
struct node * add_node(struct node *root, int data){
	if (root == NULL) return new_node(data);

	if (data < root->data)
		root->left = add_node(root->left, data);
	else if (data > root->data)
		root->right = add_node(root->right, data);

	return root;
}
int height_of_tree(struct node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lefth = height_of_tree(node->left);
		int righth = height_of_tree(node->right);
		if (lefth > righth){
			return 1 + lefth;
		}

		return 1 + righth;
	}
}
int isBalanced(struct node *root)
{
	if (root == NULL)
		return 1;

	int lefth;
	int righth;
	lefth = height_of_tree(root->left);
	righth = height_of_tree(root->right);

	int diff = lefth - righth;
	if (diff < 0){
		diff = diff*-1;
	}

	if (diff <= 1){
		int leftcheck = isBalanced(root->left);
		int rightcheck = isBalanced(root->right);

		if ((leftcheck == 1) && (rightcheck == 1)){
			return 1;
		}
	}

	return 0;
}

void Find_Unbalanced_node(struct node *root, struct node **temp)
{
	if (root != NULL)
	{
		int lefth = height_of_tree(root->left);
		int righth = height_of_tree(root->right);
		int diff = lefth - righth;
		if (diff < 0)
			diff = diff*(-1);

		if (diff >= 2)
		{
			*temp = root;
			return;
		}
		else if (diff <= 1)
		{
			Find_Unbalanced_node(root->left, temp);
			Find_Unbalanced_node(root->right, temp);
		}
	}
}

struct node *MakeBalanced(struct node *root, struct node *temp)
{
	if (root->left == NULL || root->left->left == NULL)
	{
		root = temp->right;
		struct node *temp_r = root;
		temp->right = NULL;
		while (temp_r->left != NULL)
		{
			temp_r = temp_r->left;
		}
		temp_r->left = temp;
	}
	else if (temp->data == root->data)
	{
		temp = root->right;
		struct node *temp1 = temp;
		while (temp1->left != NULL)
		{
			temp1 = temp1->left;
		}
		root->right = NULL;
		temp->left = NULL;
		temp1->right = temp;
		temp = root->left;
		root->left = NULL;
		temp->right->right = root;
		temp1->left = temp;
		root = temp1;
		temp1 = root->right;
		root->right = NULL;
		temp = temp1->right;
		temp1->right = NULL;
		root->right = temp;
		temp->left = temp1;
	}
	else if (temp->data > root->data && temp->left == NULL)
	{
		root->right = NULL;
		temp->left = root;
		root = temp;
		temp = temp->right;
		struct node * temp_r = NULL;
		temp_r = temp->right;
		root->right = NULL;
		temp->right = NULL;
		root->right = temp_r;
		temp_r->left = temp;
	}
	else if (temp->data < root->data)
	{
		struct node * temp_r = NULL;
		temp_r = temp->left;
		temp->left = NULL;
		root->left = NULL;
		root->left = temp_r;
		while (temp_r->right != NULL)
		{
			temp_r = temp_r->right;
		}
		temp_r->right = temp;
	}
	return root;
}

struct node *checkBalancing(struct node *root)
{
	if (isBalanced(root) == 0)
	{
		struct node *temp = NULL;
		Find_Unbalanced_node(root, &temp);
		root = MakeBalanced(root, temp);
		checkBalancing(root);
	}
	return root;
}

struct node * convert_array_to_bst(int *arr, int len)
{
	if (arr == NULL)
		return NULL;

	struct node *root = NULL;
	for (int i = 0; i < len; i++)
	{
		root = add_node(root, arr[i]);
		root = checkBalancing(root);
	}
	return root;
}