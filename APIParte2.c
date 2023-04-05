#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "APIParte2.h"

u32 Greedy(Grafo G, u32 *Orden, u32 *Color);

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color);

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color);