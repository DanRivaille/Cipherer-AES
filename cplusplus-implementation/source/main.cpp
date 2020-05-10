#include "Key.h"
#include "Sbox.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	Key key;
	key.loadKey(initial_key);

	Sbox sbox;
	sbox.loadTable("s-box.csv");
	sbox.showTable(TABLE);

	if(argc > 1)
	{
		int value = strtol(argv[1], NULL, RADIX);

		printf("\nTabla %2x : %2x\n", value, sbox.getValue(TABLE, value));
	}

	return 0;
}