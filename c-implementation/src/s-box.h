#include <stdlib.h>

#define RADIX 16
#define MATRIX_ORDER 4

/**
 * Estructura principal de la tabla s-box
 * */
typedef struct S_box {
	int matrix[RADIX][RADIX];				//tabla original (se usa en el proceso de encriptacion)
	int inv_matrix[RADIX][RADIX];			//tabla invertida (se usa en el proceso de desencriptacion)

} S_box;

/**
 * Devuelve una tabla cargada con los valores del archivo de la ruta ingresada.
 * */
S_box *loadBoxTable(char *path);

/**
 * Muestra por pantalla la tabla ingresada, con el formato correspondiente.
 * */
void showBoxTable(int table[RADIX][RADIX]);

/**
 * Devuelve el valor correspondiente a la coordenada (value, 1er digito en hex = filas, 2do digito en hex = columan) ingresada.
 * */
int getValue(int table[RADIX][RADIX], int value);