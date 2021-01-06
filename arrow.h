#pragma once
#include "wumpus.h"

struct Arrow
{
	Room* pos;
	int max_range_p;
	void shoot(int range, std::istream& istr, Wumpus* wumpus);

	Arrow(int max_range, Player* p);
	Arrow(Player* p);
};