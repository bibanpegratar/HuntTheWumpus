#include "arrow.h"
#include "wumpus.h"

Arrow::Arrow(int max_range, Player* p)
    :max_range_p{ max_range }
{
    pos = p->get_pos();
	pos->arrow = this;
}

Arrow::Arrow(Player* p)
    : max_range_p{ 3 }
{
    pos = p->get_pos();
	pos->arrow = this;
}

bool Arrow::shoot(int range, std::istream& istr, std::ostream& ostr, Wumpus* wumpus)
{
	if (range > max_range_p)
	{
		std::cout << "Arrow out of range!\n";
        return false;
	}

    if (range == 0) return true; //weird case if the user passes 0

	int a;
	istr >> a;
	if (a == pos->link_1->number)
	{
		pos->arrow = nullptr;
		pos = pos->link_1;
		pos->arrow = this;
        if (wumpus->get_pos() == pos)
            wumpus->die();
        shoot(range - 1, istr, ostr, wumpus);
	}

	else if (a == pos->link_2->number)
	{
		pos->arrow = nullptr;
		pos = pos->link_2;
		pos->arrow = this;
        if (wumpus->get_pos() == pos)
            wumpus->die();
        shoot(range - 1, istr, ostr, wumpus);
	}

	else if (a == pos->link_3->number)
	{
		pos->arrow = nullptr;
		pos = pos->link_3;
		pos->arrow = this;
        if (wumpus->get_pos() == pos)
            wumpus->die();
        shoot(range - 1, istr, ostr, wumpus);
	}

	else
	{
        ostr << "Invalid room!\n";
        return false;
	}
}
