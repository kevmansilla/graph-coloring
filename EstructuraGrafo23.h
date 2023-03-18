#ifndef ESTRUCTURAGRAFO23
#define ESTRUCTURAGRAFO23

typedef unsigned int u32;
typedef struct vertice_t *vertice;
typedef struct vecino_t *vecino;

#define U32_MAX_BOUND 4294967295U //(2^32)-1

/**
 * Estructura del grafo
 */
struct GrafoSt {
    u32 vertices_num;      // número de vértices del grafo
    u32 lados_num;         // número de aristas del grafo
    u32 delta;             // delta -> mayor grado de los vértices
    vertice *array_vert;   // vértices del grafo
    vertice *sorted_array; // vértices ordenados
};

/**
 * Estructura del vertice
 */
struct vertice_t {
    u32 id;    // nombre del vértice
    u32 color; // color
    u32 grado; // número de vecinos
    u32 index; // posición del vértice
    u32 size;  // tamaño que ocupa
    u32 positionON;
    vecino *vecinos; // vértices vecinos
};

/**
 * Estructura del vecino
 */
struct vecino_t {
    u32 peso;            // peso del vecino
    vertice vert_vecino; // vértice vecino
};

#endif