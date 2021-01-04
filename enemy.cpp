#include "enemy.h"

Enemy::Enemy(Map* m, Player* p)
{
	Room *r = m->random_room(); //get a random room from the rooms_ p vector of Map m
	while (true)
	{
		if (r->enemy == nullptr && p->get_pos()->number != r->number) //if the room doesn't have an enemy
		{
			pos = r;
			r->enemy = this; //set this object to that room
			break;
		}
		pos = m->random_room(); //get another room
	}
}
