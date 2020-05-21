#ifndef CIPHER_H
#define CIPHER_H

#include "definitions.h"

class Cipher
{
	public:
		Cipher(unsigned char *new_key);
		~Cipher(void);

		void setKey(unsigned char *new_key);

		unsigned char *cifrate(unsigned char *text);
		unsigned char *decifrate(unsigned char *text);

	private:
		void initialRound(void);
		void standardRound(void);
		void finalRound(void);

		void expandText(void);
		void rotWord(void);
		void xorBetweenVectors(void);

		void addRoundKey(std::vector<std::vector<unsigned char>> &state);
		void shiftRows(std::vector<std::vector<unsigned char>> &state);
		void subBytes(std::vector<std::vector<unsigned char>> &state);
		void mixColumns(std::vector<std::vector<unsigned char>> &state);

		void invAddRoundKey(std::vector<std::vector<unsigned char>> &state);
		void invShiftRows(std::vector<std::vector<unsigned char>> &state);
		void invSubBytes(std::vector<std::vector<unsigned char>> &state);
		void invMixColumns(std::vector<std::vector<unsigned char>> &state);

		std::vector<std::vector<unsigned char>> key;

};

#endif