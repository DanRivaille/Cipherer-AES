#include "Key.h"
#include "Sbox.h"
#include "Rcon.h"
#include "Tables.h"
#include "definitions.h"

int main(int argc, char const *argv[])
{
	unsigned char initial_key[] = "\x002b\x007e\x0015\x0016\x0028\x00ae\x00d2\x00a6\x00ab\x00f7\x0015\x0088\x0009\x00cf\x004f\x003c";

	
	std::vector<std::vector<int>> v = {{0xd4, 0xe0, 0xb8, 0x1e}, {0xbf, 0xb4, 0x41, 0x27}, {0x5d, 0x52, 0x11, 0x98}, {0x30, 0xae, 0xf1, 0xe5}};

	MixColumns(v);

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			printf("%2x ", v[i][j]);
		}

		printf("\n");
	}

	/*
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

	*/


	return 0;
}

void MixColumns(std::vector<std::vector<int>> &state)
{
	int aux[4], temp[4];
	
	for (int j = 0; j < MATRIX_ORDER; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			aux[i] = state[i][j];
		}

		temp[0] = Tables::mul2[aux[0]] ^ Tables::mul3[aux[1]] ^ aux[2] ^ aux[3];
		temp[1] = aux[0] ^ Tables::mul2[aux[1]] ^ Tables::mul3[aux[2]] ^ aux[3];
		temp[2] = aux[0] ^ aux[1] ^ Tables::mul2[aux[2]] ^ Tables::mul3[aux[3]];
		temp[3] = Tables::mul3[aux[0]] ^ aux[1] ^ aux[2] ^ Tables::mul3[aux[3]];

		for (int i = 0; i < 4; i++)
		{
			state[i][j] = temp[i];
		}
	}
}