#include "enemy.h"
#include "bat.h"
#include "map.h"
#include "player.h"

//NOTE : Later, try randomizing the number of pits and bats
//constexpr int bat_count = 5;
//constexpr int pit_count = 2;

void start_message(std::ostream& ostr)
{
    ostr << "-------------------------------------------------------------------------------------\n"
         << "                     |‾|  |‾| |‾|   |‾| |‾\\‾\\   |‾| |☰☰☰☰☰☰☰☰☰|                    \n"
         << "                     | |  | | | |   | | | |\\ \\  | |     | |                        \n"
         << "                     |  ==  | | |   | | | | \\ \\ | |     | |                        \n"
         << "                     | |  | | | |___| | | |  \\ \\| |     | |                        \n"
         << "                     |_|  |_| |_______| |_|   \\_\\_|     |_|                        \n\n"
         << "                            |☰☰☰☰☰☰☰☰☰||‾|  |‾| |☰☰☰☰☰☰☰|                            \n"
         << "                                | |    | |  | | |                                    \n"
         << "                                | |    |  ==  | |☰☰☰☰|                               \n"
         << "                                | |    | |  | | |                                    \n"
         << "                                |_|    |_|  |_| |☰☰☰☰☰☰☰|                            \n\n"
         << "\\‾\\                /‾/ |‾|   |‾| |‾\\‾\\  /‾/‾| |‾‾‾‾‾‾\\  |‾|   |‾|   ==========  \n"
         << " \\ \\              / /  | |   | | | |\\ \\/ /| | |  ==  |  | |   | |  | |           \n"
         << "  \\ \\    /‾‾\\    / /   | |   | | | | \\__/ | | | _____/  | |   | |  \\ \\_____    \n"
         << "   \\ \\  / /\\ \\  / /    | |___| | | |      | | | |       | |___| |          \\ \\ \n"
         << "    \\_\\/ /  \\_\\/_/     |_______| |_|      |_| |_|       |_______|          | |   \n"
         << "                                                                    ==========       \n"
         << "-------------------------------------------------------------------------------------\n";

}
void game(int bat_count)
{
    Map m(20,0);
	Player p(&m, false);

    std::vector <Bat*> bats (bat_count);
    for (int i = 0; i < bats.size(); i++)
        bats[i] = new Bat{ &m, &p };

	//game loop
    while (true)
    {
		
		int nr;
		std::cout << "You are in " << p.get_pos()->number
			<< ". Passages go to rooms : "
			<< p.get_pos()->link_1->number << " "
			<< p.get_pos()->link_2->number << " "
			<< p.get_pos()->link_3->number << "\n";

        //std::cout << "Bats are at :";
        //for (int i = 0; i < bats.size(); i++) std::cout << bats[i]->get_pos()->number << " ";
        //std::cout << "\n";

        if (p.get_pos()->link_1->enemy)
			p.get_pos()->link_1->enemy->alert(std::cout);

		if (p.get_pos()->link_2->enemy)
			p.get_pos()->link_2->enemy->alert(std::cout);

		if (p.get_pos()->link_3->enemy)
			p.get_pos()->link_3->enemy->alert(std::cout);

        std::cin >> nr;
        std::cout << "\n";
        p.move(nr);

        if (p.get_pos()->enemy) p.get_pos()->enemy->action(&p, std::cout);
    }

    for(int i = 0; i < bats.size(); i++)
        delete bats[i];
}

//For testing map generation with different sizes
void print_map()
{
    Map m;
    for (int i = 0; i < m.rooms()->size(); i++)
    {
        std::cout << "Room " << m.rooms(i)->number << " " << m.rooms(i)->link_1->number << " " << m.rooms(i)->link_2->number << " " << m.rooms(i)->link_3->number << "\n";
    }
}

int main()
try
{
    start_message(std::cout);
    game(2);
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error : " << e.what();
	return 13;
}
