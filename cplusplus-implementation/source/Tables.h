#ifndef TABLES_H
#define TABLES_H

class Tables
{
	public:
		static unsigned char sbox[256];
		static unsigned char inv_sbox[256];
		static unsigned char mul2[256];
		static unsigned char mul3[256];
		static unsigned char mul9[256];
		static unsigned char mul11[256];
		static unsigned char mul13[256];
		static unsigned char mul14[256];
		static unsigned char rcon[10];
};

#endif