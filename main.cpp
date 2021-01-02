#include "player.h"
#include "enemy.h"
#include "bat.h"
#include "map.h"


//NOTE : Later, try randomizing the number of pits and bats
constexpr int bat_count = 5;
constexpr int pit_count = 2;

void game(int bat_count)
{
	Map m;
	Player p(&m, false);

	std::vector<Bat> bats;

	for (int i = 0; i < bat_count; i++)
		bats.push_back(Bat{ &m });


	//game loop
	while (true)
	{
		int a;
		std::cout << "You are in " << p.get_pos()->number << ". Adjacent rooms : " << p.get_pos()->link_1->number << " " << p.get_pos()->link_2->number << " " << p.get_pos()->link_3->number << "\n";
		std::cout << "Bats are in ";
		for (int i = 0; i < bats.size(); i++)
			std::cout << bats[i].get_pos()->number << " ";

		if (p.get_pos()->link_1->enemy)
		{
			std::cout << "Really nigga.\n";
			//p.get_pos().link_1->enemy->alert(std::cout);
		}
		if (p.get_pos()->link_2->enemy)
		{
			std::cout << "Really nigga.\n";
			//p.get_pos().link_1->enemy->alert(std::cout);
		}
		if (p.get_pos()->link_3->enemy)
		{
			std::cout << "Really nigga.\n";
			//p.get_pos().link_1->enemy->alert(std::cout);
		}


		std::cout << "\n";
		std::cin >> a;
		p.move(a);

		/*for (int i = 0;i < bats.size(); i++)
		{
			if (bats[i].get_pos().number == p.get_pos().number)
			{
				bats[i].action(p);
				std::cout << "Oh, no! A bat has taken you to another room!\n";
			}	
		}
		*/
	}
}

int* foo(int *i) { return i; }

int main()
try
{
	game(bat_count);

	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error: " << e.what() << std::endl;
	return 1;
}