#pragma once
#include "arrow.h"

class Player
{
private:
	Room* pos;
	bool is_alive_p;
	std::vector <Arrow> *arrows_p;

public:
	Player(Map* m, bool rand_pos, int arrows); // instantiate a player at a random location with "a" arrows
	~Player() { delete arrows_p; }

	Room* get_pos() { return pos; }
	void set_pos(Room *r) { pos = r; }

	const std::vector<Arrow>* get_arrows() const { return arrows_p; }

	bool is_alive() { return is_alive_p; }

	void move(int room_number); //move to an adjacent room
	void shoot(int range, std::istream& istr, Wumpus* wumpus);
	void die() { is_alive_p = false; }
};
