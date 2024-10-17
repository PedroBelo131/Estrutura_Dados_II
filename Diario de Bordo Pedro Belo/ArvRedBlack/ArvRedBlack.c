#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *TNULL; // Nó sentinel
} RBTree;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED; // Novo nó é sempre vermelho
    return node;
}

// Inicializa a árvore
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->TNULL = createNode(0); // Sentinel
    tree->TNULL->color = BLACK; // O nó sentinel é sempre preto
    tree->root = tree->TNULL;
    return tree;
}

// Rotação à esquerda
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Rotação à direita
void rightRotate(RBTree* tree, Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != tree->TNULL) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Fixa a árvore Red-Black após a inserção
void fixInsert(RBTree* tree, Node* k) {
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right; // Tio

            if (u->color == RED) { // Caso 1
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) { // Caso 2
                    k = k->parent;
                    leftRotate(tree, k);
                }
                k->parent->color = BLACK; // Caso 3
                k->parent->parent->color = RED;
                rightRotate(tree, k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left; // Tio

            if (u->color == RED) { // Caso 1
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { // Caso 2
                    k = k->parent;
                    rightRotate(tree, k);
                }
                k->parent->color = BLACK; // Caso 3
                k->parent->parent->color = RED;
                leftRotate(tree, k->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Insere um nó na árvore Red-Black
void insert(RBTree* tree, int key) {
    Node* node = createNode(key);
    node->parent = NULL;

    Node* y = NULL;
    Node* x = tree->root;

    while (x != tree->TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL) {
        tree->root = node; // Se a árvore estava vazia
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    node->left = tree->TNULL;
    node->right = tree->TNULL;

    fixInsert(tree, node);
}

// Função para imprimir a árvore em ordem
void inOrderHelper(Node* node, RBTree* tree) {
    if (node != tree->TNULL) {
        inOrderHelper(node->left, tree);
        printf("%d (%s) ", node->data, node->color == RED ? "RED" : "BLACK");
        inOrderHelper(node->right, tree);
    }
}

// Função para imprimir a árvore
void inOrder(RBTree* tree) {
    inOrderHelper(tree->root, tree);
    printf("\n");
}

// Função principal
int main() {
    RBTree* tree = createRBTree();

    // Inserindo elementos na árvore
    insert(tree, 55);
    insert(tree, 40);
    insert(tree, 65);
    insert(tree, 20);
    insert(tree, 50);
    insert(tree, 70);
    insert(tree, 10);
    insert(tree, 30);

    // Exibindo a árvore em ordem
    printf("Árvore em ordem:\n");
    inOrder(tree);

    return 0;
}
