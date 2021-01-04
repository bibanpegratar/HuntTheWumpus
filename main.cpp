#include "enemy.h"
#include "bat.h"
#include "map.h"
#include "player.h"

//NOTE : Later, try randomizing the number of pits and bats
constexpr int bat_count = 5;
constexpr int pit_count = 2;

void game(int bat_count)
{
	Map m;
	Player p(&m, false);

	std::vector <Bat*> *bats = new std::vector<Bat*>(bat_count);
	for (int i = 0; i < bats->size(); i++)
		bats->at(i) = &Bat{ &m, &p };

	//game loop
	while (true)
	{
		
		int nr;
		if (p.get_pos()->enemy) p.get_pos()->enemy->action(&p, std::cout);

		std::cout << "You are in " << p.get_pos()->number
			<< ". Passages go to rooms : "
			<< p.get_pos()->link_1->number << " "
			<< p.get_pos()->link_2->number << " "
			<< p.get_pos()->link_3->number << "\n";

		//std::cout << "Bats are at :";
		//for (int i = 0; i < bats->size(); i++) std::cout << bats->at(i)->get_pos()->number << " ";

		if (p.get_pos()->link_1->enemy)
		{
			p.get_pos()->link_1->enemy->alert(std::cout);
		}
		if (p.get_pos()->link_2->enemy)
		{
			p.get_pos()->link_2->enemy->alert(std::cout);
		}
		if (p.get_pos()->link_3->enemy)
		{
			p.get_pos()->link_3->enemy->alert(std::cout);
		}

		std::cin >> nr;
		p.move(nr);
		while (p.get_pos()->enemy) p.get_pos()->enemy->action(&p, std::cout);
	}
	delete bats;
}

int main()
try
{
	game(5);
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error : " << e.what();
	return 13;
}
