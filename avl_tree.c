#include "EstructuraGrafo23.h"
#include "avl_tree.h"

struct Node_t {
    u32 key;              // Usado para almacenar el valor guardado por el nodo
    struct Node_t *left;  // Nodo hijo izquierdo
    struct Node_t *right; // Nodo hijo derecho
    int height;           // Altura
    u32 vert_index;       // Incide del vertice
};

// en base a la estructura del GrafoSt
static vertice CrearVertice(u32 id, u32 index) {
    vertice new_vertice = calloc(1, sizeof(struct vertice_t));
    if (new_vertice == NULL) {
        return NULL;
    }
    new_vertice->id = id;
    new_vertice->color = U32_MAX_BOUND;
    new_vertice->grado = 0;
    new_vertice->index = index;
    new_vertice->size = 1;
    new_vertice->vecinos = calloc(1, sizeof(struct vecino_t));
    if (new_vertice->vecinos == NULL) {
        return NULL;
    }

    return new_vertice;
}

int AvlHeight(Node N) {
    if (N == NULL) {
        return 0;
    }

    return N->height;
}

Node AvlNewNode(u32 vert) {
    Node node = calloc(1, sizeof(struct Node_t));
    if (node == NULL) {
        return NULL;
    }
    node->key = vert;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

Node AvlRotateRight(Node y) {
    Node x = y->left;
    Node T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(AvlHeight(y->left), AvlHeight(y->right)) + 1;
    x->height = max(AvlHeight(x->left), AvlHeight(x->right)) + 1;

    return x;
}

Node AvlRotateLeft(Node x) {
    Node y = x->right;
    Node T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(AvlHeight(x->left), AvlHeight(x->right)) + 1;
    y->height = max(AvlHeight(y->left), AvlHeight(y->right)) + 1;

    return y;
}

int AvlGetBalance(Node N) {
    if (N == NULL) {
        return 0;
    }

    return AvlHeight(N->left) - AvlHeight(N->right);
}

u32 global_index = 0;
Node AvlInsert(Node N, u32 vert, Grafo G, u32 *index_ptr) {
    // Realizar la inserción normal BST
    if (N == NULL) {
        // Si llegamos a una hoja, crear el vertice en la posición global actual
        N = AvlNewNode(vert);
        G->array_vert[global_index] = CrearVertice(vert, global_index);
        // Devolver la posición actual
        *index_ptr = global_index;
        // Guardar en el nodo la posición del vértice en el grafo
        N->vert_index = global_index;
        global_index++;
        return (N);
    }

    if (vert < N->key) {
        N->left = AvlInsert(N->left, vert, G, index_ptr);
    }
    else if (vert > N->key) {
        N->right = AvlInsert(N->right, vert, G, index_ptr);
    }
    else {
        // Los nodos de nombres idénticos no están permitidas en un BST.
        // Si el nodo ya existe, existe también en el arreglo de vértices.
        *index_ptr = N->vert_index;
        return N;
    }

    // actualizo la altura del nodo ancestro
    N->height = 1 + max(AvlHeight(N->left), AvlHeight(N->right));

    // Se obtiene el factor de balance de éste nodo ancestro para checkear
    // si fue desbalanceado o no
    int balance = AvlGetBalance(N);

    // si fue desbalanceado, hay 4 casos
    // Caso Izquierda-Izquierda
    if (balance > 1 && vert < N->left->key) {
        return AvlRotateRight(N);
    }
    // Caso Derecha-Derecha
    if (balance < -1 && vert > N->right->key) {
        return AvlRotateLeft(N);
    }
    // Caso Izquierda-Derecha
    if (balance > 1 && vert > N->left->key) {
        N->left = AvlRotateLeft(N->left);
        return AvlRotateRight(N);
    }
    // Caso Derecha-Izquierda
    if (balance < -1 && vert < N->right->key) {
        N->right = AvlRotateRight(N->right);
        return AvlRotateLeft(N);
    }

    return N;
}

void AvlDestroy(Node N) {
    if (N != NULL) {
        AvlDestroy(N->left);
        AvlDestroy(N->right);
        free(N);
        N = NULL;
    }
}

void AvlSorted(Node N, vertice *array_vert, vertice **sorted_array_arr) {
    if (N != NULL) {
        AvlSorted(N->left, array_vert, sorted_array_arr);
        **sorted_array_arr = array_vert[N->vert_index];
        ++*sorted_array_arr;
        AvlSorted(N->right, array_vert, sorted_array_arr);
    }
}