#include "Key.h"

Key::Key(void)
{
	this->current_round = 1;

	this->matrix.resize(MATRIX_ORDER * (CANT_ROUNDS + 1));
	for(int i = 0; i < MATRIX_ORDER * (CANT_ROUNDS + 1); ++i)
	{
		this->matrix[i].resize(MATRIX_ORDER);
	}
}

Key::~Key(void)
{

}

void Key::loadKey(unsigned char *initial_key)
{
	if(initial_key != NULL)
	{
		int index_initil_key = 0;

		for(int column = 0; column < MATRIX_ORDER; ++column)
		{
			for(auto &byte : this->matrix[column])
			{
				printf("%x ", initial_key[index_initil_key]);
				byte =  static_cast<int> (initial_key[index_initil_key++]);
			}
		}
	}
	else
	{
		printf("ERROR::key::initial_key null");
	}

	printf("\n");
}

void Key::show(void) const
{
	printf("\n");

	for(int i = (this->current_round - 1) * 4; i < this->current_round * 4; ++i)
	{
		for(auto byte : this->matrix[i])
		{
			printf("%2x ", byte);
		}

		printf("\n");
	}
}

/**
 * Procedimiento que calcula la siguente clave, primero realiza la rotacion rotword sobre la primera columna de la nueva clave,
 * luego realiza la funcion sbox sobre esta nueva columna, despues realiza la operacion XOR sobre esta columna con la columna 4 
 * posiciones atras, despues realiza XOR por la columna correspondiente de la tabla rcon, por ultimo se calcula las siguientes 3
 * columnas de la clave, se realiza XOR sobre la columna anterior con la columna 4 posiciones atras y el resultado se guarda en 
 * la columna actual.
 * */
void Key::calculateNextKey(Sbox &sbox, Rcon &rcon)
{
	//se realiza la rotacion rotword
	rotword();

	//se realiza la funcion sbox sobre la nueva columna
	sbox.functionSbox(this->matrix[this->current_round * MATRIX_ORDER], TABLE);

	//se realiza la operacion XOR de la columna actual con la columna 4 posiciones atras
	for(int i = 0; i < MATRIX_ORDER; ++i)
	{
		this->matrix[this->current_round * MATRIX_ORDER][i] ^= this->matrix[(this->current_round - 1) * MATRIX_ORDER][i];
	}

	//se realiza la operacion rcon
	rcon.functionRcon(this->matrix[this->current_round * MATRIX_ORDER]);

	/* Se calculan las siguientes 3 columnas, se realiza XOR sobre la columna anterior con la columna 4 posiciones atras y el resultado
	 * se guarda en la columna actual .*/
	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		for(int j = 0; j < MATRIX_ORDER; ++j)
		{
			//Columna anterior a la columna actual
			int value_column_minus_one = this->matrix[this->current_round * MATRIX_ORDER + i - 1][j];

			//Columna en 4 posiciones a la columna actual
			int value_column_minus_four = this->matrix[(this->current_round * MATRIX_ORDER) + i - 4][j];

			//Columna actual
			this->matrix[(this->current_round * MATRIX_ORDER) + i][j] = value_column_minus_one ^ value_column_minus_four;
		}
	}

	//se incrementa el contador del round actual
	this->current_round++;
}

int Key::getCurrentRound(void) const
{
	return this->current_round;
}

std::vector<int> &Key::getColumn(int column)
{
	return this->matrix[column];
}

void Key::rotword(void)
{
	int aux = this->matrix[(current_round * MATRIX_ORDER) - 1][0];

	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		this->matrix[this->current_round * MATRIX_ORDER][i - 1] = this->matrix[(this->current_round * MATRIX_ORDER) - 1][i];
	}

	this->matrix[this->current_round * MATRIX_ORDER][MATRIX_ORDER - 1] = aux;
}