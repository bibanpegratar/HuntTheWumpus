#pragma once
#include "player.h"

class Enemy
{
protected:
    Room* pos;

public:
	Enemy(Map* m, Player* p);
	Enemy() : pos{ nullptr } {}; //default constructor for usage with std::vector
    virtual ~Enemy() {}

	virtual void action(Player* p, std::ostream& ostr) = 0;
	virtual void alert(std::ostream& ostr) = 0;

	const Room* get_pos() { return pos; }
	void set_pos(const Room &r) { *pos = r; }

};
