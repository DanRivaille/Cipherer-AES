#include "Rcon.h"

Rcon::Rcon(void)
{
	this->current_round = 0;
	this->table.resize(CANT_ROUNDS);
	for(auto &columns : this->table)
	{
		columns.resize(MATRIX_ORDER);
	}

	this->table[0][0] = 1;
	
	for(int i = 1; i < CANT_ROUNDS - 2; ++i)
	{
		this->table[i][0] = this->table[i - 1][0] * 2;
	}

	this->table[8][0] = 27;
	this->table[9][0] = 54;
}
	
Rcon::~Rcon(void)
{

}

void Rcon::function(std::vector<int> &column)
{
	for(int i = 0; i < column.size(); ++i)
	{
		printf("%x %x\n", column[i], this->table[this->current_round][i]);
	}

	this->current_round++;
}

void Rcon::showTable() const
{
	for(auto columns : this->table)
	{
		printf("\n");
		for(auto byte : columns)
		{
			printf("%2x ", byte);
		}
	}
	printf("\n");
}