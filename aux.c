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
    const Nodo *na = (const Nodo *)a;
    const Nodo *nb = (const Nodo *)b;
    if (na->f < nb->f) {
        return 1;
    } else if (na->f > nb->f) {
        return -1;
    } else {
        return 0;
    }
}