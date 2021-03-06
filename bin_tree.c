#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
/* Binary search trees :
 * root = X
 * left(X) <= X
 * right(X) >= X
 * Insert/Lookup can be worst case O(N) and average O(lgN)
 * This is fixed by self balancing trees -> AVL trees
 */
/* Simplified with single pointer rathern than double
 * by returning the pointer always
 *
 * Main Algos for BST trees
 * DFS - Depth First Search
 * 1. Pre-order  - Visit Root, recur left, recur right
 * 2. Post Order - Recur left, recur right, and visit root
 * 3. In order - Recur left, visit root, recur right
 *
 * BFS - Level Order
 * Find the height of tree = 1+max(left, right)
 * for i = 1  <= height call level print function
 * In level print function, if level == 1 print, if not recur left with level-1
 * and recur right with level-1
 *
 * Operations
 * 1. Search = check root, recur left or recur right based on value
 * 2. Insert = Special root modifying code so either use double pointer or use
 *    root return technique.
 * 3. Min - Recur left till end
 * 4. Max - Recur right till end
 * 5. Next Largest or Successor - 
 *    Use modified tree with parent node (take care of insert function)
 *    2 cases
 *	a. When there is a right subtree - min(right_subtree)
 *	b. when there is no right subtree - keep going up to parent till larger
 *	value comes. As soon as you find a value larger than itself return that
 *	node.
 * 6. DELETE - 
 *    3 cases
 *	a. Leaf - free it simple
 *	b. Only one subtree as child - replace with child
 *	c. 2 subtrees - Replace it with Next laregst in right subtree and free
 *	the Next largest node.
 *
 * 7. Recongnize Unique Binary Tree : 
 *    Convert tree to unique string, for every null (leaf or single child node)
 *    add a # and construct a string.
 *    Serialize a binary tree, the simplest way is to save pre/postorder and
 *    an in-order traversal. This requires 2X space so a trick is to do pre-order
 *    and store null pointers as de-limiters.
 *
 * Interesting Problems
 *
 * 1. Check if Tree is balanced
 *    delta = absolute(height(right) - height(left)
 *    delta = 0, 1 or -1 and right tree is balanced and left is balanced
 *    delta && recur right && recur left
 *    else not balanced
 * 
 * 2. Convert sorted array into tree with minimal height
 *    1. __Heapify__
 *    2. Make mid (start+end)/2 the root. then 
 *    root->left = recur(arr, start,mid-1)
 *    root->right = recur(arr, mid+1, end)
 *    return root
 * 
 */

void mirror(struct node *root)
{
	/* Store the pre-order, and then construct
	 * a tree by inserting using spacial insert
	 * which reverses the BST property ie left goes to right
	 * and right goes to left
	 */
}

void tree_to_string(struct node* root, char *ptr)
{
	static int len = 0;
	if (root == NULL) {
		len += sprintf(ptr+len, "%d ", -1);
		return;
	}

	len += sprintf(ptr+len, "%d ", root->data);
	tree_to_string(root->left, ptr);
	tree_to_string(root->right, ptr);
}

void string_to_tree(struct node** root, char *ptr)
{
	static int val;

	if ( !sscanf(ptr, "%d ", &val)) {
		return;
	}
	if (val == -1) {
		ptr+=2;
		return;
	}
	*root = new_node(val);
	string_to_tree(&(*root)->left, ptr);
	string_to_tree(&(*root)->right, ptr);
}

int nodes(struct node* root)
{
	static int count = 0;

	if (root == NULL)
		return count;
	count++;
	count = nodes(root->left);
	count = nodes(root->right);
	return count;
}

bool hassum(struct node* root, int sum)
{
	if (root == NULL)
		return (sum == 0);

	sum -= (root->data);
	return hassum(root->left, sum) || hassum(root->right, sum);
}

int max(int a, int b)
{
	if (a == b)
		return a;
	else if (a > b)
		return a;
else
		return b;
}

int depth(struct node* root)
{
	if (root == NULL)
		return 0;
	return (1 + max(depth(root->left), depth(root->right)));
}

static struct node* max_node(struct node* root)
{
	if (root == NULL)
		return NULL;
	if (root->right != NULL)
		return max_node(root->right);
	else
		return root;
}

static struct node* min_node(struct node* root)
{
	if (root == NULL)
		return root;
	if (root->left != NULL)
		return min_node(root->left);
	else
		return root;
}
/* Returns the root after insert operation has been completed
 */
void preorder(struct node *root)
{
	if (root == NULL)
		return;
	printf(" %d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void inorder(struct node *root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	printf(" %d ", root->data);
	inorder(root->right);
}

void postorder(struct node *root)
{
	if (root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf(" %d ", root->data);
}

struct node* insert(struct node *root, int val)
{
	if (root == NULL) {
		return new_node(val);
	}

	if (root->data >= val)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	return root;
}

/* Return a pointer to the searched node
 */
struct node* search(struct node *root, int val)
{
	if (root == NULL) {
		printf ("Nothing found\n");
		return NULL;
	}

	if (root->data == val)
		return root;
	else if (root->data > val)
		return search(root->left, val);
	else
		return search(root->right, val);
}
void printlevel(struct node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1) {
		printf("%d  ", root->data);
		return;
	}
	else {
		printlevel(root->right, level-1);
		printlevel(root->left, level-1);
	}
}

void levelorder(struct node* root)
{
	int h = depth(root);
	printf("Height of the tree is %d and Level Order is\n", h);
	for (int i=1; i <=h; i++) {
		printlevel(root, i);
	}
	printf("\n");
}

int main(void)
{
	struct node* root = NULL;
	//struct node* root2 = NULL;
	struct node *find = NULL;

	char str[1024];

	root = insert(root, 10);
	root = insert(root, 15);
	root = insert(root, 9);
	root = insert(root, 8);
	root = insert(root, 13);
	root = insert(root, 7);
	root = insert(root, 5);
	root = insert(root, 18);
	root = insert(root, 22);
	root = insert(root, 3);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 1);
	print_ascii_tree(root);
	find = search(root, 18);
	print_ascii_tree(root);
	find = search(root, 22);
	printf("\n\n\nDATA found is %d\n", find->data);
	find = min_node(root);
	printf("Min in this tree is %d\n", find->data);
	find = max_node(root);
	printf("Mx in this tree is %d\n", find->data);
	print_ascii_tree(root);
	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	printf("DEPTH is %d\n", depth(root));
	tree_to_string(root, str);
	printf("The STR generated is %s\n", str);
	//string_to_tree(&root2, str);
	//print_ascii_tree(root2);
	printf("COUNT is %d\n",nodes(root));
	bool res = hassum(root, 45);
	printf("Bool val is %d\n", (int)res);
	levelorder(root);
	return 0;
}
