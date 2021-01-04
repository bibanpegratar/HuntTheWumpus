#include "map.h"

//Fills a vector with numbers from 1 to v.size()
void fill_vector(std::vector <int>& v)
{
	for (int i = 0; i < v.size(); i++)
		v[i] = i + 1;
}

//Fill rooms_p with Rooms with random number value from room_numbers
void Map::fill_rooms(int size, std::vector <Room>& v)
{
	for (int i = 0; i < size; i++)
	{
		int randint = rand() % room_numbers_p.size(); //select a random int from the v vector
		Room r;
		r.number = room_numbers_p[randint];
		v[i] = r;
		room_numbers_p.erase(room_numbers_p.begin() + randint); // delete the used number from v so it won't be used again
	}
}

//Sets the links inside rooms_p accordingly
void Map::generate_map()
{
	int first_r_size = room_count_p / 4;
	int second_r_size = room_count_p / 2;
	int third_r_size = first_r_size;
	int index = 0; // used for iterating over rooms_p

	
	//for the first room of the first row
	rooms_p->at(index).link_1 = &rooms_p->at(index + first_r_size - 1); //link_1 = the last room on the first row
	rooms_p->at(index).link_2 = &rooms_p->at(index + 1); //link_2 = next room
	index++;

	//for rooms between the first and the last of the first row
	for (int i = 0; i < first_r_size - 2; i++)
	{
		rooms_p->at(index).link_1 = &rooms_p->at(index - 1); //link_1 = previous room
		rooms_p->at(index).link_2 = &rooms_p->at(index + 1); //link_2 = next room
		index++;
	}

	//for the last room of the first row
	rooms_p->at(index).link_1 = &rooms_p->at(index - 1); //link_1 = previous room
	rooms_p->at(index).link_2 = &rooms_p->at(index - (first_r_size - 1)); //link_2 = the first room on the first row
	index++;


	//Linking rooms of first row (link_1 and link_2)
	//for the first room of the second row
	rooms_p->at(index).link_1 = &rooms_p->at(index + second_r_size - 1); //link_1 = the last room on the second row
	rooms_p->at(index).link_2 = &rooms_p->at(index + 1); //link_2 = next room
	index++;

	//for rooms between the first and the last of the second row
	for (int i = 0; i < second_r_size - 2; i++)
	{
		rooms_p->at(index).link_1 = &rooms_p->at(index - 1);
		rooms_p->at(index).link_2 = &rooms_p->at(index + 1);
		index++;
	}

	rooms_p->at(index).link_1 = &rooms_p->at(index - 1);
	rooms_p->at(index).link_2 = &rooms_p->at(index - (second_r_size + 1)); 
	index++;

	//Linking rooms of first row (link_1 and link_2)
	rooms_p->at(index).link_1 = &rooms_p->at(index + third_r_size - 1);
	rooms_p->at(index).link_2 = &rooms_p->at(index + 1);
	index++;

	for (int i = 0; i < third_r_size - 2; i++)
	{
		rooms_p->at(index).link_1 = &rooms_p->at(index - 1);
		rooms_p->at(index).link_2 = &rooms_p->at(index + 1);
		index++;
	}

	rooms_p->at(index).link_1 = &rooms_p->at(index - 1);
	rooms_p->at(index).link_2 = &rooms_p->at(index - (third_r_size + 1));
	index++;

	index = 0; // reset the index, start iterating from the start of the vector to add link_3
	
	//Linking link_3 between first and second row
	for (int i = 0; i < first_r_size; i++)
	{
		rooms_p->at(index).link_3 = &rooms_p->at(index * 2 + first_r_size); //linking "din doi in doi" (first row room)
		rooms_p->at(index * 2 + first_r_size).link_3 = &rooms_p->at(index); //link_3 of the second row room
		index++;
	}

	//Linking link_3 between remaining rooms on second row and third row
	for (int i = 0; i < second_r_size; i++)
	{
		if (index % 2 == 0) //the rooms with no link_3 have even indexes
		{
			rooms_p->at(index).link_3 = &rooms_p->at(room_count_p - third_r_size + i / 2);
			rooms_p->at(room_count_p - third_r_size + i / 2).link_3 = &rooms_p->at(index);
		}
		index++;
	}

}

//This method should only be called after the whole map is generated
//Sets the Map pointer inside Room to this Map
void Map::link_map_to_rooms(std::vector<Room>& r)
{
	for (int i = 0; i < r.size(); i++)
	{
		r[i].map = this;
	}
}

Map::Map(int room_count, int seed)
	: room_count_p{ room_count }, room_numbers_p{ std::vector<int>(room_count_p) }, rooms_p{ new std::vector<Room>(room_count_p) }
{
	//if the first row is smaller than 3 or if the rooms can't be distributed right, they won't link properly
	if (room_count_p % 4 != 0 || room_count_p / 4 < 3) throw std::runtime_error("invalid room count");
	srand(seed); // seed rand()
	fill_vector(room_numbers_p);
	fill_rooms(rooms_p->size(), *rooms_p);
	generate_map();
	link_map_to_rooms(*rooms_p);
}

Map::Map(int seed)
	: room_count_p{ 20 }, room_numbers_p{ std::vector<int>(room_count_p) }, rooms_p{ new std::vector<Room>(room_count_p) }
{
	srand(seed); // seed rand()
	fill_vector(room_numbers_p);
	fill_rooms(rooms_p->size(), *rooms_p);
	generate_map();
	link_map_to_rooms(*rooms_p);
}

Map::Map()
	: room_count_p{ 20 }, room_numbers_p{ std::vector<int>(room_count_p) }, rooms_p{ new std::vector<Room>(room_count_p) }
{
	srand(time(0)); // seed rand()
	fill_vector(room_numbers_p);
	fill_rooms(rooms_p->size(), *rooms_p);
	generate_map();
	link_map_to_rooms(*rooms_p);
}

Room* Map::rooms_by_number(int number)
{
	for (int i = 0; i < rooms_p->size(); i++)
		if (rooms_p->at(i).number == number) return &rooms_p->at(i);
	// NOTE : handling of room not found not properly implemented, returning nullptr
	return nullptr;
}

Room* Map::random_room()
{
	return &rooms_p->at(rand() % rooms_p->size());
}
