#include <stdio.h>

#include "rcon.h"
#include "s-box.h"
#include "key.h"

#define EXAMPLE 0xBA

int main(int argv, char **args) 
{
	Key *key = createKey("\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c");

	Rcon *rcon = createRconTable();

	//showRconTable(rcon);
	showKey(key);

	free(rcon);
	free(key);

	return 0;
}