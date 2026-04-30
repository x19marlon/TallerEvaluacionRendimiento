# Evaluación de Rendimiento - Multiplicación de Matrices

Este repositorio contiene el código fuente, scripts de ejecución, resultados y documentación del taller de evaluación de rendimiento de algoritmos de multiplicación de matrices.

El objetivo del proyecto es comparar el rendimiento de diferentes implementaciones de multiplicación de matrices usando paralelismo con procesos `fork()` e hilos POSIX (`pthreads`), evaluando además el impacto del acceso a memoria mediante el método clásico de filas por columnas y el método optimizado usando la transpuesta de la segunda matriz.

---

## 📁 Estructura del repositorio

```text
├── Docs
│   └── Taller_de_rendimiento.pdf
├── evalRend2610
│   ├── bin
│   │   ├── mxmForkFxC
│   │   ├── mxmForkFxT
│   │   ├── mxmPosixFxC
│   │   └── mxmPosixFxT
│   ├── lanzador.pl
│   ├── Makefile
│   └── src
│       ├── moduloMM.c
│       ├── moduloMM.h
│       ├── mxmForkFxC.c
│       ├── mxmForkFxT.c
│       ├── mxmPosixFxC.c
│       └── mxmPosixFxT.c
├── excel
│   ├── AnalisisRendimientoJellyfish.xlsx
│   ├── AnalisisRendimientoNoble1A.xlsx
│   ├── AnalisisRendimientoNoble2M.xlsx
│   ├── AnalisisRendimientoPop_os.xlsx
│   └── EspecificacionesEquiposUtilizados.xlsx
├── LICENSE
└── readme.md

---
```

## ⚙️ Algoritmos evaluados

Se implementaron y compararon cuatro versiones del algoritmo de multiplicación de matrices:

* mxmForkFxC → Filas x Columnas usando procesos fork()
* mxmForkFxT → Filas x Transpuesta usando procesos fork()
* mxmPosixFxC → Filas x Columnas usando hilos POSIX (pthreads)
* mxmPosixFxT → Filas x Transpuesta usando hilos POSIX (pthreads)
## 📐 Tamaños de matrices evaluados

Se trabajó con matrices cuadradas de tamaño:

* 600 × 600
* 1200 × 1200
* 1800 × 1800
* 2400 × 2400---
## 🔢 Configuración de hilos/procesos

Cada algoritmo fue ejecutado con los siguientes valores:

    1, 2, 4, 8, 12, 24, 32

Para cada combinación se realizaron:

👉 30 repeticiones

Esto permite obtener resultados más estables y comparables.

## 🚀 Ejecución del proyecto
1. Compilar
cd evalRend2026
make
2. Ejecutar pruebas
    ./lanzador.pl
3. Ejecución remota (IMPORTANTE)

Si ejecutas por SSH:

    nohup ./lanzador.pl & exit

Esto permite que el programa:

Siga ejecutándose aunque cierres la terminal
No se detenga por desconexión SSH
Permita correr experimentos largos (horas o días)
## 📊 Resultados

Los resultados crudos se almacenan en:

    resultados/datos/

Organizados por tamaño:

    Soluciones_600
    Soluciones_1200
    Soluciones_1800
    Soluciones_2400

Cada archivo .dat contiene:

Algoritmo
Tamaño de matriz
Número de hilos/procesos
Tiempos de ejecución
## 📈 Análisis de resultados

Los archivos procesados se encuentran en:

    resultados/excel/

Incluyen:

* Promedios
* Comparaciones
* Gráficas
* Análisis de rendimiento
## 📄 Informe

El documento final está en:

    Docs/Taller_de_rendimiento.pdf

Incluye:

* Explicación de algoritmos
* Diseño de pruebas
* Descripción de equipos
* Análisis de resultados
* Conclusiones
## 🧠 Conceptos clave evaluados

Este proyecto analiza:

* Paralelismo con procesos (fork())
* Paralelismo con hilos (pthreads)
* Multiplicación de matrices
* Uso de transpuesta
* Jerarquía de memoria
* Localidad temporal
* Localidad espacial
* Uso de caché (L1, L2, L3)
## 🖥️ Requisitos
Linux (Ubuntu, Debian, etc.)
GCC
Make
Perl
POSIX Threads
## 📦 Instalación de dependencias

En Ubuntu/Debian:

    sudo apt update
    sudo apt install build-essential make perl


# Concluisones
El rendimiento de los algoritmos depende de:

* Número de núcleos
* Cantidad de hilos
* Tamaño de caché
* Acceso a memoria (filas vs columnas)
* Uso de transpuesta

👉 Por eso este proyecto compara diferentes enfoques para entender cómo influyen estos factores.
