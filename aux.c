#include "aux.h"


int comp_impar_par(const void *a, const void *b) {
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

int comp_jedi(const void *a, const void *b) {
    const Vertice *v1 = (const Vertice *)a;
    const Vertice *v2 = (const Vertice *)b;
    if (v1->valorF != v2->valorF) {
        return (v2->valorF > v1->valorF) - (v1->valorF > v2->valorF);
    } else {
        return (v1->indice > v2->indice) - (v2->indice > v1->indice);
    }
}

bool esColoreoPropio(Grafo G, const u32 *coloreo) {
    bool coloreoPropio = true;
    u32 n = NumeroDeVertices(G);
    for (u32 i = 0u; i < n && coloreoPropio; i++) {
        u32 grado = Grado(i, G);
        u32 color = coloreo[i];
        for (u32 j = 0u; j < grado && coloreoPropio; j++) {
            coloreoPropio = (color != coloreo[IndiceVecino(j, i, G)]);
        }
    }
    return coloreoPropio;
}
