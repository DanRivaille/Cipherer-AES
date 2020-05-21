#include "Cipher.h"
#include "definitions.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	std::vector<std::vector<int>> v = {{0xda, 0xe0, 0xb8, 0x1e}, {0xbf, 0xb4, 0x41, 0x27}, {0x5d, 0x52, 0x11, 0x98}, {0x30, 0xae, 0xf1, 0xe5}};
	
	Cipher cipher(initial_key);

	cipher.cifrate(NULL);



	return 0;
}

void mostrar(std::vector<std::vector<int>> &v)
{
	printf("\n");
	printf("\n");
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			printf("%2x ", v[i][j]);
		}

		printf("\n");
	}
}

void mostrarinv(std::vector<std::vector<int>> &v)
{
	printf("\n");
	printf("\n");
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			printf("%2x ", v[j][i]);
		}

		printf("\n");
	}
}