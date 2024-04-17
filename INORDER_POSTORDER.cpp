#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to search for the index of an element in an array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1; // If element not found
}

// Helper function to construct the binary search tree
struct TreeNode* buildTree(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    // Create a new node with the value of the last element in postOrder array
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postOrder[(*postIndex)--];
    root->left = NULL;
    root->right = NULL;

    // If the node has no children, return it
    if (inStart == inEnd)
        return root;

    // Find the index of the root node in inOrder array
    int inIndex = search(inOrder, inStart, inEnd, root->val);

    // Construct the right and left subtrees recursively
    root->right = buildTree(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    root->left = buildTree(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return root;
}

// Function to construct the binary search tree from in-order and post-order traversals
struct TreeNode* bst_construct(int inOrder[], int postOrder[], int size) {
    int postIndex = size - 1; // Index of the last element in postOrder array
    return buildTree(inOrder, postOrder, 0, size - 1, &postIndex);
}

// Function to traverse the binary tree in breadth-first-search (BFS) traversal and print the nodes
void breadthFirstSearch(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Queue to store the nodes for BFS traversal
    struct TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->val); // Print the current node's value

        if (current->left)
            queue[rear++] = current->left;

        if (current->right)
            queue[rear++] = current->right;
    }
}

int main() {
    // In-order and post-order traversal arrays
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int size = sizeof(inOrder) / sizeof(inOrder[0]);

    // Print post-order traversal
    printf("Post-order: ");
    for (int i = 0; i < size; i++) {
        printf("%d", postOrder[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");

    // Print in-order traversal
    printf("In-order: ");
    for (int i = 0; i < size; i++) {
        printf("%d", inOrder[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");

    // Construct the binary search tree
    struct TreeNode* root = bst_construct(inOrder, postOrder, size);

    // Traverse and print the binary search tree in breadth-first-search (BFS) traversal
    printf("BFS traversal: ");
    breadthFirstSearch(root);

    return 0;
}

