#include "bat.h"

void Bat::action(Player* p, std::ostream& ostr)
{
	//NOTE: Try implementing different probabilities (depending on numbers of entrances of the player in the room etc)
	//NOTE: Try making the bat teleport to a random location too

	//Randomly teleport the player to a random location
	Room *r = this->get_pos()->map->random_room();
	if (p->get_pos()->number == r->number) //there might be a chance that the same room is randomly selected
		this->action(p, ostr); // in that case, call this function again
	else
	{
		ostr << "Oh no! A bat has taken you to another room!\n";
		p->set_pos(r);
	}
}
