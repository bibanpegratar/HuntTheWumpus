#include "map.h"

//Fills an array with numbers from 1 to v.size()
void fill_vector(std::vector <int>& v)
{
	for (int i = 0; i < v.size(); i++)
		v[i] = i + 1;
}

void Map::fill_row(int size, std::vector <Room>& v)
{
	for (int i = 0; i < size; i++)
	{
		int randint = rand() % room_numbers_p.size(); //select a random int from the v vector
		Room r;
		r.number = room_numbers_p[randint];
		v.push_back(r);
		room_numbers_p.erase(room_numbers_p.begin() + randint); // delete the used number from v so it won't be used again
	}
}

void Map::link_first_row()
{
	int first_row_size = room_count_p / 4;
	//fill the first row with random integers
	fill_row(first_row_size, first_row_p);
	link_map_to_rooms(first_row_p);

	first_row_p[0].link_1 = &first_row_p[first_row_p.size() - 1]; //link the first room with the last room
	first_row_p[0].link_2 = &first_row_p[1]; //link the first room with the next room

	//link each room with the previous and next
	for (int i = 1; i < first_row_p.size() - 1; i++)
	{

		first_row_p[i].link_1 = &first_row_p[i - 1];
		first_row_p[i].link_2 = &first_row_p[i + 1];
	}

	first_row_p[first_row_p.size() - 1].link_1 = &first_row_p[first_row_p.size() - 2]; //link the last room with the second to last room
	first_row_p[first_row_p.size() - 1].link_2 = &first_row_p[0]; //link the last room with the first room
};

void Map::link_second_row()
{
	int second_row_size = room_count_p / 2;
	fill_row(second_row_size, second_row_p);
	link_map_to_rooms(second_row_p);

	second_row_p[0].link_3 = &first_row_p[0];
	first_row_p[0].link_3 = &second_row_p[0];

	second_row_p[0].link_1 = &second_row_p[second_row_p.size() - 1];
	second_row_p[0].link_2 = &second_row_p[1];

	for (int i = 1; i < second_row_p.size() - 1; i++)
	{
		switch (i % 2)
		{
		case (0):
		{
			second_row_p[i].link_1 = &second_row_p[i - 1];
			second_row_p[i].link_2 = &second_row_p[i + 1];
			second_row_p[i].link_3 = &first_row_p[i / 2];
			first_row_p[i / 2].link_3 = &second_row_p[i];
			break;
		}

		case (1):
		{
			second_row_p[i].link_1 = &second_row_p[i - 1];
			second_row_p[i].link_2 = &second_row_p[i + 1];
			break;
		}

		default:
			throw std::runtime_error("impossible");
			break;
		}

	}

	second_row_p[second_row_p.size() - 1].link_1 = &second_row_p[second_row_p.size() - 2];
	second_row_p[second_row_p.size() - 1].link_2 = &second_row_p[0];
}

void Map::link_third_row()
{
	int third_row_size = room_count_p / 4;
	fill_row(third_row_size, third_row_p);
	link_map_to_rooms(third_row_p);

	//add link 3 to all
	int index = 0;
	for (int i = 0; i < second_row_p.size(); i++)
	{
		if (second_row_p[i].link_3 == nullptr)
		{
			third_row_p[index].link_3 = &second_row_p[i];
			second_row_p[i].link_3 = &third_row_p[index];
			index++;
		}
	}

	third_row_p[0].link_1 = &third_row_p[third_row_p.size() - 1];
	third_row_p[0].link_2 = &third_row_p[1];

	for (int i = 1; i < third_row_p.size() - 1; i++)
	{
		third_row_p[i].link_1 = &third_row_p[i - 1];
		third_row_p[i].link_2 = &third_row_p[i + 1];
	}

	third_row_p[third_row_p.size() - 1].link_1 = &third_row_p[third_row_p.size() - 2];
	third_row_p[third_row_p.size() - 1].link_2 = &third_row_p[0];
}

void Map::generate_map()
{
	for (int i = 0; i < first_row_p.size(); i++)
		rooms_p.push_back(first_row_p[i]);

	for (int i = 0; i < second_row_p.size(); i++)
		rooms_p.push_back(second_row_p[i]);

	for (int i = 0; i < third_row_p.size(); i++)
		rooms_p.push_back(third_row_p[i]);
}

void Map::link_map_to_rooms(std::vector<Room>& r)
{
	//this method should only be called after the whole map is generated
	for (int i = 0; i < r.size(); i++)
	{
		r[i].map = this;
	}
}

Map::Map(int room_count, int seed)
	: room_count_p{ room_count }, room_numbers_p{ std::vector<int>(room_count_p) }
{
	srand(seed); // seed rand
	//if the first row is smaller than 3 or if the rooms can't be distributed right, they won't link properly
	if (room_count_p % 4 != 0 || room_count_p / 4 < 3) throw std::runtime_error("invalid room count");
	fill_vector(room_numbers_p);
	//enemy_rooms_p = room_numbers_p;
	link_first_row();
	link_second_row();
	link_third_row();
	generate_map();
}

Map::Map(int seed)
	: room_count_p{ 20 }, room_numbers_p{ std::vector<int>(room_count_p) }
{
	srand(seed); // seed rand
	fill_vector(room_numbers_p);
	//enemy_rooms_p = room_numbers_p;
	link_first_row();
	link_second_row();
	link_third_row();
	generate_map();
}

Map::Map()
	: room_count_p{ 20 }, room_numbers_p{ std::vector<int>(room_count_p) }
{
	srand(time(0)); // seed rand
	fill_vector(room_numbers_p);
	//enemy_rooms_p = room_numbers_p;
	link_first_row();
	link_second_row();
	link_third_row();
	generate_map();
}

Room* Map::rooms_by_number(int number) 
{
	for (int i = 0; i < rooms_p.size(); i++) 
		if (rooms_p[i].number == number) return &rooms_p[i]; 
	// NOTE : handle no room found
}

/*Room* Map::fill_with_enemy()
{
	
}*/