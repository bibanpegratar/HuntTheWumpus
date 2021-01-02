#pragma once
#include "player.h"
#include "map.h"

class Enemy
{
	Room* pos = nullptr;
public:
	Enemy(Map* m);
	//virtual void action() = 0;
	virtual void action(Player* p) = 0;
	virtual void alert(std::ostream& ostr) = 0;
	const Room* get_pos() { return pos; }
	void set_pos(const Room &r) { *pos = r; }
};