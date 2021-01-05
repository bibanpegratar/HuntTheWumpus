#pragma once
#include "enemy.h"

class Wumpus : public Enemy
{
public:
	void action(Player* p, std::ostream& ostr) { p->die(); ostr << "The Wumpus got you! "; }
	void alert(std::ostream& ostr) { ostr << "\tI smell a Wumpus!\n"; }
	void move();

	Wumpus(Map* m, Player* p) : Enemy{ m,p } {};
	Wumpus() : Enemy() {};
};