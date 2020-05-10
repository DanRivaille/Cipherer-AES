#include "Key.h"
#include "Sbox.h"
#include "Rcon.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	Key key;
	key.loadKey(initial_key);

	Sbox sbox;

	Rcon rcon;
	rcon.showTable();
	rcon.function(key.getColumn(0));

	return 0;
}