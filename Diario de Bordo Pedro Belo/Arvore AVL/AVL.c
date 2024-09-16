#include <stdio.h>
#include <stdlib.h>

// Definição do nó da árvore AVL
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Função para obter a altura do nó
int height(Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // Novo nó é inicialmente adicionado na folha
    return node;
}

// Função para realizar uma rotação à direita
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna a nova raiz
    return x;
}

// Função para realizar uma rotação à esquerda
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Função para inserir um nó na árvore AVL
Node* insert(Node* node, int key) {
    // 1. Inserção normal na BST
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas
        return node;

    // 2. Atualiza a altura deste nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtém o fator de balanceamento deste nó ancestral
    int balance = getBalance(node);

    // 4. Se o nó estiver desbalanceado, aplica as rotações adequadas

    // Caso Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retorna o ponteiro do nó (inalterado se não houver rotação)
    return node;
}

// Função para imprimir a árvore em ordem
void preOrder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função principal
int main() {
    Node *root = NULL;

    // Inserção de nós
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Imprime a árvore em ordem
    printf("A travessia de pré-ordem da árvore AVL construída é:\n");
    preOrder(root);

    return 0;
}
