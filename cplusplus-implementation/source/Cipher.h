#ifndef CIPHER_H
#define CIPHER_H

#include "definitions.h"
#include <string>


#include <iostream>

using namespace std;

#define CIFRATE 1
#define DECIFRATE 2

using namespace std;

class Cipher
{
	public:
		Cipher(void);

		void setKey(unsigned char *new_key);

		string cifrate(string text, unsigned char *new_key = NULL);
		string decifrate(string text, unsigned char *new_key = NULL);

	private:
		void initialRoundCifrate(std::vector<std::vector<unsigned char>> &state);
		void standardRoundCifrate(std::vector<std::vector<unsigned char>> &state, int current_round);
		void finalRoundCifrate(std::vector<std::vector<unsigned char>> &state);

		void initialRoundDecifrate(std::vector<std::vector<unsigned char>> &state);
		void standardRoundDecifrate(std::vector<std::vector<unsigned char>> &state, int current_round);
		void finalRoundDecifrate(std::vector<std::vector<unsigned char>> &state);

		vector<vector<vector<unsigned char>>> expandBlocks(string text, int mode);
		string getText(vector<vector<vector<unsigned char>>> &states, int mode);

		void rotWord(const std::vector<unsigned char> &vec, std::vector<unsigned char> &result);
		void rotColumnLeft(std::vector<std::vector<unsigned char>> &vec, int column);
		void rotColumnRight(std::vector<std::vector<unsigned char>> &vec, int column);
		void xorBetweenVectors(const vector<unsigned char> &vec1, const vector<unsigned char> &vec2, vector<unsigned char> &vec_result);

		void addRoundKey(std::vector<std::vector<unsigned char>> &state, int current_round);
		void shiftRows(std::vector<std::vector<unsigned char>> &state);
		void subBytes(std::vector<std::vector<unsigned char>> &state);
		void mixColumns(std::vector<std::vector<unsigned char>> &state);

		void invShiftRows(std::vector<std::vector<unsigned char>> &state);
		void invSubBytes(std::vector<std::vector<unsigned char>> &state);
		void invMixColumns(std::vector<std::vector<unsigned char>> &state);

		void calculateSubKeys(void);

		std::vector<std::vector<unsigned char>> key;

};

#endif