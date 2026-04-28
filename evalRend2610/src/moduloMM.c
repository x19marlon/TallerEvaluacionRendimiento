/*#########################################################################################
 #* Fecha:27/04/2026
 #* Autor: Maria Alejandra Rodriguez
 #* Modulo:
 #       -Modulo Multiplicacion de matrices
 #* Versión:
 #*	 	Concurrencia de Tareas: Paralelismo sobre Multiplicación de Matrices
 #* Descripción:
 #       -Módulo en C para la multiplicación de matrices, con implementación optimizada
 #	 mediante transposición,soporte para ejecución concurrente por división de filas
 #	 y medición de tiempo de ejecución.
###########################################################################################*/

#ifndef __MODULOMM_H__
#define __MODULOMM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "moduloMM.h"

// Variables para medir tiempo de ejecución
struct timeval inicio, fin;

/*
 * impMatrix:
 * Imprime una matriz cuadrada almacenada en un arreglo 1D (orden fila).
 * Solo la imprime si es pequeña (D < 13) para evitar saturar salida.
 */
void impMatrix(double *matrix, int D){
    if(D < 13){
        printf("\n");
        for(int i=0; i<D*D; i++){
            if(i % D == 0) printf("\n"); // cambio de fila
            printf("%.2f ", matrix[i]);
        }
        printf("\n*--------------------------*\n");
    }
}

/*
 * matrixTRP:
 * Calcula la transpuesta de la matriz B (mB) y la guarda en mT.
 * mT[i][j] = mB[j][i]
 */
void matrixTRP(int N, double *mB, double *mT){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            mT[i*N+j] = mB[j*N+i];

    impMatrix(mT, N);
}

/*
 * mxmForkFxT:
 * Multiplicación de matrices usando B transpuesta.
 * Calcula solo un rango de filas [filaI, filaF) -> pensado para paralelizar.
 * Optimiza acceso a memoria (producto punto fila-fila).
 */
void mxmForkFxT(double *mA, double *mT, double *mC, int D, int filaI, int filaF){
    for (int i = filaI; i < filaF; i++)
        for (int j = 0; j < D; j++) {
            double *pA, *pB, Suma = 0.0;

            pA = mA + i*D; // fila i de A
            pB = mT + j*D; // fila j de B^T

            for (int k = 0; k < D; k++, pA++, pB++)
                Suma += *pA * *pB; // producto punto

            mC[i*D+j] = Suma;
        }
}

/*
 * mxmForkFxC:
 * Multiplicación clásica (sin transpuesta).
 * También trabaja por rango de filas.
 * Menos eficiente en memoria (acceso por columnas).
 */
void mxmForkFxC(double *mA, double *mB, double *mC, int D, int filaI, int filaF){
    for (int i = filaI; i < filaF; i++)
        for (int j = 0; j < D; j++) {
            double *pA, *pB, Suma = 0.0;

            pA = mA + i*D; // fila de A
            pB = mB + j;   // columna de B

            for (int k = 0; k < D; k++, pA++, pB+=D)
                Suma += *pA * *pB;

            mC[i*D+j] = Suma;
        }
}

/*
 * InicioMuestra:
 * Guarda el tiempo actual (inicio de medición)
 */
void InicioMuestra(){
    gettimeofday(&inicio, (void *)0);
}

/*
 * FinMuestra:
 * Calcula el tiempo transcurrido desde InicioMuestra en microsegundos.
 */
void FinMuestra(){
    gettimeofday(&fin, (void *)0);

    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;

    double tiempo = (double)(fin.tv_sec*1000000 + fin.tv_usec);
    printf("%9.0f \n", tiempo);
}

/*iniMatrix:
 * Inicializa dos matrices con valores aleatorios */

void iniMatrix(double *m1, double *m2, int D){
    srand(time(NULL));

    for(int i=0; i<D*D; i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);
        *m2 = (double)rand()/RAND_MAX*(9.0-2.0);
    }
}

#endif
