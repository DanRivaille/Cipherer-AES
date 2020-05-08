#include <stdio.h>

#include "s-box.h"

#define EXAMPLE 0xBA

int main(int argv, char **args) 
{
	S_box *s_box = loadBoxTable("s-box.csv");

	if(s_box != NULL)
	{
		printf("\nElemento %x = %x\n", EXAMPLE, getValue(s_box->matrix, EXAMPLE));

		printf("Se cargo con exito la tabla s_box\n");

		free(s_box);
	}
	else
	{
		printf("Hubo un error en la carga de la tabla s-box");
	}

	return 0;
}