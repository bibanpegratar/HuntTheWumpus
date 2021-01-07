#include "wumpus.h"

void Wumpus::move()
{
	int i = 0;
	srand(time(0));
    i = rand() % 3 + 1;
    std::cout << "\t The Wumpus moved!\n";
	switch (i)
	{
	case 1:
		pos->enemy = nullptr;
		pos = pos->link_1;
		pos->enemy = this;
		break;

	case 2:
		pos->enemy = nullptr;
		pos = pos->link_2;
		pos->enemy = this;
		break;

	case 3:
		pos->enemy = nullptr;
		pos = pos->link_3;
		pos->enemy = this;
		break;

	default:
		std::cout << "wrong room\n";
		break;
	}
}

