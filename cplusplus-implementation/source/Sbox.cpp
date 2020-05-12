#include "Sbox.h"

#define MAX_LINE 50

Sbox::Sbox()
{
	this->table.resize(RADIX);
	this->inv_table.resize(RADIX);
	for (int i = 0; i < RADIX; ++i)
	{
		this->table[i].resize(RADIX);
		this->inv_table[i].resize(RADIX);
	}
}

Sbox::~Sbox()
{

}

/**
 * Carga la tabla s-box del archivo en la ruta ingresada, si hubo un error al abrir el archivo
 * muestra una amenaza y termina la funcion, sino lee todos los valores del archivo y los 
 * guarda en la tabla original y la tabla invertida, por ultimo cierra el archivo.
 * */
void Sbox::loadTable(const std::string path)
{
	FILE *file = fopen(path.c_str(), "r");	
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
			this->table[rows][columns] = value;

			//se carga el valor en la matriz inversa
			this->inv_table[value / 16][value % 16] = (rows * 16) + columns;

			token = strtok(NULL, ",\n");
		}
	}
}

/**
 * Muestra la tabla ingresada con el formato correspondiente, si la tabla es nula imprime una advertencia y termina la funcion.
 * */
void Sbox::showTable(IdTable id_table) const 
{
	printf("\n  ");
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
			if(id_table == TABLE)
				printf("%2x ", this->table[i][j]);
			else
				printf("%2x ", this->inv_table[i][j]);
		}

		printf("\n");
	}	
}

void Sbox::functionSbox(std::vector<int> &column, IdTable id_table)
{
	for(auto &value : column)
	{
		value = getValue(id_table, value);
	}
}

/**
 * Funcion que devuelve el valor correspondiente a las coordenadas de "value", el primer digito
 * de su representacion en hexadecimal corresponde a la fila, y el segundo digito de su representacion
 * en hexadecimal corresponde a la columna, si estos valores estan en el rango valido devuelve el 
 * valor correspondiente, sino imprime una advertencia y devuelve -1.
 * */
int Sbox::getValue(IdTable id_table, int value)
{
	int value_table = -1;
	int rows = value / 16;
	int columns = value % 16;

	if((rows >= RADIX) || (columns >= RADIX))
		printf("EROR::getValue::valor ingresado no valido %i\n", value);

	else
		if(id_table == TABLE)
			value_table = this->table[rows][columns];
		else
			value_table = this->inv_table[rows][columns];

	return value_table;
}