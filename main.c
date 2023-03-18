#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "APIG23.h"

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define YELL "\e[0;33m"
#define reset "\e[0m"

int main() {
    clock_t begin = clock();
    printf(BGRN "\n--------------------------------------------------\n");
    printf(">>>> Probando proyecto Discreta II\n" reset);

    Grafo G = ConstruirGrafo();
    if (G == NULL) {
        fprintf(stderr, BRED "ERROR: El grafo está vacío.\n" reset);
        fprintf(stderr, BRED "Cerrando el programa ...\n" reset);
        exit(1);
    }
    // -------------------------------------------------
    // ----------------- Primera Parte -----------------
    // -------------------------------------------------

    printf(BBLU ">>>> Probando parte I\n" reset);
    printf(YELL ">>>> Estructura del grafo\n" reset);
    printf("El número de vertices del grafo es: %u\n",
           NumeroDeVertices(G));
    printf("El número de lados del grafo es: %u\n", NumeroDeLados(G));
    printf("El Delta del grafo es: %u.\n", Delta(G));
    printf(YELL">>>> indiceONvecino\n" reset);
    printf("indic k: %u, vertice: %u\n", 4u, Nombre(4, G));
    printf("vecinoIndice j: %u, vecino: %u\n", 0u, IndiceVecino(0, 4, G));
    printf("vecinoIndice j: %u, vecino: %u\n", 1u, IndiceVecino(1, 4, G));
    printf("vecinoIndice j: %u, vecino: %u\n", 2u, IndiceVecino(2, 4, G));

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(BBLU ">>>> Fin de la prueba" reset);
    printf(BGRN "\n--------------------------------------------------\n");
    printf(BRED "El tiempo de corrida del programa fue de: %fs\n", time_spent);
    printf("Nos vemos ...\n" reset);

    DestruirGrafo(G);
    return 0;
}