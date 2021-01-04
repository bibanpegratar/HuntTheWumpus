#pragma once
#include "map.h"

class Player
{
	Room* pos;
	bool is_alive;

public:
	Player(Map* m, bool rand_pos); // instantiate a player at a random location with "a" arrows

	const Room* get_pos() { return pos; }
	void set_pos(Room *r) { pos = r; }

	void move(int room_number); //move to an adjacent room
	//void die() { is_alive = false; }
};
