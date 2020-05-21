#ifndef KEY_H
#define KEY_H

#include "definitions.h"

class Key
{
	public:
		const static int KEY_LENGTH = 16;

		Key(void);
		~Key(void);

		void rotword(void);

		void loadKey(unsigned char *new_key);
		void show(void) const;

		//void calculateNextKey(Sbox &sbox, Rcon &rcon);

		std::vector<int> &getColumn(int column);
		int getCurrentRound(void) const;
	
	private:
		std::vector<std::vector<int>> matrix;
		int current_round;

};

#endif