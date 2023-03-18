#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "APIG23.h"
#include "avl_tree.h"

/**
 * Funciones auxiliares
 */

/**
 * Crear e inicializar un vecino asignando la memoria
 * correspondiente
 */
static vecino CrearVecino(vertice vert) {
    vecino new_vecino = (vecino)malloc(sizeof(struct vecino_t));
    if (new_vecino == NULL) {
        fprintf(stderr, "-- ERROR -- No se pudo crear vecino.\n");
        return NULL;
    }
    new_vecino->vert_vecino = vert;
    new_vecino->peso = 0u;
    return new_vecino;
}

/**
 * Agrega a vert el vecino vec que se encuentra en la posición
 * index
 */
static void AgregarVecino(vertice vert, vertice vec, u32 index) {
    if (vert->size == vert->grado) {
        u32 new_size = 2 * vert->size * sizeof(struct vecino_t);
        vert->vecinos = (vecino *)realloc(vert->vecinos, new_size);
        vert->size = 2 * vert->size;
    }
    vert->vecinos[index] = CrearVecino(vec);
    vert->grado++;
}

/**
 * Inserta id_fst e id_snd en el avl y crea los vértices en el array del
 * grafo, también actualiza el delta. Retorna el avl con los nuevos
 * nodos
 */
static Node InsertVert(Node vert_avl, Grafo G, u32 id_fst, u32 id_snd) {
    u32 index_fst = 0u, index_snd = 0u, index = 0u;
    vertice vert_fst = NULL, vert_snd = NULL;

    vert_avl = AvlInsert(vert_avl, id_fst, G, &index);
    index_fst = index;
    vert_fst = G->array_vert[index_fst];

    vert_avl = AvlInsert(vert_avl, id_snd, G, &index);
    index_snd = index;
    vert_snd = G->array_vert[index_snd];

    if (vert_fst->id != vert_snd->id) {
        AgregarVecino(vert_fst, vert_snd, vert_fst->grado);
        AgregarVecino(vert_snd, vert_fst, vert_snd->grado);
    }

    G->delta = max(G->delta, vert_fst->grado);
    G->delta = max(G->delta, vert_snd->grado);
    return vert_avl;
}

/**
 * Función auxiliar para liberar la memoria de
 * vertice y vecinos
 */
static void destruir_vertice(vertice vert) {
    if (vert != NULL) {
        for (u32 i = 0; (i < vert->grado) && (vert->vecinos != NULL); ++i) {
            if (vert->vecinos[i] != NULL) {
                free(vert->vecinos[i]);
                vert->vecinos[i] = NULL;
            }
        }
        free(vert->vecinos);
        vert->vecinos = NULL;
        free(vert);
        vert = NULL;
    }
}

/**
 * Construcción del grafo
 */
Grafo ConstruirGrafo() {
    // Carga de archivo y chequeo
    char buffer[255], discard[255], edge[255], indicador[255];
    u32 lados_num = 0u, vertices_num = 0u, id_fst = 0u, id_snd = 0u, check = 0u,
        counter = 0u;
    Node vert_avl = NULL;

    // Empieza a leer el archivo
    while (fgets(buffer, 255, stdin) != NULL && buffer[0] == 'c')
        ;

    // Lee la primera linea con los datos
    check = sscanf(buffer, "%s %s %u %u %s", indicador, edge, &vertices_num, &lados_num,
                   discard);
    if (check != 4 || strcmp(indicador, "p") || strcmp(edge, "edge")) {
        fprintf(stderr, "-- ERROR -- Formato invalido.\n");
        return NULL;
    }
    // Pido memoria
    Grafo G = calloc(1, sizeof(struct GrafoSt));

    // En caso que falle
    if (G == NULL) {
        fprintf(stderr, "-- ERROR -- No se pudo crear el grafo.\n");
        return NULL;
    }
    G->vertices_num = vertices_num;
    G->lados_num = lados_num;
    G->array_vert = calloc(vertices_num, (sizeof(struct vertice_t)));
    G->sorted_array = calloc(vertices_num, (sizeof(struct vertice_t)));

    // Verifico los callocs
    if (G->array_vert == NULL || G->sorted_array == NULL) {
        fprintf(stderr,
                "-- ERROR -- No se pudo crear el arreglo de vertices.\n");
        DestruirGrafo(G);
        AvlDestroy(vert_avl);
        return NULL;
    }

    // Armando el grafo y chequeos
    for (u32 i = 0u; i < lados_num; i++) {
        if ((fgets(buffer, 255, stdin) == NULL)) {
            fprintf(stderr, "-- ERROR -- Formato invalido.\n");
            DestruirGrafo(G);
            AvlDestroy(vert_avl);
            return NULL;
        }
        check =
            sscanf(buffer, "%s %u %u %s", indicador, &id_fst, &id_snd, discard);
        if (check != 3 || strcmp(indicador, "e")) {
            fprintf(stderr, "-- ERROR -- Formato invalido.\n");
            DestruirGrafo(G);
            AvlDestroy(vert_avl);
            return NULL;
        }
        // Sino falla, cargo los vertices y sumo en counter
        vert_avl = InsertVert(vert_avl, G, id_fst, id_snd);
        if (vert_avl == NULL) {
            DestruirGrafo(G);
            return NULL;
        }
        counter++;
    }

    if (counter < lados_num) {
        fprintf(stderr, "-- ERROR -- Faltan lados.\n");
        DestruirGrafo(G);
        AvlDestroy(vert_avl);
        return NULL;
    }

    // Realloc en caso que sea necesario
    for (u32 i = 0; i < vertices_num; i++) {
        if (G->array_vert != NULL) {
            vertice curr = G->array_vert[i];
            if ((curr != NULL) && (curr->size > curr->grado)) {
                curr->vecinos = (vecino *)realloc(
                    curr->vecinos, curr->grado * sizeof(struct vecino_t));
            }
        }
    }
    vertice *sorted = G->sorted_array;
    AvlSorted(vert_avl, G->array_vert, &sorted);
    // setear la posición de los vertices
    for (u32 i = 0; i < G->vertices_num; i++) {
        G->sorted_array[i]->positionON = i;
    }
    AvlDestroy(vert_avl);
    return G;
}

/**
 * Destruccción del grafo
 */
void DestruirGrafo(Grafo G) {
    if (G != NULL) {
        for (u32 i = 0; (i < G->vertices_num) && (G->array_vert != NULL); i++) {
            destruir_vertice(G->array_vert[i]);
        }
        if ((G->array_vert != NULL)) {
            free(G->array_vert);
            G->array_vert = NULL;
        }
        if ((G->sorted_array != NULL)) {
            free(G->sorted_array);
            G->sorted_array = NULL;
        }
        free(G);
        G = NULL;
    }
}

/**
 * Funciones para extraer datos del grafo
 */
u32 NumeroDeVertices(Grafo G) {
    return G->vertices_num;
}

u32 NumeroDeLados(Grafo G) {
    return G->lados_num;
}

u32 Delta(Grafo G) {
    return G->delta;
}

/**
 * Funciones para extraer info de los vértices
 */
u32 Nombre(u32 i, Grafo G) {
    if (G == NULL || i >= G->vertices_num) {
        fprintf(stderr, "-- ERROR -- Fuera de Rango.\n");
        return U32_MAX_BOUND;
    }
    return G->sorted_array[i]->id;
}

u32 Grado(u32 i, Grafo G) {
    if (G == NULL || i >= G->vertices_num) {
        fprintf(stderr, "-- ERROR -- Fuera de Rango.\n");
        return U32_MAX_BOUND;
    }
    return G->sorted_array[i]->grado;
}

/**
 * Vecinos info
 */
u32 IndiceVecino(u32 j, u32 i, Grafo G) {
    if (i < NumeroDeVertices(G) && G->sorted_array[i]->grado > j) {
        return G->sorted_array[i]->vecinos[j]->vert_vecino->positionON;
    }
    return U32_MAX_BOUND;
}