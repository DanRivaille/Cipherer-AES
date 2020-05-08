#include <stdlib.h>

#define RADIX 16
#define MATRIX_ORDER 4

typedef struct S_box {
	int matrix[RADIX][RADIX];

} S_box;

S_box *loadBox(char *path);