/* ALGOS WHICH REQUIRE PARENT POINTER*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
};

struct node* new_node(int val)
{
	struct node *temp;

	temp = (struct node*)(malloc(sizeof(struct node)));
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	temp->data = val;
	return temp;
}

struct node* max_node(struct node* root)
{
	if (root == NULL)
		return NULL;
	if (root->right != NULL)
		return max_node(root->right);
	else
		return root;
}
struct node* min_node(struct node* root)
{
	if (root == NULL)
		return NULL;
	if (root->left != NULL)
		return min_node(root->left);
	else
		return root;
}

struct node* insert(struct node* root, int val)
{
	if (root == NULL)
		return new_node(val);
	if (val <= root->data) {
		root->left = insert(root->left, val);
		root->left->parent = root;
	}
	else {
		root->right = insert(root->right, val);
		root->right->parent = root;
	}
	return root;
}

struct node* next_largest(struct node* node)
{
	if (node == NULL)
		return NULL;
	if (node->right != NULL)
		return min_node(node->right);
	/* use parent to keep going up till
	 * we get desired value
	 */
	int val = node->data;
	while (node !=NULL) {
		if (node->data <= val)
			node = node->parent;
		else
			return node;
	}
	printf("Doesnt exist\n");
	return NULL;
}

int main(void)
{
	struct node* root = NULL, *temp, *succ;

	root = insert(root, 20);
	root = insert(root, 8);
	root = insert(root, 22);
	root = insert(root, 4);
	root = insert(root, 12);
	root = insert(root, 10);
	root = insert(root, 14);

	temp = root->right;
	succ =  next_largest(temp);
	  if(succ !=  NULL)
		      printf("\n Inorder Successor of %d is %d ", temp->data,
			     succ->data);    
	    else
		        printf("\n Inorder Successor doesn't exit");

	return 0;
}
