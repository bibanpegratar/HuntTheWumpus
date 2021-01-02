#pragma once
#include "map.h"

class Player
{
	Room* pos = nullptr;
	bool is_alive;

public:
	void shoot(int range, std::vector<Room> rooms);
	void move(int room_number); //move to an adjacent room
	void die() { is_alive = false; }

	//const std::vector<Arrow>& get_arrows() { return arrows; }
	//int set_arrows(int a) { arrows = a; }

	const Room* get_pos() { return pos; }
	void set_pos(Room *r) { pos = r; }

	Player(Map* m, bool rand_pos); // instantiate a player at a random location with "a" arrows
};
