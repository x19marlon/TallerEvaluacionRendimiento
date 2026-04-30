/*#######################################################################################
 #* Fecha:27/04/2026
#* Autor: Marlon Garcia
 #* Modulo:
 #       -Paraleismo de multiplicacion de matrices
 #* Versión:
 #*	 	Concurrencia de Tareas: Paralelismo sobre Multiplicación de Matrices
 #* Descripción:
 #       - Módulo en C para multiplicación de matrices (método clásico y optimizado con
 #*    transposición), con soporte para paralelización por filas y medición de tiempo.

######################################################################################*/

#ifndef __MODULOMM_H__
#define __MODULOMM_H__

/*
 * iniMatrix:
 * Inicializa dos matrices (m1 y m2) de tamaño D x D con valores aleatorios.
 */
void iniMatrix(double *m1, double *m2, int D);

/*
 * InicioMuestra:
 * Marca el inicio de la medición de tiempo.
 */
void InicioMuestra();

/*
 * FinMuestra:
 * Calcula e imprime el tiempo transcurrido desde InicioMuestra.
 */
void FinMuestra();

/*
 * impMatrix:
 * Imprime una matriz en consola (solo si es pequeña para evitar exceso de salida).
 */
void impMatrix(double *matrix, int D);

/*
 * matrixTRP:
 * Calcula la matriz transpuesta de mB y la almacena en mT.
 */
void matrixTRP(int N, double *mB, double *mT);

/*
 * mxmForkFxC:
 * Multiplicación de matrices usando el método clásico (sin transposición).
 * Calcula solo un rango de filas [filaI, filaF) para permitir paralelización.
 */
void mxmForkFxC(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

/*
 * mxmForkFxT:
 * Multiplicación de matrices usando la matriz B transpuesta.
 * Mejora el acceso a memoria y también trabaja por rango de filas.
 */
void mxmForkFxT(double *mA, double *mT, double *mC, int D, int filaI, int filaF);

#endif
