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
static void DeColorar(Grafo G, u32 *array) {
    for (u32 i = 0u; i < NumeroDeVertices(G); i++) {
        array[i] = UINT32_MAX;
    }
}

/**
 * Greedy
 */
u32 Greedy(Grafo G, u32 *Orden, u32 *Color) {
    u32 k = 0u, n_colores = 1u;
    u32 *colores_usados = NULL; // colores usados
    u32 n_vert = NumeroDeVertices(G);

    // Chequeo los parametros de la funcion
    if (G == NULL || Orden == NULL || Color == NULL || n_vert == 0) {
        fprintf(stderr, "ERROR");
        return UINT32_MAX;
    }
    // Decolorar los vertices
    DeColorar(G, Color);

    // for para colorear
    for (u32 i = 0u; i < n_vert; i++) {
        // tomo el vertice de la posición k
        u32 colores_usados_k = 0u;
        u32 ind_vecino_k = 0u;
        u32 color_vecino_k = 0u;
        k = Orden[i];
        // colores usados
        colores_usados = calloc(n_colores, sizeof(u32));
        if (colores_usados == NULL) {
            fprintf(stderr, "No se pudo asignar memoria");
            return UINT32_MAX;
        }
        u32 grado = Grado(k, G);
        for (u32 j = 0u; j < grado; j++) {
            color_vecino_k = Color[IndiceVecino(ind_vecino_k, k, G)];
            if (color_vecino_k < n_colores && colores_usados[color_vecino_k] == 0) {
                // significa que si esta coloreado
                colores_usados[color_vecino_k] = 1;
                colores_usados_k++;
            }
            ind_vecino_k++;
        }
        if (colores_usados_k == n_colores) {
            // crear un nuevo color
            n_colores++;
            // Lo asigno al vertice en posicion natural K
            Color[k] = n_colores - 1u;
        } else {
            // buscar el primer color libre
            for (u32 j = 0u; j < n_colores; j++) {
                if (colores_usados[j] == 0u) {
                    // asignarlo al vertice en posicion natural k
                    Color[k] = j;
                    break;
                }
            }
        }
        // liberar colores_usados
        free(colores_usados);
        colores_usados = NULL;
    }
    return n_colores;
}

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

/**
 * TAD para abstraer los elementos del vertice
 */
typedef struct {
    u32 id;
    u32 grado;
    u32 color;
} Vertice;

/**
 * Funcion auxiliar para comparar los vertices por su valor de F
 */
int comparar_vertices(const void *a, const void *b) {
    Vertice *v1 = (Vertice *)a;
    Vertice *v2 = (Vertice *)b;
    u32 f1 = v1->grado * (u32)(v1->color+1);
    u32 f2 = v2->grado * (u32)(v2->color+1);
    if (f1 > f2)
        return -1;
    if (f1 < f2)
        return 1;
    return 0;
}

/**
 * Orden Jedi
 */
char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 r = 0u;

    //cuento la cantidad de colores que aparecen en color
    for (u32 i = 0; i < n; i++) {
        if (Color[i] >= r) {
            r = Color[i] + 1;
        }
    }

    // Crear el array de vertices
    Vertice *vertices = (Vertice *)malloc(n * sizeof(Vertice));
    if (vertices == NULL) {
        fprintf(stderr, "No se pudo asignar memoria");
        return 1; 
    }

    // Inicializar estructura
    for (u32 i = 0; i < n; i++) {
        vertices[i].id = i;
        vertices[i].grado = Grado(i, G);
        vertices[i].color = Color[i];
    }

    // Ordenar los vertices segun el valor de F
    qsort(vertices, n, sizeof(Vertice), comparar_vertices);

    // Agregar los vertices al array Orden en orden decreciente de F
    for (u32 i = 0; i < n; i++) {
        Orden[i] = vertices[i].id;
    }

    free(vertices);
    return 0;
}