#ifndef CIPHER_H
#define CIPHER_H

#include "definitions.h"

using namespace std;

class Cipher
{
	public:
		Cipher(unsigned char *new_key);
		~Cipher(void);

		void setKey(unsigned char *new_key);

		unsigned char *cifrate(unsigned char *text);
		unsigned char *decifrate(unsigned char *text);

	private:
		void initialRoundCifrate(std::vector<std::vector<unsigned char>> &state);
		void standardRoundCifrate(void);
		void finalRoundCifrate(void);

		void initialRoundDecifrate(void);
		void standardRoundDecifrate(void);
		void finalRoundDecifrate(void);

		void expandText(void);
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