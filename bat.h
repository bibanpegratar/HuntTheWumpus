#pragma once
#include "enemy.h"
#include "map.h"


class Bat : public Enemy
{
public:
	void action(Player* p, std::ostream& ostr);
	void alert(std::ostream& ostr) { ostr << "A bat is nearby.\n"; }
	Bat(Map* m, Player* p) : Enemy{ m, p } {};
	Bat() : Enemy() {};
};