/*#######################################################################################
#* Fecha:27/04/2026
#* Autor: Marlon Garcia
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "moduloMM.h" 

// Mutex para sincronización (aunque aquí no se usa para proteger nada crítico)
pthread_mutex_t MM_mutex;

// Matrices globales
double *matrixA, *matrixB, *matrixC;

/*
 * Estructura para pasar parámetros a cada hilo
 * nH  → número total de hilos
 * idH → identificador del hilo
 * N   → dimensión de la matriz
 */
struct parametros{
    int nH;
    int idH;
    int N;
};

/*
 * Función que ejecuta cada hilo
 * Realiza la multiplicación de matrices por filas
 */
void *mxmPosixFxC(void *variables){

    // Conversión de parámetros recibidos
    struct parametros *data = (struct parametros *)variables;

    int idH = data->idH;
    int nH  = data->nH;
    int D   = data->N;

    // División de trabajo: cada hilo calcula un rango de filas
    int filaI = (D/nH)*idH;
    int filaF = (D/nH)*(idH+1);

    // Multiplicación de matrices (método clásico)
    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
            double *pA, *pB, Suma = 0.0;

            pA = matrixA + i*D; // fila i de A
            pB = matrixB + j;   // columna j de B

            // producto punto fila-columna
            for (int k = 0; k < D; k++, pA++, pB+=D){
                Suma += *pA * *pB;
            }

            matrixC[i*D + j] = Suma; // resultado
        }
    }

    // Zona de sincronización (no protege nada realmente aquí)
    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    // Validación de argumentos
    if (argc < 3){
        printf("Ingreso de argumentos \n $. /ejecutable tamMatriz numHilos\n");
        exit(0);
    }

    // Lectura de parámetros
    int N      = (int) atoi(argv[1]); // tamaño matriz
    int num_Th = (int) atoi(argv[2]); // número de hilos

    // Arreglo de hilos y atributos
    pthread_t p[num_Th];
    pthread_attr_t atrMM;

    // Reserva de memoria
    matrixA = (double *)calloc(N*N, sizeof(double));
    matrixB = (double *)calloc(N*N, sizeof(double));
    matrixC = (double *)calloc(N*N, sizeof(double));

    // Inicialización de matrices
    iniMatrix(matrixA, matrixB, N);

    // Impresión (si son pequeñas)
    impMatrix(matrixA, N);
    impMatrix(matrixB, N);

    // Inicio de medición de tiempo
    InicioMuestra();

    // Inicialización de mutex y atributos de hilos
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Creación de hilos
    for (int j = 0; j < num_Th; j++){

        // Reserva y asignación de parámetros para cada hilo
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
        datos->idH = j;
        datos->nH  = num_Th;
        datos->N   = N;

        // Crea hilo y le pasa la función + parámetros
        pthread_create(&p[j], &atrMM, mxmPosixFxC, (void *)datos);
    }

    // Espera a que todos los hilos terminen
    for (int j = 0; j < num_Th; j++)
        pthread_join(p[j], NULL);

    // Fin de medición de tiempo
    FinMuestra();

    // Imprime resultado
    impMatrix(matrixC, N);

    // Liberación de memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    // Liberación de recursos de hilos
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);

    pthread_exit(NULL);

    return 0;
}
