#include <stdio.h>
#include <stdlib.h>

#define T 3  // Grau mínimo da árvore B

// Estrutura para os nós da árvore B
typedef struct BTreeNode {
    int *keys;                // Array de chaves
    int t;                    // Grau mínimo
    struct BTreeNode **C;     // Ponteiros para os filhos
    int n;                    // Número atual de chaves
    int leaf;                 // Booleano: 1 se o nó é folha, 0 caso contrário
} BTreeNode;

// Função para criar um novo nó de árvore B
BTreeNode *createNode(int t, int leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int *)malloc((2 * t - 1) * sizeof(int));
    node->C = (BTreeNode **)malloc(2 * t * sizeof(BTreeNode *));
    node->n = 0;
    return node;
}

// Função para percorrer a árvore e imprimir as chaves
void traverse(BTreeNode *node) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf)
            traverse(node->C[i]);
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf)
        traverse(node->C[i]);
}

// Função para buscar uma chave em um nó
BTreeNode *search(BTreeNode *node, int k) {
    int i = 0;
    while (i < node->n && k > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == k)
        return node;

    if (node->leaf)
        return NULL;

    return search(node->C[i], k);
}

// Função auxiliar para dividir o filho y de um nó x que está cheio
void splitChild(BTreeNode *x, int i, BTreeNode *y) {
    int t = y->t;
    BTreeNode *z = createNode(t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];

    x->C[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[t - 1];
    x->n++;
}

// Função auxiliar para inserir uma chave em um nó não cheio
void insertNonFull(BTreeNode *node, int k) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && node->keys[i] > k)
            i--;

        if (node->C[i + 1]->n == 2 * node->t - 1) {
            splitChild(node, i + 1, node->C[i + 1]);

            if (node->keys[i + 1] < k)
                i++;
        }
        insertNonFull(node->C[i + 1], k);
    }
}

// Função para inserir uma nova chave na árvore B
void insert(BTreeNode **root, int k) {
    BTreeNode *r = *root;

    if (r->n == 2 * r->t - 1) {
        BTreeNode *s = createNode(r->t, 0);
        *root = s;
        s->C[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Função principal
int main() {
    BTreeNode *root = createNode(T, 1);  // Inicializa a árvore B como uma árvore vazia

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("Percorrendo a árvore B:\n");
    traverse(root);
    printf("\n");

    int k = 6;
    (search(root, k) != NULL) ? printf("Chave %d está presente\n", k) : printf("Chave %d não está presente\n", k);

    return 0;
}
