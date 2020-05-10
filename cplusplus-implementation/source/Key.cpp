#include "Key.h"

Key::Key(void)
{
	this->current_round = 1;

	this->matrix.resize(MATRIX_ORDER * CANT_ROUNDS);
	for(int i = 0; i < MATRIX_ORDER * CANT_ROUNDS; ++i)
	{
		this->matrix[i].resize(MATRIX_ORDER);
	}
}

Key::~Key(void)
{

}

void Key::rotword(void)
{
	int aux = this->matrix[(current_round * MATRIX_ORDER) - 1][0];

	for(int i = 1; i < this->matrix[(this->current_round * MATRIX_ORDER) - 1].size(); ++i)
	{
		this->matrix[this->current_round * MATRIX_ORDER][i - 1] = this->matrix[(this->current_round * MATRIX_ORDER) - 1][i];
	}

	this->matrix[this->current_round * MATRIX_ORDER][MATRIX_ORDER - 1] = aux;
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

std::vector<int> &Key::getColumn(int column)
{
	return this->matrix[column];
}

void Key::show(void) const
{
	printf("\n");

	for(auto column : this->matrix)
	{
		for(auto byte : column)
		{
			printf("%2x ", byte);
		}

		printf("\n");
	}
}