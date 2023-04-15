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


// static bool esColoreoPropio(Grafo G, const u32 *coloreo) {
//     bool coloreoPropio = true;
//     u32 n = NumeroDeVertices(G);
//     for (u32 i = 0u; i < n && coloreoPropio; i++) {
//         u32 grado = Grado(i, G);
//         u32 color = coloreo[i];
//         for (u32 j = 0u; j < grado && coloreoPropio; j++) {
//             coloreoPropio = (color != coloreo[IndiceVecino(j, i, G)]);
//         }
//     }
//     return coloreoPropio;
// }

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

    // printf(BBLU ">>>> Probando parte I\n" reset);
    // printf(YELL ">>>> Estructura del grafo\n" reset);
    // printf("El número de vertices del grafo es: %u\n",
    //        NumeroDeVertices(G));
    // printf("El número de lados del grafo es: %u\n", NumeroDeLados(G));
    // printf("El Delta del grafo es: %u.\n", Delta(G));
    // printf(YELL">>>> indiceONvecino\n" reset);
    // printf("indic k: %u, vertice: %u\n", 4u, Nombre(4, G));
    // printf("vecinoIndice j: %u, vecino: %u\n", 0u, IndiceVecino(0, 4, G));
    // printf("vecinoIndice j: %u, vecino: %u\n", 1u, IndiceVecino(1, 4, G));
    // printf("vecinoIndice j: %u, vecino: %u\n", 2u, IndiceVecino(2, 4, G));

    // -------------------------------------------------
    // ----------------- Segunda Parte -----------------
    // -------------------------------------------------

    // printf(BBLU ">>>> Probando parte II\n" reset);
    // //----------------- GREEDY -----------------
    // printf(YELL ">>>> Greedy\n" reset);

    // // Crear arreglo orden e inicializar con los indices de los vertices
    // u32 *orden = calloc(G->vertices_num, sizeof(u32));
    // for (u32 i = 0u; i < G->vertices_num; i++) {
    //     orden[i] = i;
    // }
    // // Arreglo de colores
    // u32 *coloreo = calloc(G->vertices_num, sizeof(u32));

    // // Greedy
    // u32 nColores = Greedy(G, orden, coloreo);
    // printf("Greedy: %u\n", nColores);

    // 1000 greedys
    // u32 indice = 0u;
    // for (u32 i = 0u; i < 1000; i++) {
    //     u32 nColores = Greedy(G, orden, coloreo);
    //     indice++;
    //     printf("Greedy: %u, Nro: %u\n", nColores, indice);
    // }

    // // Chequeo si el coloreo es propio
    // printf(YELL ">>>> Chequeo si el coloreo es propio\n" reset);
    // if(esColoreoPropio(G, coloreo) == 1){
    //     printf(BGRN "test: OK\n" reset);
    // }
    // else{
    //     printf(BRED "test: NO\n" reset);
    // }

    // libero
    // free(orden);
    // orden = NULL;
    // free(coloreo);
    // coloreo = NULL;

    // Prueba orden par e impar
    // printf(YELL ">>>> Prueba orden par-impar\n" reset);
    // // Caso de prueba 1: Arreglo con valores aleatorios
    // u32 n = 10;
    // u32 Color1[] = {3, 2, 4, 1, 5, 6, 0, 2, 4, 3};
    // u32 Orden1[n];
    // OrdenImparPar(n, Orden1, Color1);
    // printf("Caso de prueba 1: Arreglo con valores aleatorios\n");
    // printf("Color: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Color1[i]);
    // }
    // printf("\nOrden: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Orden1[i]);
    // }
    // printf("\n\n");
    // // Caso de prueba 2: Arreglo con valores repetidos
    // u32 Color2[] = {0, 1, 2, 2, 2, 3, 3, 3, 4, 5};
    // u32 Orden2[n];
    // OrdenImparPar(n, Orden2, Color2);
    // printf("Caso de prueba 2: Arreglo con valores repetidos\n");
    // printf("Color: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Color2[i]);
    // }
    // printf("\nOrden: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Orden2[i]);
    // }
    // printf("\n\n");

    // // Caso de prueba 3: Arreglo con valores todos iguales
    // u32 Color3[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    // u32 Orden3[n];
    // OrdenImparPar(n, Orden3, Color3);
    // printf("Caso de prueba 3: Arreglo con valores todos iguales\n");
    // printf("Color: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Color3[i]);
    // }
    // printf("\nOrden: ");
    // for (u32 i = 0; i < n; i++) {
    //     printf("%u ", Orden3[i]);
    // }
    // printf("\n\n");

    // Prueba orden jedi
    printf(YELL ">>>> Prueba orden jedi\n" reset);
    // Asignar colores aleatorios a los vertices
    u32 n = NumeroDeVertices(G);
    u32 *Color = (u32 *)calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        Color[i] = rand() % 3;
    }
    // Ordenar los vertices de G segun la funcion OrdenJedi
    u32 *Orden = (u32 *)calloc(n, sizeof(u32));
    char ok = OrdenJedi(G, Orden, Color);
    if (!ok) {
        printf("Orden de los vertices:\n");
        for (u32 i = 0; i < n; i++) {
            printf("%u ", Orden[i]);
        }
        printf("\n");
    } else {
        printf("Error: no se pudo ordenar los vertices\n");
    }

    free(Color);
    free(Orden);
    DestruirGrafo(G);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(BBLU ">>>> Fin de la prueba" reset);
    printf(BGRN "\n--------------------------------------------------\n");
    printf(BRED "El tiempo de corrida del programa fue de: %fs\n", time_spent);
    printf("Nos vemos ...\n" reset);

    return 0;
}