#pragma once
#include "enemy.h"

class Wumpus : public Enemy
{
	bool is_alive_p;
public:
	void action(Player* p, std::ostream& ostr) { p->die(); ostr << "The Wumpus got you! "; }
	void alert(std::ostream& ostr) { ostr << "\tI smell a Wumpus!\n"; }
	void move();

	void die() { is_alive_p = false; }
	bool is_alive() { return is_alive_p; }

	Wumpus(Map* m, Player* p) : Enemy{ m,p }, is_alive_p{ true } {};
	Wumpus() : Enemy(), is_alive_p{ true } {};
};