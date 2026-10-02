#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key_;
    struct node* left_;
    struct node* right_;
} node_t;

node_t* create_node(int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    temp->left_ = temp->right_ = NULL;
    return temp;
}

// insertion 
node_t* insert(node_t* root, int key) {
    if(root == NULL) {
        return create_node(key);
    }
    if(key < root->key_)
        root->left_ = insert(root->left_, key);
    else if(key > root->key_)
        root->right_ = insert(root->right_, key);
    // ignore duplicates
    return root;
}

// 2. Count number of nodes
int count_nodes(node_t* root) {
    if(root == NULL) return 0;
    return 1 + count_nodes(root->left_) + count_nodes(root->right_);
}

// 3. Count number of leaves
int count_leaves(node_t* root) {
    if(root == NULL) return 0;
    if(root->left_ == NULL && root->right_ == NULL) return 1;
    return count_leaves(root->left_) + count_leaves(root->right_);
}

// 4. Compare two trees
int compare_trees(node_t* t1, node_t* t2) {
    if(t1 == NULL && t2 == NULL) return 1; // both empty
    if(t1 == NULL || t2 == NULL) return 0; // one empty
    return (t1->key_ == t2->key_) &&
           compare_trees(t1->left_, t2->left_) &&
           compare_trees(t1->right_, t2->right_);
}

// 5. Copy a tree
node_t* copy_tree(node_t* root) {
    if(root == NULL) return NULL;
    node_t* temp = create_node(root->key_);
    temp->left_ = copy_tree(root->left_);
    temp->right_ = copy_tree(root->right_);
    return temp;
}

// Utility: Inorder traversal (for testing)
void inorder(node_t* root) {
    if(root != NULL) {
        inorder(root->left_);
        printf("%d ", root->key_);
        inorder(root->right_);
    }
}

// Driver code
int main() {
    node_t* root = NULL;

    // Insert nodes
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of tree: ");
    inorder(root);
    printf("\n");

    printf("Number of nodes = %d\n", count_nodes(root));
    printf("Number of leaves = %d\n", count_leaves(root));

    // Copy tree
    node_t* copy = copy_tree(root);
    printf("Inorder traversal of copied tree: ");
    inorder(copy);
    printf("\n");

    // Compare trees
    if(compare_trees(root, copy))
        printf("Trees are identical\n");
    else
        printf("Trees are different\n");

    return 0;
}
