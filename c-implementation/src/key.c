#include "key.h"

Key *createKey(unsigned char *initial_key)
{
	Key *new_key = NULL;

	if(initial_key != NULL)
	{
		new_key = (Key *) malloc(sizeof(Key));

		int index_initil_key = 0;

		for(int j = 0; j < MATRIX_ORDER; ++j)
		{
			for(int i = 0; i < MATRIX_ORDER; ++i)
			{
				printf("%x ", initial_key[index_initil_key]);
				new_key->matrix[i][j]= initial_key[index_initil_key++];
			}	
		}
	}
	else
	{
		printf("ERROR::key::initial_key null\n");
	}

	return new_key;
}

void showKey(Key *key)
{
	printf("\n");

	for (int i = 0; i < MATRIX_ORDER; ++i)
	{
		for (int j = 0; j < MATRIX_ORDER * CANT_ROUNDS; ++j)
		{
			printf("%2x ", key->matrix[i][j]);
		}

		printf("\n");
	}
}