#include "enemy.h"

Enemy::Enemy(Map* m)
{
	Room* r = m->rooms(rand() % m->rooms()->size());
	while (true)
	{
		if (r->enemy == nullptr)
		{
			pos = r;
			pos->enemy = this;
			r->enemy = this;
			break;
		}
		r = m->rooms(rand() % m->rooms()->size());
	}
}