#include "player.h"

Player::Player(Map* m, bool rand_pos, int arrows)
    :is_alive_p{ true }
{
	if (rand_pos) pos = m->random_room(); //spawn the player at a random position
	else pos = m->rooms(0); //spawn the player at the first room in the vector
    arrows_p = std::vector<Arrow*> ( arrows, new Arrow{this} );
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
    else if (pos->link_1->number == r->number)
    {
        pos = pos->link_1;
        update_arrow_position();
    }
    else if (pos->link_2->number == r->number)
    {
        pos = pos->link_2;
        update_arrow_position();

    }
    else if (pos->link_3->number == r->number)
    {
        pos = pos->link_3;
        update_arrow_position();
    }
	else std::cout << "Can't go there !\n";
}

bool Player::shoot(int range, std::istream& istr, Wumpus* wumpus)
{
    if(arrows_p.size() == 0)
    {
        std::cout << "You ran out of arrows!\n";
        return false;
    }
    if(arrows_p[arrows_p.size()-1]->shoot(range, istr, wumpus))
    {
        //delete arrows_p[arrows_p.size() - 1];
        arrows_p.pop_back();
        return true;
    }
    return false;
}

//should be called each time Player's pos is updated
void Player::update_arrow_position()
{
    for(int i = 0; i < arrows_p.size(); i++)
    {
        arrows_p[i]->pos = pos;
    }
}


