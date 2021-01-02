#include "bat.h"

void Bat::action(Player* p)
{
	//NOTE: Try implementing different probabilities (depending on numbers of entrances of the player in the room etc)
	//Randomly teleport the player to a random location
	//Room *r = random_room(p->get_pos().map).number; 
	//if (p->get_pos().number == random_room(p->get_pos().map).number) //there might be a chance that the same room is randomly selected
		//this->action(p); // in that case, call this function again
	//else p->set_pos(*random_room(*this->get_pos().map)); 
}

void Bat::alert(std::ostream& ostr)
{
	ostr << "A bat is nearby.";
}