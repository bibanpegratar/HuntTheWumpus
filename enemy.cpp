#include "enemy.h"

Enemy::Enemy(Map* m, Player* p)
{
	Room *r = m->random_room(); //get a random room from the rooms_ p vector of Map m
	while (true)
	{
		//check for room already having enemy or a player being on that position
		if (r->enemy == nullptr && p->get_pos()->number != r->number)
		{
			pos = r;
			r->enemy = this; //set this object to that room
			break;
		}
		r = m->random_room(); //get another room
	}
}
