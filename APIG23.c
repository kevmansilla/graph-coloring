#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "APIG23.h"

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeLados(Grafo G);

u32 Delta(Grafo G);

u32 Nombre(u32 i, Grafo G);

u32 Grado(u32 i, Grafo G);

u32 IndiceVecino(u32 j, u32 i, Grafo G);