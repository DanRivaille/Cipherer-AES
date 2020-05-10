#include "Key.h"

Key::Key(void)
{
	this->matrix.resize(MATRIX_ORDER * CANT_ROUNDS);
	for(int i = 0; i < MATRIX_ORDER * CANT_ROUNDS; ++i)
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

	for(auto column : this->matrix)
	{
		for(auto byte : column)
		{
			printf("%2x ", byte);
		}

		printf("\n");
	}
}