#include "Cipher.h"
#include "definitions.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";	
	
	Cipher cipher(initial_key);

	cipher.cifrate("Hola como estas? yo bien y tu?je");

	return 0;
}