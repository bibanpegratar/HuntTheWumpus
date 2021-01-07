#pragma once
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "arrow.h"

class Pit : public Enemy
{
public:
	void action(Player* p, std::ostream& ostr) { p->die(); ostr << "\tYou fell into a pit! "; };
	void alert(std::ostream& ostr) { ostr << "\tI feel a draft.\n"; }

	Pit(Map* m, Player* p) : Enemy{ m,p } {};
	Pit() : Enemy() {};
};
