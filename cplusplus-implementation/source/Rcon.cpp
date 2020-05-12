#include "Rcon.h"

Rcon::Rcon(void)
{
	this->current_round = 0;
	this->table.resize(CANT_ROUNDS);

	this->table[0] = 1;
	
	for(int i = 1; i < CANT_ROUNDS - 2; ++i)
	{
		this->table[i] = this->table[i - 1] * 2;
	}

	this->table[8] = 27;
	this->table[9] = 54;
}
	
Rcon::~Rcon(void)
{

}

void Rcon::functionRcon(std::vector<int> &column)
{
	column[0] ^= this->table[this->current_round];

	this->current_round++;
}

void Rcon::showTable() const
{
	printf("\n");

	for(auto byte : this->table)
	{
		printf("%2x ", byte);
	}

	printf("\n");
}