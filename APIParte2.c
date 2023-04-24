#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "APIParte2.h"
#include "aux.h"

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
        // colores usados en los vecinos de k
        memset(colores_usados, 0, n_colores * sizeof(u32));
        u32 ind_vecino_k = 0;
        for (u32 j = 0; j < grado; j++) {
            // tomo el vecino de k
            u32 color_vecino_k = Color[IndiceVecino(ind_vecino_k, k, G)];
            // si el color del vecino es menor a n_colores, lo marco como usado
            if (color_vecino_k < n_colores) {
                colores_usados[color_vecino_k] = 1;
            }
            // incremento el indice del vecino de k
            ind_vecino_k++;
        }
        u32 color_k;
        // busco el primer color que no fue usado
        for (color_k = 0; color_k < n_colores; color_k++) {
            // si el color no fue usado, lo asigno a k
            if (colores_usados[color_k] == 0) {
                Color[k] = color_k;
                break;
            }
        }
        // si no encontre un color, le asigno uno nuevo
        if (color_k == n_colores) {
            n_colores++;
            Color[k] = color_k;
        }
    }
    free(colores_usados);
    return n_colores;
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
    qsort(temp, n, sizeof(Tupla), comp_impar_par);

    //escribimos array ordenado
    for (u32 i = 0u; i < n; i++) {
        Orden[i] = temp[i].indice;
    }
    //liberamos memoria
    free(temp);
    return 0;
}

/**
 * Orden Jedi
 */
char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 r = 0;
    //cuento la cantidad de colores
    for (u32 i = 0; i < n; i++) {
        if (Color[i] >= r) {
            r = Color[i] + 1;
        }
    }
    u32 *sumaGrados = calloc(r, sizeof(u32));
    Vertice *vertices = calloc(n, sizeof(Vertice));
    if (!sumaGrados || !vertices) {
        return 1;
    }

    // Calcular valorF para cada vértice y sumar los grados de cada color
    for (u32 i = 0; i < n; i++) {
        vertices[i].indice = i;
        u32 color = Color[i];
        u32 grado = Grado(i, G);
        vertices[i].valorF = color * grado;
        sumaGrados[color] += grado;
    }

    // Ordenar los vértices
    qsort(vertices, n, sizeof(Vertice), comp_jedi);

    // Asignar el orden a los vértices
    for (u32 i = 0; i < n; i++) {
        Orden[i] = vertices[i].indice;
    }

    // Liberar memoria
    free(sumaGrados);
    free(vertices);
    return 0;
}
