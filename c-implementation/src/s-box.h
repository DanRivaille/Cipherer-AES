#include <stdlib.h>

#define RADIX 16
#define MATRIX_ORDER 4

typedef struct S_box {
	int matrix[RADIX][RADIX];
	int inv_matrix[RADIX][RADIX];

} S_box;

S_box *loadBoxTable(char *path);

void showBoxTable(int table[RADIX][RADIX]);

int getValue(int table[RADIX][RADIX], int value);