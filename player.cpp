#include "player.h"

Player::Player(Map* m, bool rand_pos)
	:is_alive{ true }
{
	if (rand_pos) pos = m->random_room(); //spawn the player at a random position
	else pos = m->rooms(0); //spawn the player at the first room in the vector
}

void Player::move(int room_number)
{
	int n = pos->map->rooms_by_number(room_number)->number;
	if (pos->number == n) std::cout << "Already in room " << pos->number << ".\n";
	else if (pos->link_1->number == n) pos = pos->link_1;
	else if (pos->link_2->number == n) pos = pos->link_2;
	else if (pos->link_3->number == n) pos = pos->link_3;
	else std::cout << "Can't go there !\n";
	//std::cout << "Player is at room " << current_room->number;
}

//void Player::shoot(int rage, std::vector<Room> rooms)
//{

//}
