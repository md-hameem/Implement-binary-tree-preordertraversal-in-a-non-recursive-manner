#include <stdio.h>
#include <stdlib.h>

// Define struct for tree nodes
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Define struct for stack nodes
struct StackNode {
    struct Node* node;
    struct StackNode* next;
};

// Function to create a new tree node with the given data
struct Node* createNode(int data);

// Function to push a tree node onto the stack
void push(struct StackNode** root, struct Node* node);

// Function to pop a tree node from the stack
struct Node* pop(struct StackNode** root);

// Function to perform preorder traversal of a binary tree using a stack
void preorderTraversal(struct Node* root);

int main() {
    // Construct a binary tree and perform preorder traversal
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->right->left = createNode(4);
    root->right->right = createNode(5);

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}

struct Node* createNode(int data) {
    // Allocate memory for a new tree node and initialize its fields
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void push(struct StackNode** root, struct Node* node) {
    // Allocate memory for a new stack node and initialize its fields
    struct StackNode* stackNode = (struct StackNode*) malloc(sizeof(struct StackNode));
    if (!stackNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    stackNode->node = node;
    stackNode->next = *root;
    *root = stackNode;
}

struct Node* pop(struct StackNode** root) {
    // If the stack is empty, return NULL
    if (*root == NULL) {
        return NULL;
    }

    // Pop the top node from the stack and free its memory
    struct StackNode* temp = *root;
    struct Node* popped = temp->node;
    *root = (*root)->next;
    free(temp);

    return popped;
}

void preorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = NULL;

    push(&stack, root);

    while (stack != NULL) {
        struct Node* current = pop(&stack);
        printf("%d ", current->data);
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}
