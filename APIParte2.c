#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "APIParte2.h"

/**
 * Colorea los vertices del Grafo con un color que nunca se usa
 */
// static void DeColorar(Grafo G, u32 *array) {
//     for (u32 i = 0u; i < NumeroDeVertices(G); i++) {
//         array[i] = UINT32_MAX;
//     }
// }

/**
 * Greedy
 */
u32 Greedy(Grafo G, u32 *Orden, u32 *Color) {
    u32 n_vert = NumeroDeVertices(G);
    u32 n_colores = 1;
    u32 *colores_usados = calloc(n_vert, sizeof(u32));
    if (colores_usados == NULL) {
        fprintf(stderr, "No se pudo asignar memoria");
        return UINT32_MAX;
    }
    // Decolorar los vertices
    memset(Color, UINT32_MAX, n_vert * sizeof(u32));

    // for para colorear
    for (u32 i = 0; i < n_vert; i++) {
        // tomo el vertice de la posición k
        u32 k = Orden[i];
        u32 grado = Grado(k, G);
        memset(colores_usados, 0, n_colores * sizeof(u32));
        u32 ind_vecino_k = 0;
        for (u32 j = 0; j < grado; j++) {
            u32 color_vecino_k = Color[IndiceVecino(ind_vecino_k, k, G)];
            if (color_vecino_k < n_colores) {
                colores_usados[color_vecino_k] = 1;
            }
            ind_vecino_k++;
        }
        u32 color_k;
        for (color_k = 0; color_k < n_colores; color_k++) {
            if (colores_usados[color_k] == 0) {
                Color[k] = color_k;
                break;
            }
        }
        if (color_k == n_colores) {
            n_colores++;
            Color[k] = color_k;
        }
    }
    free(colores_usados);
    return n_colores;
}

// u32 Greedy(Grafo G, u32 *Orden, u32 *Color)
// {
//     u32 n_colores = 1;
//     u32 n_vert = NumeroDeVertices(G);

//     // Chequeo los parametros de la funcion
//     if (!G || !Orden || !Color || !n_vert)
//     {
//         fprintf(stderr, "ERROR");
//         return UINT32_MAX;
//     }
//     // Decolorar los vertices
//     DeColorar(G, Color);

//     // for para colorear
//     for (u32 i = 0; i < n_vert; i++)
//     {
//         // tomo el vertice de la posición k
//         u32 colores_usados_k = 0;
//         u32 ind_vecino_k = 0;
//         u32 color_vecino_k = 0;
//         u32 k = Orden[i];
//         // colores usados
//         u32 *colores_usados = calloc(n_colores, sizeof(u32));
//         if (!colores_usados)
//         {
//             fprintf(stderr, "No se pudo asignar memoria");
//             return UINT32_MAX;
//         }
//         u32 grado = Grado(k, G);
//         for (u32 j = 0; j < grado; j++)
//         {
//             color_vecino_k = Color[IndiceVecino(ind_vecino_k, k, G)];
//             if (color_vecino_k < n_colores && !colores_usados[color_vecino_k])
//             {
//                 // significa que si esta coloreado
//                 colores_usados[color_vecino_k] = 1;
//                 colores_usados_k++;
//             }
//             ind_vecino_k++;
//         }
//         if (colores_usados_k == n_colores)
//         {
//             // crear un nuevo color
//             n_colores++;
//             // Lo asigno al vertice en posicion natural K
//             Color[k] = n_colores - 1;
//         }
//         else
//         {
//             // buscar el primer color libre
//             for (u32 j = 0; j < n_colores; j++)
//             {
//                 if (!colores_usados[j])
//                 {
//                     // asignarlo al vertice en posicion natural k
//                     Color[k] = j;
//                     break;
//                 }
//             }
//         }
//         // liberar colores_usados
//         free(colores_usados);
//     }
//     return n_colores;
// }

/**
 * TAD para funciones de crear ordenes
 */
typedef struct {
    u32 indice;
    u32 color;
} Tupla;

/**
 * Función auxiliar que da el orden del ordenamiento
 */
int comparar(const void *a, const void *b) {
    Tupla *pa = (Tupla *)a;
    Tupla *pb = (Tupla *)b;
    if (pa->color % 2 != pb->color % 2) {
        // Si tienen paridad distinta, el de mayor paridad va primero
        return (pb->color % 2) - (pa->color % 2);
    } else {
        // Si tienen la misma paridad, el de mayor valor va primero
        return pb->color - pa->color;
    }
}

/**
 * Reordena los vertices de Color
 */
char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {
    Tupla *temp = malloc(n * sizeof(Tupla));
    if (!temp) {
        fprintf(stderr, "No se pudo asignar memoria");
        return 1;
    }
    //copia
    for (u32 i = 0u; i < n; i++) {
        temp[i].indice = i;
        temp[i].color = Color[i];
    }

    //ordenamos
    qsort(temp, n, sizeof(Tupla), comparar);

    //escribimos array ordenado
    for (u32 i = 0u; i < n; i++) {
        Orden[i] = temp[i].indice;
    }
    //liberamos memoria
    free(temp);
    return 0;
}

typedef struct {
    u32 color;
    u32 f;
    u32 index;
} Nodo;

int compare(const void *a, const void *b) {
    const Nodo *na = (const Nodo *)a;
    const Nodo *nb = (const Nodo *)b;
    if (na->f < nb->f) {
        return 1;
    } else if (na->f > nb->f) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * En resumen, este código itera sobre los colores del grafo, y para cada 
 * color, selecciona los nodos del grafo que tienen ese color, los ordena 
 * según el valor de F(x), y los agrega al arreglo Orden.
 */
char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 r = 0;
    //cuento la cantidad de colores que aparecen en color
    for (u32 i = 0; i < n; i++) {
        if (Color[i] >= r) {
            r = Color[i] + 1;
        }
    }

    Nodo *nodos = malloc(n * sizeof(Nodo));
    if (nodos == NULL) {
        fprintf(stderr, "No se pudo asignar memoria");
        return 1;
    }

    for (u32 i = 0; i < n; i++) {
        nodos[i].color = Color[i];
        nodos[i].f = Grado(i, G);
        nodos[i].index = i;
    }

    Nodo *temp = malloc(n * sizeof(Nodo));
    if (temp == NULL) {
        fprintf(stderr, "No se pudo asignar memoria");
        free(nodos);
        return 1;
    }

    //itero sobre los r-1 colores
    for (u32 c = 0; c < r; c++) {
        //contador de nodos
        u32 count = 0;
        //itero sobre los nodos y verifica si el color del nodo actual es c
        //si es así se agrega el nodo al arreglo temp y se incrementa el contador
        for (u32 i = 0; i < n; i++) {
            if (nodos[i].color == c) {
                temp[count++] = nodos[i];
            }
        }
        //ordena los nodos de temp, de mayor a menor
        qsort(temp, count, sizeof(Nodo), compare);
        //lleno el arreglo Orden con los indices de los nodos ordenados
        for (u32 i = 0; i < count; i++) {
            Orden[i] = temp[i].index;
        }
        //actualizo orden
        Orden += count;
    }
    free(nodos);
    free(temp);
    return 0;
}