#include "player.h"

Player::Player(Map* m, bool rand_pos)
	:is_alive{true}
{
	if (rand_pos) pos = m->rooms(rand() % m->rooms()->size()); //spawn the player at a random position
	else pos = m->rooms(rand() % m->rooms()->size()); //spawn the player at the first room in the vector
}

void Player::move(int room_number)
{
	Room* r = pos->map->rooms_by_number(room_number);
	if (pos->number == r->number) std::cout << "Already in room " << pos->number << ".\n";
	else if (pos->link_1->number == r->number) pos = pos->link_1;
	else if (pos->link_2->number == r->number) pos = pos->link_2;
	else if (pos->link_3->number == r->number) pos = pos->link_3;
	else std::cout << "Can't go there !\n";
	//std::cout << "Player is at room " << current_room->number;
}

void Player::shoot(int rage, std::vector<Room> rooms)
{

}