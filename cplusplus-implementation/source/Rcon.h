#ifndef RCON_H
#define RCON_H

#include "definitions.h"

class Rcon
{
	public:
		Rcon(void);
		~Rcon(void);

		void function(std::vector<int> &column);
		void showTable() const;
	
	private:
		std::vector<std::vector<int>> table;
		int current_round;
};

#endif