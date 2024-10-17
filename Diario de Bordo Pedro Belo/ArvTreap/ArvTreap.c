#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da Treap
typedef struct Node {
    int key;
    int priority;
    struct Node *left, *right;
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->priority = rand() % 100; // Atribui uma prioridade aleatória
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Rotação à esquerda
Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

// Rotação à direita
Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// Inserir um nó na Treap
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    
    if (key < root->key) {
        root->left = insert(root->left, key);
        if (root->left->priority > root->priority) {
            root = rightRotate(root);
        }
    } else {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority) {
            root = leftRotate(root);
        }
    }
    return root;
}

// Remover um nó da Treap
Node* removeNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        root->right = removeNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        if (root->left->priority > root->right->priority) {
            root = rightRotate(root);
            root->right = removeNode(root->right, key);
        } else {
            root = leftRotate(root);
            root->left = removeNode(root->left, key);
        }
    }
    return root;
}

// Imprimir a árvore por prioridade
void printByPriority(Node* root) {
    if (root != NULL) {
        printf("Chave: %d, Prioridade: %d\n", root->key, root->priority);
        printByPriority(root->left);
        printByPriority(root->right);
    }
}

// Deixar a árvore em ordem
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    // Inserindo elementos na Treap
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // Imprimindo a árvore por prioridade
    printf("Imprimindo a árvore por prioridade:\n");
    printByPriority(root);

    // Imprimindo a árvore em ordem
    printf("\nÁrvore em ordem:\n");
    inOrder(root);
    printf("\n");

    // Removendo um nó
    int keyToRemove = 30;
    root = removeNode(root, keyToRemove);
    printf("Árvore após remover %d:\n", keyToRemove);
    
    // Imprimindo a árvore em ordem após remoção
    inOrder(root);
    printf("\n");

    return 0;
}
