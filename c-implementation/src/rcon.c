#include "rcon.h"

/**
 * Funcion que retorna una nueva tabla rcon inicializada.
 * */
Rcon *createRconTable()
{
	Rcon *new_table = (Rcon *) calloc(1, sizeof(Rcon));

	new_table->current_round = 0;
	new_table->matrix[0][0] = 1;
	
	for(int i = 1; i < CANT_ROUNDS - 2; ++i)
	{
		new_table->matrix[0][i] = new_table->matrix[0][i - 1] * 2;
	}

	new_table->matrix[0][8] = 27;
	new_table->matrix[0][9] = 54;

	return new_table;
}

/**
 * Muestra la tabla rcon ingresada en el formato ingresado, valida que la tabla ingresada no sea nula.
 * */
void showRconTable(Rcon *table)
{
	if(table != NULL)
	{
		for(int i = 0; i < MATRIX_ORDER; ++i)
		{
			for(int j = 0; j < CANT_ROUNDS; ++j)
			{
				printf("%2x ", table->matrix[i][j]);
			}

			printf("\n");
		}
	}
	else
	{
		printf("ERROR::showRconTable::tabla nula\n");
	}
}

/**
 * Funcion que se encarga realizar la operacion xor entre la columna ingresada 
 * y la columna (correspondiente al round actual del algoritmo) de la tabla rcon,
 * por ultimo incrementa el round actual de la tabla.
 * */
void functionRcon(Rcon *table, int state[])
{
	table->current_round++;
}