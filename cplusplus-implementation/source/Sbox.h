#ifndef S_BOX_H
#define S_BOX_H

#include "definitions.h"

enum IdTable {
	TABLE, INV_TABLE	
};

class Sbox
{
	public:
		Sbox();
		~Sbox();

		void loadTable(const std::string path);
		void showTable(IdTable id_table) const;

		void functionSbox(std::vector<int> &column, IdTable id_table);
		int getValue(IdTable id_table, int value);
	
	private:
		std::vector<std::vector<int>> table;
		std::vector<std::vector<int>> inv_table;

};

#endif