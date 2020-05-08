#include "s-box.h"

#define MAX_LINE 50

/**
 * Carga la tabla s-box del archivo en la ruta ingresada, si hubo un error al abrir el archivo
 * muestra una amenaza y termina la funcion, sino lee todos los valores del archivo y los 
 * guarda en la tabla original y la tabla invertida, por ultimo cierra el archivo.
 * */
S_box *loadBoxTable(char *path)
{
	FILE *file = fopen(path, "r");
	S_box *new_table = NULL;

	if(file != NULL)
	{
		new_table = (S_box *) malloc(sizeof(S_box));
		char line[MAX_LINE];
		char *token;

		for(int rows = 0; rows < RADIX; ++rows)
		{
			fscanf(file, "%s", line);
			token = strtok(line, ",\n");

			for(int columns = 0; columns < RADIX; ++columns)
			{
				int value = strtol(token, NULL, RADIX);

				//se carga el valor en la matriz original
				new_table->matrix[rows][columns] = value;

				//se carga el valor en la matriz inversa
				new_table->inv_matrix[value / 16][value % 16] = (rows * 16) + columns;

				token = strtok(NULL, ",\n");
			}
		}

		fclose(file);
	}
	else
	{
		printf("No se pudo abrir el archivo correctamente\n");
	}

	return new_table;
}

/**
 * Muestra la tabla ingresada con el formato correspondiente, si la tabla es nula imprime una advertencia y termina la funcion.
 * */
void showBoxTable(int table[RADIX][RADIX])
{
	if(table != NULL)
	{
		printf("  ");
		for(int i = 0; i < RADIX; ++i)
		{
			printf(" %2x", i);
		}

		printf("\n");

		for(int i = 0; i < RADIX; ++i)
		{
			printf("%2x ", i);

			for(int j = 0; j < RADIX; ++j)
			{
				printf("%2x ", table[i][j]);
			}

			printf("\n");
		}	
	}
	else
	{
		printf("TABLA NULA::showBoxTable\n");
	}	
}

/**
 * Funcion que devuelve el valor correspondiente a las coordenadas de "value", el primer digito
 * de su representacion en hexadecimal corresponde a la fila, y el segundo digito de su representacion
 * en hexadecimal corresponde a la columna, si estos valores estan en el rango valido devuelve el 
 * valor correspondiente, sino imprime una advertencia y devuelve -1.
 * */
int getValue(int table[RADIX][RADIX], int value)
{
	int value_table = -1;
	int rows = value / 16;
	int columns = value % 16;

	if((rows >= RADIX) || (columns >= RADIX))
		printf("EROR::getValue::valor ingresado no valido %i\n", value);

	else
		value_table = table[rows][columns];

	return value_table;
}