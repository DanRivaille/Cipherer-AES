#include "Key.h"
#include "Sbox.h"
#include "Rcon.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	Key key;
	key.loadKey(initial_key);

	Sbox sbox;
	sbox.loadTable("s-box.csv");

	Rcon rcon;
	//rcon.showTable();
	//rcon.functionRcon(key.getColumn(0));

	key.show();
	
	for(int i = 0; i < 10; ++i)
	{
		key.calculateNextKey(sbox, rcon);

		key.show();
	}




	return 0;
}