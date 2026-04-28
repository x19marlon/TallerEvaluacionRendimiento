#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: J. Corredor 
#	  Nombre Estudiante: Maria Alejandra Rodriguez
#     Fecha:27/04/2026 
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

# Obtiene la ruta actual del sistema
$Path = `pwd`;
chomp($Path);

# Lista de ejecutables a probar (diferentes implementaciones)
@Nombre_Ejecutable = ("mxmPosixFxC", "mxmPosixFxT", "mxmForkFxC", "mxmForkFxT");

# Tamaño de la matriz
@Size_Matriz = ("1800");

# Número de hilos/procesos a evaluar
@Num_Hilos = (1,2,4,8,12,32);

# Número de repeticiones por cada configuración
$Repeticiones = 30;

# Carpeta donde se guardan los resultados
$Resultados = "matriz1800";

# Carpeta donde están los ejecutables compilados
$Binarios = "bin";

# Recorre cada ejecutable
foreach $nombre (@Nombre_Ejecutable){

    # Recorre cada tamaño de matriz
    foreach $size (@Size_Matriz){

        # Recorre cada cantidad de hilos
        foreach $hilo (@Num_Hilos) {

            # Construye el nombre del archivo de salida (.dat)
            $file = "$Path/$Resultados/$nombre-".$size."-Hilos-".$hilo.".dat";

            # Imprime el archivo donde se guardarán resultados
            printf("$file \n");

            # Ejecuta varias veces el mismo experimento
            for ($i=0; $i<$Repeticiones; $i++) {

                # Ejecuta el programa y guarda la salida en el archivo
                system("$Path/$Binarios/$nombre $size $hilo >> $file");

                # Muestra en consola qué se está ejecutando
                printf("$Path/$Binarios/$nombre $size $hilo \n");
            }

            # (innecesario en este caso, no hay archivo abierto con open)
            close($file);
        }
    }
}
