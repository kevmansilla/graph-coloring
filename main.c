#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "APIG23.h"
#include "APIParte2.h"

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define YELL "\e[0;33m"
#define reset "\e[0m"
#define min(A, B) ((A) > (B) ? (B) : (A))
#define CAMBIO_FLAG_ITEREACIONES 16
#define NUM_ITERACIONES 500


static bool esColoreoPropio(Grafo G, const u32 *coloreo) {
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

int main() {
    printf(YELL "\n--------------------------------------------------\n");
    printf(">>>> Probando proyecto Discreta II\n" reset);

    Grafo G = ConstruirGrafo();
    if (G == NULL) {
        fprintf(stderr, BRED "ERROR: El grafo está vacío.\n" reset);
        fprintf(stderr, BRED "Cerrando el programa ...\n" reset);
        exit(1);
    }
    u32 num_vertices = NumeroDeVertices(G);
    u32 num_lados = NumeroDeLados(G);
    u32 delta = Delta(G);

    printf(YELL ">>>> Estructura del grafo\n" reset);
    printf("El número de vertices del grafo es: %u\n", num_vertices);
    printf("El número de lados del grafo es: %u\n", num_lados);
    printf("El Delta del grafo es: %u.\n", delta);
    printf("\n");

    // creo arreglo de orden natural
    u32 *orden_natural = calloc(num_vertices, sizeof(u32));
    if (orden_natural == NULL) {
        fprintf(stderr, BRED "ERROR: No se pudo asignar memoria.\n" reset);
        exit(1);
    }
    for (u32 i = 0u; i < num_vertices; i++) {
        orden_natural[i] = i;
    }

    // Greedy
    u32 *coloreo_0 = calloc(num_vertices, sizeof(u32));
    if (coloreo_0 == NULL) {
        fprintf(stderr, BRED "ERROR: No se pudo asignar memoria.\n" reset);
        exit(1);
    }
    u32 greedy = Greedy(G, orden_natural, coloreo_0);
    if (greedy == U32_MAX_BOUND) {
        fprintf(stderr, BRED "ERROR: No se pudo colorear el grafo.\n" reset);
        exit(1);
    }

    printf("Greedy colorea el grafo en el orden natural con %u colores.\n\n",
           greedy);
    // Chequeo si el coloreo es propio
    printf(YELL ">>>> Chequeo si el coloreo es propio\n" reset);
    if(esColoreoPropio(G, coloreo_0) == 1){
        printf(BGRN "test: OK\n\n" reset);
    } else{
        printf(BRED "test: NO\n" reset);
        exit(1);
    }

    //inicio del cronometro
    clock_t begin = clock();

    u32 *coloreo_1 = calloc(num_vertices, sizeof(u32));
    u32 *coloreo_2 = calloc(num_vertices, sizeof(u32));
    if (coloreo_1 == NULL || coloreo_2 == NULL) {
        fprintf(stderr, BRED "ERROR: No se pudo asignar memoria.\n" reset);
        exit(1);
    }
    for (u32 i = 0u; i < num_vertices; i++) {
        coloreo_1[i] = coloreo_0[i];
        coloreo_2[i] = coloreo_0[i];
    }

    u32 *orden_impar = calloc(num_vertices, sizeof(u32));
    u32 *orden_jedi = calloc(num_vertices, sizeof(u32));
    if (orden_impar == NULL || orden_jedi == NULL) {
        fprintf(stderr, BRED "ERROR: No se pudo asignar memoria.\n" reset);
        exit(1);
    }
    for (u32 i = 0u; i < num_vertices; i++) {
        orden_impar[i] = orden_natural[i];
        orden_jedi[i] = orden_natural[i];
    }

    bool changeflag = 0;
    u32 Greedy1 = U32_MAX_BOUND;
    u32 Greedy2 = U32_MAX_BOUND;
    u32 greedycount = 0;
    char impar_ok = '0';
    char jedi_ok = '0';

    printf(YELL ">>>> 1000 greedys\n" reset);
    for (u32 i = 0u; i < NUM_ITERACIONES; i++) {
        if (i % CAMBIO_FLAG_ITEREACIONES == 0) {
            changeflag = !changeflag;
        }
        if (changeflag) {
            impar_ok = OrdenImparPar(num_vertices, orden_impar, coloreo_1);
            jedi_ok = OrdenJedi(G, orden_jedi, coloreo_2);
        } else {
            impar_ok = OrdenImparPar(num_vertices, orden_impar, coloreo_2);
            jedi_ok = OrdenJedi(G, orden_jedi, coloreo_1);
        }
        if (impar_ok == '0' || jedi_ok == '0') {
            printf(BRED "ERROR: Orden no válido.\n" reset);
            exit(1);
        }
        Greedy1 = min(Greedy1, Greedy(G, orden_impar, coloreo_1));
        Greedy2 = min(Greedy2, Greedy(G, orden_jedi, coloreo_2));
        greedycount ++;
        if (Greedy1 == U32_MAX_BOUND || Greedy2 == U32_MAX_BOUND) {
            printf(BRED "ERROR: No se pudo colorear el grafo.\n" reset);
            exit(1);
        }
        printf("Greedy-impar-par: %u - ", Greedy1);
        printf("Greedy-jedi: %u\n", Greedy2);
        printf(BBLU"Total de greedys: %u\n\n" reset, greedycount);
    }

    //libero memoria
    DestruirGrafo(G);
    free(orden_natural);
    free(coloreo_0);
    free(coloreo_1);
    free(coloreo_2);
    free(orden_impar);
    free(orden_jedi);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(BBLU ">>>> Fin de la prueba" reset);
    printf(BGRN "\n--------------------------------------------------\n");
    printf(BRED "El tiempo de corrida del programa fue de: %f minutos \n"reset, time_spent/60);
    return 0;
}