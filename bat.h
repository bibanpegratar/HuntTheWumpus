#pragma once
#include "enemy.h"
#include "map.h"

//Build an entity (or enemy) class of some type
//Hold a pointer to that inside Room
//Make child classes for Bats, Pits and Wumpus
//No need to iterate over some vectors, just check if the room's pointer is null or not, and call a method if it isn't
class Bat : public Enemy
{
public:
	void action(Player* p);
	void alert(std::ostream& ostr);
	Bat(Map* m) : Enemy{ m } {};
	//void move_player(Player& p);
};