#include "map.h"
#include "arrow.h"
#include "player.h"
#include "enemy.h"
#include "bat.h"
#include "pit.h"
#include "wumpus.h"

//NOTE : Later, try randomizing the number of pits and bats
//constexpr int bat_count = 5;
//constexpr int pit_count = 2;

void keep_window_open(char ch)
{
	std::cout << "Press " << ch << " to exit.\n";
	char a;
	while (std::cin >> a)
		if (a == ch) break;
}
void start_banner(std::ostream& ostr)
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

void start_message(std::ostream &ostr)
{
	ostr << "Hunt The Wumpus - Remake (from the game in 17')                        \n"
		<< "								by Biban        					    \n\n"

		<< "YOU ARE A FAMOUS HUNTER DESCENDING DOWN INTO THE CAVES OF DARKNESS,     \n"
		<< "LAIR OF THE INFAMOUS MAN - EATING WUMPUS.YOU ARE EQUIPPED WITH 5 	    \n"
		<< "BENT ARROWS, AND ALL YOUR SENSES.THERE ARE 20 CAVES CONNECTED			\n"
		<< "BY TUNNELS, AND THERE ARE TWO OTHER KINDS OF HAZARDS :					\n\n"

		<< "A) PITS, WHICH ARE BOTTOMLESS, AND USUALLY FATAL TO FALL				\n"
        << "INTO .THERE ARE 2 SUCH PITS IN THE NETWORK. 							\n\n"

		<< "B) SUPER - BATS, WHICH IF YOU STUMBLE INTO THEIR ROOM WILL				\n"
		<< "PICK YOU UP AND DROP YOU IN SOME RANDOM ROOM IN THE NETWORK.			\n"
		<< "THEY GENERALLY STAY IN THEIR OWN ROOMS, EXCEPT WHEN DISPOSING			\n"
		<< "OF INTRUDERS OR SCAVENGING FOR FOOD IN THE PITS.						\n\n"

		<< "IF YOU BLUNDER INTO THE SAME ROOM AS THE WUMPUS, YOU LOSE....			\n\n"

		<< "THE NORMALLY SLEEPING WUMPUS DOES NOT MOVE(HAVING GORGED HIMSELF UPON	\n"
		<< "A PREVIOUS HUNTER).HOWEVER SEVERAL THINGS CAN WAKE HIM UP :		        \n\n"

        << "\t1) WALKING INTO HIS ROOM                                              \n"
		<< "\t2) SHOOTING AN ARROW ANYWHERE IN THE NETWORK							\n"
		<< "\t3) TRIPPING OVER DEBRIS(CLUMSINESS).									\n\n"

		<< "IF HE WAKES UP THERE'S A POSSIBILITY HE WILL MOVE, HOWEVER, HE'S TOO  	\n"
		<< "LAZY TO MOVE MORE THAN ONE ROOM BETWEEN SNOOZES.THE WUMPUS IS TOO	   	\n"
		<< "BIG TO BE PICKED UP BY SUPER - BATS AND HAS SUCKER FEET, SO HE DOESN'T	\n"
		<< "FALL INTO THE PITS.												      	\n\n"

		<< "YOU CAN SMELL THE WUMPUS FROM ONE ROOM AWAY.YOU WILL		        	\n"
		<< "TREMBLE WITH FEAR WHEN HE MOVES ABOUT.YOU CAN HEAR SUPER - BATS FROM  	\n"
		<< "ONE ROOM AWAY, AND FEEL DRAFTS(FROM BOTTOMLESS PITS) FROM ONE ROOM	   	\n"
		<< "AWAY(AND TASTE THE FEAR...).										   	\n\n"

        << "TO MOVE TYPE 'M' FOLLOWED BY AN ADJACENT ROOM.                          \n"
        << "TO SHOOT TYPE 'S' <NUMBER_OF_ADJACENT_ROOMS> ADJACENT_ROOMS             \n"
        << "\t -NUMBER_OF_ADJACENT_ROOMS = the number of rooms the arrow will go through(max 3);\n"
        << "\t -ADJACENT_ROOMS = the list of adjacent rooms you want the arrows to go through (space separated);\n\n"

		<< "EACH ROOM IS CONNECTED TO THREE OTHER ROOMS BY THREE TUNNELS.		   	\n"
		<< "YOU MUST ALWAYS MOVE BETWEEN ROOMS BY SPECIFYING WHICH				   	\n"
		<< "TUNNEL YOU WISH TO EXPLORE.YOU CAN ALWAYS RETRACE YOUR FOOT STEPS	   	\n"
		<< "BY MOVING BACK USING THE SAME TUNNEL DESIGNATOR.					   	\n\n"

		<< "\tGOOD LUCK HUNTING!! (Press X to exit the game)					    \n\n";
}

void game(int bat_count, int pit_count)
{
	Map m(0);
    Player p(&m, false, 5); //a player with 5 arrows

	//allocate memory on the free store for enemies
	std::vector <Bat*> bats(bat_count);
	for (int i = 0; i < bats.size(); i++)
		bats[i] = new Bat{ &m, &p };

	std::vector <Pit*> pits(pit_count);
	for (int i = 0; i < pits.size(); i++)
		pits[i] = new Pit{ &m, &p };

	Wumpus *wumpus = new Wumpus{ &m, &p };

	//game loop
    while (true)
    {
		std::cout << "You are in " << p.get_pos()->number
			<< ". Passages go to rooms : "
			<< p.get_pos()->link_1->number << " "
			<< p.get_pos()->link_2->number << " "
			<< p.get_pos()->link_3->number << "\n";

        //std::cout << "Bats are at :";
        //for (int i = 0; i < bats.size(); i++) std::cout << bats[i]->get_pos()->number << " ";
        //std::cout << "\n";

        //std::cout << "Pits are at :";
        //for (int i = 0; i < pits.size(); i++) std::cout << pits[i]->get_pos()->number << " ";
        //std::cout << "\n";

        //std::cout << "The Wumpus is on " << wumpus->get_pos()->number << ".\n";

        if (p.get_pos()->link_1->enemy)
			p.get_pos()->link_1->enemy->alert(std::cout);

		if (p.get_pos()->link_2->enemy)
			p.get_pos()->link_2->enemy->alert(std::cout);

		if (p.get_pos()->link_3->enemy)
			p.get_pos()->link_3->enemy->alert(std::cout);

		char ch;
		std::cin >> ch;

		switch (ch)
		{
			case 'M':
			{
				int nr;
                std::cin >> nr;
                if(std::cin.fail())
                {
					std::cin.ignore(100000000, '\n');
                    std::cerr << "Error reading number\n";
                    std::cin.clear();
                    break;
                }
				std::cout << "\n";
                p.move(nr, std::cout);
                break;
			}
			
			case 'S':
			{
				int range;
                //std::cout << "How many rooms do you want to shoot the arrow through ? (max " << p.get_arrows()->at(0).max_range_p << " rooms)\n";
				std::cin >> range;
                if(std::cin.fail())
                {
                    std::cerr << "Error reading number\n";
					std::cin.ignore(100000000, '\n');
                    std::cin.clear();
                    break;
                }
                if(range == 0)
                {
                    std::cout << "Range cannot be 0!\n";
                    break;
                }
                bool success_shot = p.shoot(range, std::cin, std::cout, wumpus);

                if(wumpus->is_alive() && success_shot) //if the wumpus is still alive after shooting, it means it hasn't been hit by an arrow, so move
                {
                    std::cout << "You missed! ";
                    wumpus->move();
                    break;
                }
                else if (!wumpus->is_alive())
                {
                    break;
                }
                break;
			}
            default:
                std::cout << "Invalid choice. Try again\n\n";
                std::cin.ignore(100000000,'\n'); // clear input buffer for a huge number of chars or until newline
                break;
		}

        if (p.get_pos()->enemy) p.get_pos()->enemy->action(&p, std::cout);

        if (p.get_arrows().size() == 0)
        {
            p.die(); //if the player runs out of arrows, die
        }


        if (!p.is_alive())
        {
            std::cout << "YOU DIED !\n";
            break;
        }

        if (!wumpus->is_alive())
        {
            std::cout << "YOU WON !\n";
            break;
        }
    }

	//dealocate memory on the free store
    for(int i = 0; i < bats.size(); i++)
    {
        delete bats[i];
    }

	for (int i = 0; i < pits.size(); i++)
    {
		delete pits[i];
    }

	delete wumpus;
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
    game(3,2);
	keep_window_open('X');
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error : " << e.what();
	return 13;
}

