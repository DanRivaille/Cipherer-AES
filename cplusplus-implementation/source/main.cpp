#include "Cipher.h"
#include "definitions.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	unsigned char key[] = "\x0063\x006C\x0061\x0076\x0065\x0020\x0070\x0072\x0069\x006E\x0063\x0069\x0070\x0061\x006C\x0020";

	
	
	Cipher cipher(initial_key);

	cipher.cifrate(NULL);



	return 0;
}