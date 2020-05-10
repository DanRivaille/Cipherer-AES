#ifndef KEY_H
#define KEY_H

#include "s-box.h"
#include "rcon.h"

typedef struct Key {
	int matrix[MATRIX_ORDER][MATRIX_ORDER * CANT_ROUNDS];

} Key;

Key *createKey(unsigned char *initial_key);

void showKey(Key *key);

#endif