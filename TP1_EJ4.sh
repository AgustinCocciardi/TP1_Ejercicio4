#!/bin/bash

#Funcion que muestra la ayuda
function ayuda(){
    echo "Este script se ha creado con la finalidad de contar la cantidad de líneas de código y líneas de comentario de los archivos de"
    echo "determinada extensión de un directorio."
    echo "Para que funcione correctamente, se le deben pasar dos parámetros: "
    echo "El primer parámetro es la ruta del directorio <---> El segundo parámetro es la extensión de los archivos"
    echo "El script buscará en la ruta todos los directorios (y subdirectorios) y hará el análisis de aquellos que tengan la misma extensión"
    echo "Al finalizar el script, se informará la cantidad de archivos analizados, junto con los porcentajes de líneas de código y comentario"
	exit 0
} 

#Funcion que me hace salir del script si los parámetros no son correctos
function salir1(){
    echo "El numero de parametros no es correcto"
    exit 1
}

#Funcion que me hace salir del script si la ruta ingresada no es válida
function salir2(){
    echo "La ruta ingresada no es un directorio VALIDO";
	exit 2;
}

#Funcion que me hace salir del script si el directorio que pasó por parámetro está vacío
function salir3(){
    echo "El directorio que pasó por parámetro está vacío";
	exit 3;
}

#Funcion que me hace salir del script si la extensión que quiero buscar en el directorio está vacía
function salir4(){
    echo "La extensión a buscar no puede estar vacía"
    exit 4;
}

#valido que los parametros pasados sean correctos
if [ $# -lt 1 -o $# -gt 2 ]; then
    salir1
fi

#ayuda
if [ $1 = "-h" -o $1 = "-?" -o $1 = "-help" ]
then
	ayuda
fi

#valido que la ruta pasada sea un directorio
if [ ! -d "$1" ] 
then
	salir2
fi

#valido que la ruta pasada tenga archivos
dato=$(ls -1 "$1" | wc -l)

if [ "$dato" -eq 0 ] 
then
	salir3
fi

#valido que la 
if [ -z $2 ]
then
	salir4
fi

#declaro estas variables para acumular la cantidad de archivos que analizo, la cantidad de lineas de codigo y la cantidad de lineas de comentarios
cant_archivos_analizados=0
cant_lineas_codigo=0
cant_lineas_comentario=0

#me muevo a la ruta que se pasó por parámetro
cd $1

#busco en todos los subdirectorios de la ruta los archivos con la extension pasada por parámetro y los guardo en un array
archivos=$( find -name "*.$2")

#para cada archivo encontrado
for i in $archivos
do
    #incremento la cantidad de archivos analizados
    cant_archivos_analizados=$((cant_archivos_analizados+1))
    #utilizo el comando awk para contar las líneas de código. guardo el resultado en una variable auxiliar
    codigo=$(awk -f CuentaCodigo.awk $i)
    #utilizo el comando awk para contar las líneas de comentario. guardo el resultado en una variable auxiliar
    comentario=$(awk -f CuentaComentarios.awk $i)
    #incremento el contador de líneas de código
    cant_lineas_codigo=$((cant_lineas_codigo+$codigo))
    #incremento el contador de líneas de comentario
    cant_lineas_comentario=$((cant_lineas_comentario+$comentario))
done

#sumo las líneas de código y comentario
lineas_totales=$(($cant_lineas_codigo+$cant_lineas_comentario))
#obtengo el porcentaje de líneas de código sobre las líneas totales 
porcentaje_codigo=$(echo "scale=2; $cant_lineas_codigo / $lineas_totales * 100" | bc)
#obtengo el porcentaje de líneas de comentario restandole 100 el porcentaje de líneas de código
porcentaje_comentarios=$(echo "scale=2; 100 - $porcentaje_codigo" | bc)

#muestro los datos por pantalla
echo ""
echo "Se han analizado $cant_archivos_analizados archivos"
echo "Hay un total de $cant_lineas_codigo líneas de código"
echo "Hay un total de $cant_lineas_comentario líneas de comentarios"
echo "El "$porcentaje_codigo"% de líneas son de código"
echo "El "$porcentaje_comentarios"% de líneas son de comentarios"