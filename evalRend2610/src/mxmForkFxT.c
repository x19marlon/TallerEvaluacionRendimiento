/*#######################################################################################
#* Fecha:27/04/2026
#* Autor: Maria Alejandra Rodriguez
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

    // Verifica que se ingresen los parámetros requeridos:
    // N (tamaño de la matriz) y num_P (número de procesos)
    if (argc < 3){
        printf("Ingreso de argumentos \n $. /ejecutable tamMatriz numHilos\n");
        exit(0);
    }

    // Lectura de argumentos desde consola
    int N     = (int) atoi(argv[1]); // dimensión de la matriz NxN
    int num_P = (int) atoi(argv[2]); // número de procesos

    // Cantidad de filas que procesará cada proceso
    int filasxP = N / num_P;

    // Reserva de memoria para matrices (representadas como arreglo 1D)
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = (double *) calloc(N*N, sizeof(double));
    double *matT = (double *) calloc(N*N, sizeof(double)); // transpuesta de B

    // Inicializa matrices A y B con valores aleatorios
    iniMatrix(matA, matB, N);

    // Imprime matrices si son pequeñas
    impMatrix(matA, N);
    impMatrix(matB, N);

    // Inicia medición de tiempo
    InicioMuestra();

    // Calcula la transpuesta de B para optimizar el acceso en memoria
    matrixTRP(N, matB, matT);

    // Creación de procesos para dividir el trabajo
    for (int i = 0; i < num_P; i++) {

        pid_t pid = fork(); // crea proceso hijo

        if (pid == 0) {
            // BLOQUE DEL PROCESO HIJO

            // Determina el rango de filas que le corresponde a este proceso
            int filaI = i * filasxP;

            // El último proceso toma las filas restantes
            int filaF = (i == num_P - 1) ? N : filaI + filasxP;

            // Multiplicación usando matriz transpuesta (más eficiente)
            // Cada proceso calcula solo su bloque de filas
            mxmForkFxT(matA, matT, matC, N, filaI, filaF);

            // Si la matriz es pequeña, imprime el resultado parcial
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
            // Manejo de error en fork
            perror("fork failed");
            exit(1);
        }
    }

    // El proceso padre espera a que todos los hijos finalicen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    // Finaliza medición de tiempo y muestra el tiempo total
    FinMuestra();

    // Liberación de memoria
    free(matA);
    free(matB);
    free(matC);
    free(matT);

    return 0;
}
