#include "player.h"

Player::Player(Map* m, bool rand_pos, int arrows)
	:is_alive_p{ true }, arrows_p { new std::vector<Arrow> ( arrows, Arrow{this} )}
{
	if (rand_pos) pos = m->random_room(); //spawn the player at a random position
	else pos = m->rooms(0); //spawn the player at the first room in the vector
}

void Player::move(int room_number)
{
	Room* r = pos->map->rooms_by_number(room_number);
	if (r == nullptr)
	{
		std::cout << "Invalid room.\n";
		return;
	}
	if (pos->number == r->number) std::cout << "Already in room " << pos->number << ".\n";
	else if (pos->link_1->number == r->number) pos = pos->link_1;
	else if (pos->link_2->number == r->number) pos = pos->link_2;
	else if (pos->link_3->number == r->number) pos = pos->link_3;
	else std::cout << "Can't go there !\n";
}

void Player::shoot(int range, std::istream& istr, Wumpus* wumpus)
{
	arrows_p->at(arrows_p->size()).shoot(range, istr, wumpus);
	arrows_p->pop_back();
}


