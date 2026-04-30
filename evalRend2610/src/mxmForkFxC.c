
/*#######################################################################################
#* Fecha:27/04/2026
#* Autor: Marlon Garcia
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Procesos Fork
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "moduloMM.h"

int main(int argc, char *argv[]) {

    // Verifica que se ingresen los parámetros:
    // tamaño de la matriz (N) y número de procesos
    if (argc < 3){
        printf("Ingreso de argumentos \n $. /ejecutable tamMatriz numHilos\n");
        exit(0);
    }

    // Conversión de argumentos
    int N     = (int) atoi(argv[1]); // dimensión de la matriz
    int num_P = (int) atoi(argv[2]); // número de procesos

    // Cantidad de filas que le corresponde a cada proceso
    int filasxP = N / num_P;

    // Reserva de memoria para matrices (arreglo 1D)
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = (double *) calloc(N*N, sizeof(double));

    // Inicializa matrices A y B con valores aleatorios
    iniMatrix(matA, matB, N);

    // Imprime matrices si son pequeñas
    impMatrix(matA, N);
    impMatrix(matB, N);

    // Inicia medición de tiempo
    InicioMuestra();

    // Creación de procesos para paralelizar por filas
    for (int i = 0; i < num_P; i++) {

        pid_t pid = fork(); // crea proceso hijo

        if (pid == 0) {
            // BLOQUE HIJO

            // Calcula rango de filas que le corresponde a este proceso
            int filaI = i * filasxP;

            // El último proceso toma hasta N para cubrir todas las filas
            int filaF = (i == num_P - 1) ? N : filaI + filasxP;

            // Multiplicación de matrices (método clásico)
            // Cada proceso trabaja solo en su rango de filas
            mxmForkFxC(matA, matB, matC, N, filaI, filaF);

            // Si la matriz es pequeña, imprime lo que calculó este proceso
            if(N < 11){
                printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), filaI, filaF-1);

                for (int f = filaI; f < filaF; f++) {
                    for (int c = 0; c < N; c++) {
                        printf(" %.2f ", matC[N*f + c]);
                    }
                    printf("\n");
                }
            }

            // Termina el proceso hijo
            exit(0);
        }
        else if (pid < 0) {
            // Error al crear proceso
            perror("fork failed");
            exit(1);
        }
    }

    // El proceso padre espera a que todos los hijos terminen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    // Finaliza medición de tiempo y muestra resultado
    FinMuestra();

    // Liberación de memoria
    free(matA);
    free(matB);
    free(matC);

    return 0;
}
