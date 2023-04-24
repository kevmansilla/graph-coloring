#ifndef AUX_H
#define AUX_H

#include "EstructuraGrafo23.h"
#define min(A, B) ((A) > (B) ? (B) : (A))
#define max(A, B) ((A) > (B) ? (A) : (B))

/**
 * TADs para funciones de crear ordenes
 */

typedef struct {
    u32 indice;
    u32 color;
} Tupla;

typedef struct {
    u32 indice;
    u32 valorF;
} Vertice;

/*
* Función para ordenar OrdenImparPar()
*/
int comp_impar_par(const void *a, const void *b);

/*
 * Función para ordenar OrdenJedi()
 */
int comp_jedi(const void *a, const void *b);

#endif