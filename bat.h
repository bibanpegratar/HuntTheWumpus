#pragma once
#include "enemy.h"

class Bat : public Enemy
{
    int action_chance_p;
public:
	void action(Player* p, std::ostream& ostr);
    void alert(std::ostream& ostr) { ostr << "\tA bat is nearby.\n"; }
    void move();

    Bat(Map* m, Player* p, int action_chance);
    Bat(Map* m, Player* p);
	Bat() : Enemy() {};
};