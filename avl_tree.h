#ifndef _TREE_
#define _TREE_

/**
 * en base a -> https://www.geeksforgeeks.org/avl-tree-set-1-insertion
 *           -> https://programmerclick.com/article/4481359464/
 *           -> https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
 *           -> https://programmerclick.com/article/72641037701/
 */

#include "APIG23.h"

/* Definición de macros */
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) > (B) ? (B) : (A))

typedef struct Node_t *Node;

/**
 * height del arbol
 */
int AvlHeight(Node N);

/**
 * Crea un nuevo nodo de la estructura
 */
Node AvlNewNode(u32 vtx);

/**
 * Rota el avl a la izquierda
 */
Node AvlRotateLeft(Node x);

/**
 * Rota el avl a la Derecha
 */
Node AvlRotateRight(Node y);

/**
 * Devuelve la diferencia entre la altura de la rama derecha y la izquierda.
 */
int AvlGetBalance(Node N);

/**
 * Inserta un nuevo nodo en su posición correspondiente
 * y balancea el árbol resultante. Crea el vértice vtx
 * y lo agrega al grafo.
 */
Node AvlInsert(Node node, u32 vtx, Grafo graph, u32 *index_ptr);

/**
 * Destruye el avl
 */
void AvlDestroy(Node root);

/**
 * Ordena en un array los elementos, recorriendo inorden al avl
 */
void AvlSorted(Node root, vertice *array_vert, vertice **sorted_array_arr);

#endif
