#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um novo nó na árvore
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Função para procurar um valor na árvore
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

// Função para encontrar o menor nó (usado na remoção)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Função para remover um nó da árvore
Node* removeNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = removeNode(root->left, data);
    } else if (data > root->data) {
        root->right = removeNode(root->right, data);
    } else {
        // Encontrou o nó a ser removido
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos: pega o menor do subárvore direita
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

// Função de travessia em pré-ordem
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função de travessia em ordem
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Função de travessia em pós-ordem
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    // Inserindo elementos na árvore
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Exibindo as travessias
    printf("Travessia em pré-ordem: ");
    preOrder(root);
    printf("\n");

    printf("Travessia em ordem: ");
    inOrder(root);
    printf("\n");

    printf("Travessia em pós-ordem: ");
    postOrder(root);
    printf("\n");

    // Procurando um valor
    int valueToSearch = 40;
    Node* foundNode = search(root, valueToSearch);
    if (foundNode) {
        printf("Valor %d encontrado na árvore.\n", foundNode->data);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valueToSearch);
    }

    // Removendo um nó
    int valueToRemove = 30;
    root = removeNode(root, valueToRemove);
    printf("Árvore após remover %d:\n", valueToRemove);
    
    printf("Travessia em ordem: ");
    inOrder(root);
    printf("\n");

    return 0;
}
