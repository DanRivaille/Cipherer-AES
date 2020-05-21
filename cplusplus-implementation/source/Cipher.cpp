#include "Tables.h"

#include "Cipher.h"

using namespace std;

void show(std::vector<std::vector<unsigned char>> v)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			printf("%2x ", v[j][i]);
		}
		printf("\n");
	}
	printf("\n");
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

		calculateSubKeys();
	}
	else
	{
		printf("ERROR::setKey::initial_key null");
	}
}

unsigned char *Cipher::cifrate(unsigned char *text)
{
	//se crean los bloques de 128 bits que se cifraran
	expandText();

	std::vector<std::vector<unsigned char>> state = {{0x32, 0x43, 0xf6, 0xa8}, {0x88, 0x5a, 0x30, 0x8d}, {0x31, 0x31, 0x98, 0xa2}, {0xe0, 0x37, 0x07, 0x34}};

	show(state);

	initialRoundCifrate(state);

	for(int round = 1; round < CANT_ROUNDS; ++round)
	{
		standardRoundCifrate(state, round);
	}

	finalRoundCifrate(state);

	decifrate(state);
}

unsigned char *Cipher::decifrate(std::vector<std::vector<unsigned char>> &state)
{
	initialRoundDecifrate(state);

	for(int round = CANT_ROUNDS - 1; round > 0; --round)
	{
		standardRoundDecifrate(state, round);
	}

	finalRoundDecifrate(state);

	show(state);
}

/** ----------------------------- Rondas del modo de cifrado ----------------------------- **/
void Cipher::initialRoundCifrate(std::vector<std::vector<unsigned char>> &state)
{
	addRoundKey(state, 0);
}

void Cipher::standardRoundCifrate(std::vector<std::vector<unsigned char>> &state, int current_round)
{
	subBytes(state);

	shiftRows(state);

	mixColumns(state);

	addRoundKey(state, current_round);
}

void Cipher::finalRoundCifrate(std::vector<std::vector<unsigned char>> &state)
{
	subBytes(state);

	shiftRows(state);

	addRoundKey(state, 10);
}

/** ----------------------------- Rondas del modo de decifrado ----------------------------- **/
void Cipher::initialRoundDecifrate(std::vector<std::vector<unsigned char>> &state)
{
	addRoundKey(state, 10);

	invShiftRows(state);

	invSubBytes(state);
}

void Cipher::standardRoundDecifrate(std::vector<std::vector<unsigned char>> &state, int current_round)
{
	addRoundKey(state, current_round);

	invMixColumns(state);

	invShiftRows(state);

	invSubBytes(state);
}

void Cipher::finalRoundDecifrate(std::vector<std::vector<unsigned char>> &state)
{
	addRoundKey(state, 0);
}

/** --------------------------------------- Funciones auxiliares --------------------------------------- **/

/**
 * Expande el texto de forma que se armen los bloques de 128 bits para poder cifrar cada uno de ellos
 */
void Cipher::expandText(void)
{

}

/**
 * Calcula las subclaves a partir de la clave estableceida previamente.
 * */
void Cipher::calculateSubKeys(void)
{
	//Recorre columna por columna, empezando por la primera columna de la primera subclave
	for(int current_key = 1; current_key <= CANT_ROUNDS; ++current_key)
	{
		//Se aplica rotWord a la columna de la subclave anterior y se guarda en la primera columna de la sublave actual
		rotWord(this->key[(current_key * MATRIX_ORDER) - 1], this->key[current_key * MATRIX_ORDER]);

		//Se recorre la columna actual, osea la primera de la subclave actual
		for(int j = 0; j < MATRIX_ORDER; ++j)
		{
			//Se aplica subBytes sobre cada byte de la columna y se guarda en la misma posicion
			this->key[current_key * MATRIX_ORDER][j] = Tables::sbox[this->key[current_key * MATRIX_ORDER][j]];

			//Se aplica un xor con el byte correspondiente de la primera columna de la sublave anterior
			this->key[current_key * MATRIX_ORDER][j] ^= this->key[(current_key - 1) * MATRIX_ORDER][j];
		}

		//Se aplica un xor con el primer byte de la columna, con el byte correspondiente de la tabla rcon
		this->key[current_key * MATRIX_ORDER][0] ^= Tables::rcon[current_key - 1];

		//Se calcula las 3 columnas restantes de la subclave actual
		for(int j = 1; j < MATRIX_ORDER; ++j)
		{
			//Se aplica un xor byte a byte de la columna anterior, con la columna 4 posiciones atras y se guarda en la columna actual
			xorBetweenVectors(
				this->key[(current_key * MATRIX_ORDER) + j - 1], 
				this->key[((current_key - 1) * MATRIX_ORDER) + j], 
				this->key[(current_key * MATRIX_ORDER) + j]);
		}
	}
}

/** Realiza la funcion rotWord en el calculo de las subclaves */
void Cipher::rotWord(const std::vector<unsigned char> &vec, std::vector<unsigned char> &result)
{
	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		result[i - 1] = vec[i];
	}

	result[MATRIX_ORDER - 1] = vec[0];
}

/**
 * Rota la columna especificada con el parametro "column" hacia la izquierda de la matriz ingresada
 * */
void Cipher::rotColumnLeft(std::vector<std::vector<unsigned char>> &vec, int column)
{
	unsigned char aux = vec[0][column];

	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		vec[i - 1][column] = vec[i][column];
	}

	vec[MATRIX_ORDER - 1][column] = aux;
}

/**
 * Rota la columna especificada con el parametro "column" hacia la derecha de la matriz ingresada
 * */
void Cipher::rotColumnRight(std::vector<std::vector<unsigned char>> &vec, int column)
{
	unsigned char aux = vec[MATRIX_ORDER - 1][column];

	for(int i = MATRIX_ORDER - 1; i > 0; --i)
	{
		vec[i][column] = vec[i - 1][column];
	}

	vec[0][column] = aux;
}

/**
 * Realiza un XOR byte a byte del vector vec1 con el vector vec2 y el resultado de cada operacion lo guarda en vec_result
 * */
void Cipher::xorBetweenVectors(const vector<unsigned char> &vec1, const vector<unsigned char> &vec2, vector<unsigned char> &vec_result)
{
	for(int i = 0; i < MATRIX_ORDER; ++i)
	{
		vec_result[i] = vec1[i] ^ vec2[i];
	}
}


/** ---------------------------------- Funciones principales del algoritmo de cifreado -------------------------------------- **/

void Cipher::addRoundKey(std::vector<std::vector<unsigned char>> &state, int current_round)
{
	for(int i = 0; i < MATRIX_ORDER; ++i)
	{
		xorBetweenVectors(state[i], this->key[(current_round * MATRIX_ORDER) + i], state[i]);
	}
}

void Cipher::shiftRows(std::vector<std::vector<unsigned char>> &state)
{
	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			rotColumnLeft(state, i);
		}
	}
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

/** ---------------------------------- Funciones principales del algoritmo de decifreado -------------------------------------- **/

void Cipher::invShiftRows(std::vector<std::vector<unsigned char>> &state)
{
	for(int i = 1; i < MATRIX_ORDER; ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			rotColumnRight(state, i);
		}
	}
}

void Cipher::invSubBytes(std::vector<std::vector<unsigned char>> &state)
{
	for(auto &column : state)
	{
		for(auto &byte : column)
		{
			byte = Tables::inv_sbox[byte];
		}
	}
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