#pragma once
#include "map.h"
#include "player.h"
#include "enemy.h"

struct Arrow
{
	Room* pos;
	int max_range_p;
    bool shoot(int range, std::istream& istr, std::ostream& ostr, Wumpus* wumpus);

	Arrow(int max_range, Player* p);
	Arrow(Player* p);
    Arrow() : pos{nullptr}, max_range_p{0} {};
};
