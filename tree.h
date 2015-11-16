struct node {
	struct node *left;
	struct node *right;
	int data;
};
void print_ascii_tree(struct node *root);
static inline struct node* new_node(int val)
{
	struct node *temp;
	temp = (struct node *)(malloc(sizeof(struct node)));
	if (!temp) {
		 printf ("Memory not there \n");
		 return NULL;
	}
	temp->right = NULL;
	temp->left = NULL;
	temp->data = val;
	return temp;
}

