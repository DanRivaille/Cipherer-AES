#include <stdio.h>

#include "rcon.h"

#define EXAMPLE 0xBA

int main(int argv, char **args) 
{
	Rcon *rcon = createRconTable();

	showRconTable(rcon);

	free(rcon);

	return 0;
}