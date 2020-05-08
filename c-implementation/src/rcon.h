#include "s-box.h"

#define CANT_ROUNDS 10

/**
 * Estructura principal de la tabla rcon
 * */
typedef struct Rcon {
	int matrix[MATRIX_ORDER][CANT_ROUNDS];
	int current_round;

} Rcon;

/**
 * Devuelve una tabla rcon recien creada.
 * */
Rcon *createRconTable();

/**
 * Muestra la tabla rcon ingresada con el formato correspondiente.
 */
void showRconTable(Rcon *table);

/**
 * Funcion que se encarga realizar la operacion xor entre la columna ingresada 
 * y la columna correspondiente de la tabla rcon.
 * */
void functionRcon(Rcon *table, int state[]);