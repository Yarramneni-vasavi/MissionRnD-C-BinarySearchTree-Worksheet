/*
Given a Binary Search Tree and a Node(temp).Find the Closest Distance from the Node to 
any leaf of the Tree.
(Least number of Edges needed to be travelled to go to the Node )

Ex : Consider the below tree .
      2
     / \
,   1   3
         \
         14
For 3 ,Output is 1 . As its closest leaf is 14 and 3 is at a distance of 1 to 14 .

Ex 2: Consider the below tree .
    2
   / \
  1   3
       \
        14
        / \
       9   20
      /      \
     6       25
For 3 ,Output is now 2 . As closest leaf to 3 is 1 and 3 is at a distance of 2 to 1 .
(through root 2 )

For 14 ,O/P : 2
For 2 , O/P : 1

Return -1 ,for Invalid Inputs
*/

#include <stdlib.h>
#include <stdio.h>

struct node{
  struct node * left;
  int data;
  struct node *right;
};
void Nodes_and_leafNodes(struct node *root, int *nodes, int *leaves)
{
	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL)
			(*leaves)++;

		(*nodes)++;
		Nodes_and_leafNodes(root->left, nodes, leaves);
		Nodes_and_leafNodes(root->right, nodes, leaves);
	}
}
void preorder_call(struct node *root, int *nodes_arr, int *leaves_arr, int *node_index, int *leaf_index)
{
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
	{
		leaves_arr[*leaf_index] = root->data;	(*leaf_index)++;
	}

	nodes_arr[*node_index] = root->data;		(*node_index)++;
	preorder_call(root->left, nodes_arr, leaves_arr, node_index, leaf_index);
	preorder_call(root->right, nodes_arr, leaves_arr, node_index, leaf_index);
}
int FindLevel(struct node *root, int k, int level)
{
	if (root == NULL)
		return -1;
	if (root->data == k)
		return level;
	int l = FindLevel(root->left, k, level + 1);
	if (l != -1)
	{
		return l;
	}
	else
		return FindLevel(root->right, k, level + 1);
}
struct node *Distance(struct node *root, int src_node, int dest_node, int &n1_dist_from_root, int &n2_dist_from_root, int &dist, int curnt_node_level)
{
	if (root == NULL)
		return NULL;
	if (root->data == src_node)
	{
		n1_dist_from_root = curnt_node_level;
		return root;
	}
	if (root->data == dest_node)
	{
		n2_dist_from_root = curnt_node_level;
		return root;
	}
	struct node *left_cmn = Distance(root->left, src_node, dest_node, n1_dist_from_root, n2_dist_from_root, dist, curnt_node_level + 1);
	struct node *right_cmn = Distance(root->right, src_node, dest_node, n1_dist_from_root, n2_dist_from_root, dist, curnt_node_level + 1);
	if (left_cmn && right_cmn)
	{
		dist = n1_dist_from_root + n2_dist_from_root - 2 * curnt_node_level;
		return root;
	}
	if (left_cmn != NULL)
		return left_cmn;
	else
		return right_cmn;
}
int Find_Distance(struct node *root, int src_node, int dest_node)
{
	int n1_dist_from_root = -1, n2_dist_from_root = -1, dist;

	struct node *common_node = Distance(root, src_node, dest_node, n1_dist_from_root, n2_dist_from_root, dist, 1);

	if (n1_dist_from_root != -1 && n2_dist_from_root != -1)
		return dist;

	if (n1_dist_from_root != -1)
	{
		dist = FindLevel(common_node, dest_node, 0);
		return dist;
	}
	if (n2_dist_from_root != -1)
	{
		dist = FindLevel(common_node, src_node, 0);
		return dist;
	}
	return -1;
}
int get_closest_leaf_distance(struct node *root, struct node *temp)
{
	if (root == NULL || temp == NULL)
		return -1;

	int n = 0, l = 0;
	Nodes_and_leafNodes(root, &n, &l);
	int *nodes_array = (int *)malloc(sizeof(int)*n);
	int *leaves_array = (int *)malloc(sizeof(int)*l);
	int node_index = 0, leaf_index = 0, ele_indx = 0;
	preorder_call(root, nodes_array, leaves_array, &node_index, &leaf_index);

	for (int i = 0; i < node_index; i++)
	{
		if (nodes_array[i] == temp->data)
			ele_indx = i;
	}
	int dist = 0;
	for (int j = 0; j < leaf_index; j++)
	{
		if (nodes_array[ele_indx + 1] == leaves_array[j])
		{
			dist = Find_Distance(root, temp->data, leaves_array[j]);
			break;
		}
	}
	if (dist == 0)
	{
		for (int j = 0; j < leaf_index; j++)
		{
			if ((ele_indx - 1) >= 0 && nodes_array[ele_indx - 1] == leaves_array[j])
			{
				dist = Find_Distance(root, temp->data, leaves_array[j]);
				break;
			}
		}
	}
	if (dist == 0)
	{
		int j = 0;
		for (int i = 0; i < n; i++)
		{
			if (nodes_array[i] == leaves_array[j])
			{
				dist = Find_Distance(root, temp->data, leaves_array[j]);
				break;
			}
		}
	}
	return dist;
}