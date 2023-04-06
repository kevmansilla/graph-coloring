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

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color);

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color);