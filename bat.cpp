#include "bat.h"

Bat::Bat(Map* m, Player* p, int action_chance)
    : Enemy{ m, p }, action_chance_p{action_chance}
{
    srand(time(0));
    if(action_chance < 0 || action_chance > 100) throw std::runtime_error("Bat : invalid action_chance; value must be between 0 and 100");
}

Bat::Bat(Map* m, Player* p)
    : Enemy{ m, p }
{
    srand(time(0));
    int action_chance = rand() % 100;
    while(true)
    {
        //SOME MAGIC NUMBERS HERE!!!!!
        if (action_chance > 20 && action_chance < 55) //default action chance is between 20 and 55
        {
            action_chance_p = action_chance;
            break;
        }
        action_chance = rand() % 100;
    }
}

void Bat::action(Player* p, std::ostream& ostr)
{
	//NOTE: Try implementing different probabilities (depending on numbers of entrances of the player in the room etc)

	//Randomly teleport the player to a random location
    Room *r = pos->map->random_room();
    if (p->get_pos()->number == r->number) //there might be a chance that the same room is randomly selected
		this->action(p, ostr); // in that case, call this function again
	else
	{
        //if the random generated number is smaller than the Bat's action chance, do the actions
        if(rand() % 100 < action_chance_p)
        {
            ostr << "Oh no! A bat has taken you to another room!\n";
            p->set_pos(r);
            p->update_arrow_position();
            this->move();
        }
        else //increase the action chance for the Bat
        {
            ostr << "The bat didn't see you this time.\n";
            if (action_chance_p < 98) action_chance_p++; //raise the chance of action by 1 only if it hasn't achieved over 98%
        }
	}
}

//The bat moves to a random location
void Bat::move()
{
    pos->enemy = nullptr;
    Room *r = pos->map->random_room();
    if (pos->number == r->number || r->enemy != nullptr)
        this->move();
    else
    {
        pos = r;
        pos->enemy = this;
    }
}
