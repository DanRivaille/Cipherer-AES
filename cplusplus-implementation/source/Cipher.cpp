#include "Tables.h"

#include "Cipher.h"

using namespace std;

void show(std::vector<std::vector<unsigned char>> v)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			printf("%2x ", v[i][j]);
		}
		printf("\n");
	}
}

Cipher::Cipher(unsigned char *new_key = NULL)
{
	this->key.resize(MATRIX_ORDER * (CANT_ROUNDS + 1));
	for(int i = 0; i < MATRIX_ORDER * (CANT_ROUNDS + 1); ++i)
	{
		this->key[i].resize(MATRIX_ORDER);
	}

	if(new_key != NULL)
		setKey(new_key);
}

Cipher::~Cipher(void)
{

}

void Cipher::setKey(unsigned char *new_key)
{
	if(new_key != NULL)
	{
		for(int column = 0; column < MATRIX_ORDER; ++column)
		{
			for(auto &byte : this->key[column])
			{
				byte =  static_cast<int> (*new_key);

				new_key++;
			}
		}
	}
	else
	{
		printf("ERROR::setKey::initial_key null");
	}

	//calcular todas las subclaves
}

unsigned char *Cipher::cifrate(unsigned char *text)
{
	std::vector<std::vector<unsigned char>> v = {{0xda, 0xbf, 0x5d, 0x30}, {0xe0, 0xb4, 0x52, 0xae}, {0xb8, 0x41, 0x11, 0xf1}, {0x1e, 0x27, 0x98, 0xe5}};
	std::vector<std::vector<unsigned char>> v2 = {{0x49, 0xdb, 0x87, 0x3b}, {0x45, 0x39, 0x53, 0x89}, {0x7f, 0x02, 0xd2, 0xf1}, {0x77, 0xde, 0x96, 0x1a}};

	std::vector<std::vector<unsigned char>> ad = {{0x32, 0x43, 0xf6, 0xa8}, {0x88, 0x5a, 0x30, 0x8d}, {0x31, 0x31, 0x98, 0xa2}, {0xe0, 0x37, 0x07, 0x34}};	

	std::vector<std::vector<unsigned char>> sub = {{0x19, 0x3d, 0xe3, 0xbe}, {0xa0, 0xf4, 0xe2, 0x2b}, {0x9a, 0xc6, 0x8d, 0x2a}, {0xe9, 0xf8, 0x48, 0x08}};

	subBytes(sub);

	show(sub);

	//se crean los bloques de 128 bits que se cifraran
	expandText();

	initialRound();

	for(int round = 0; round < CANT_ROUNDS; ++round)
	{
		standardRound();
	}

	finalRound();
}

unsigned char *Cipher::decifrate(unsigned char *text)
{

}

void Cipher::initialRound(void)
{

}

void Cipher::standardRound(void)
{

}

void Cipher::finalRound(void)
{

}

void Cipher::expandText(void)
{

}

void Cipher::rotWord(void)
{

}

void Cipher::xorBetweenVectors(const vector<unsigned char> &vec1, const vector<unsigned char> &vec2, vector<unsigned char> &vec_result)
{
	for(int i = 0; i < MATRIX_ORDER; ++i)
	{
		vec_result[i] = vec1[i] ^ vec2[i];
	}
}

void Cipher::addRoundKey(std::vector<std::vector<unsigned char>> &state)
{
	std::vector<std::vector<unsigned char>> qye = {{0x2b, 0x7e, 0x15, 0x16}, {0x28, 0xae, 0xd2, 0xa6}, {0xab, 0xf7, 0x15, 0x88}, {0x09, 0xcf, 0x4f, 0x3c}};	

	for(int i = 0; i < MATRIX_ORDER; ++i)
	{
		xorBetweenVectors(state[i], qye[i], state[i]);
	}
}

void Cipher::shiftRows(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::subBytes(std::vector<std::vector<unsigned char>> &state)
{
	for(auto &column : state)
	{
		for(auto &byte : column)
		{
			byte = Tables::sbox[byte];
		}
	}
}

void Cipher::mixColumns(std::vector<std::vector<unsigned char>> &state)
{
	std::vector<unsigned char> aux(MATRIX_ORDER);
	std::vector<unsigned char> temp(MATRIX_ORDER);

	for (int j = 0; j < MATRIX_ORDER; j++)
	{
		aux = state[j];

		temp[0] = Tables::mul2[aux[0]] ^ Tables::mul3[aux[1]] ^ aux[2] ^ aux[3];
		temp[1] = aux[0] ^ Tables::mul2[aux[1]] ^ Tables::mul3[aux[2]] ^ aux[3];
		temp[2] = aux[0] ^ aux[1] ^ Tables::mul2[aux[2]] ^ Tables::mul3[aux[3]];
		temp[3] = Tables::mul3[aux[0]] ^ aux[1] ^ aux[2] ^ Tables::mul2[aux[3]];

		state[j] = temp;
	}
}

void Cipher::invAddRoundKey(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::invShiftRows(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::invSubBytes(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::invMixColumns(std::vector<std::vector<unsigned char>> &state)
{
	std::vector<unsigned char> aux(MATRIX_ORDER);
	std::vector<unsigned char> temp(MATRIX_ORDER);

	for (int j = 0; j < MATRIX_ORDER; j++)
	{
		aux = state[j];

		temp[0] = Tables::mul14[aux[0]] ^ Tables::mul11[aux[1]] ^ Tables::mul13[aux[2]] ^ Tables::mul9[aux[3]];
		temp[1] = Tables::mul9[aux[0]] ^ Tables::mul14[aux[1]] ^ Tables::mul11[aux[2]] ^Tables::mul13[aux[3]];
		temp[2] = Tables::mul13[aux[0]] ^ Tables::mul9[aux[1]] ^ Tables::mul14[aux[2]] ^ Tables::mul11[aux[3]];
		temp[3] = Tables::mul11[aux[0]] ^ Tables::mul13[aux[1]] ^ Tables::mul9[aux[2]] ^ Tables::mul14[aux[3]];

		state[j] = temp;
	}
}