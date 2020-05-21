#include "Tables.h"

#include "Cipher.h"

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
	//mixColumns(v);

	//se crean los bloques de 128 bits que se cifraran
	scaleText();

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

void Cipher::scaleText(void)
{

}

void Cipher::rotWord(void)
{

}

void Cipher::xorBetweenVectors(void)
{

}

void Cipher::addRoundKey(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::shiftRows(std::vector<std::vector<unsigned char>> &state)
{

}

void Cipher::subBytes(std::vector<std::vector<unsigned char>> &state)
{

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

		printf("%x %x %x %x\n", temp[0], temp[1], temp[2], temp[3]);

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