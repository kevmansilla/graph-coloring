#ifndef STRUCTS_H
#define STRUCTS_H

#include "EstructuraGrafo23.h"

/**
 * TADs para funciones de crear ordenes
 */

typedef struct {
    u32 indice;
    u32 color;
} Tupla;

typedef struct {
    u32 color;
    u32 f;
    u32 index;
} Nodo;

/*
* Función para ordenar OrdenImparPar()
*/
int comp_impar_par(const void *a, const void *b);

/*
 * Función para ordenar OrdenJedi()
 */
int comp_jedi(const void *a, const void *b);

#endif