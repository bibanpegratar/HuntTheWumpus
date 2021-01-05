#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>

/*
The (original) map consits of 20 rooms, each one being linked to other 3, in the shape of a "squashed" dodecahedron.
A Room consits of a number (a point of the dodecahedron) and 3 connections to other Rooms (which represent the vertices in a dodecahedron)
A squashed dodecahedron has three "layers", which are represented down bellow
	- the first is the base layer of size number of rooms \ 4 ( first_row_p )
	- the second layer has double the first layer's rooms ( second_row_p )
	- the last layer has the same number of rooms as the first one ( third_row_p )
All the rooms are also stored inside rooms_p.
Inside the constructor, each layer is initialized, and then generate_map() fills the rooms_p vector with all the rooms
	- note that the default size of the map will be 20 ( all the points on a dodecahedron )
	- the number of rooms can be customized, but it must still represent a version of a dodecahedron to be valid
*/

struct Room;
class Enemy;
class Player;

class Map
{
public:
	//constructors
	Map(int room_count, int seed);
	Map(int seed);
	Map(); //the default size of the map is 20 rooms (as it always should be)

	//destructor
    ~Map() { delete rooms_p; }

	const std::vector<Room> *rooms() const { return rooms_p; }
	Room* rooms(int index) { if (index < 0 || index > rooms_p->size()) throw std::runtime_error("invalid index"); return &rooms_p->at(index); }
	Room* rooms_by_number(int number);
	Room* random_room();

	const std::vector<int> *room_numbers() { return &room_numbers_p; }

private:
	int room_count_p; //used for Map construction
	std::vector <int> room_numbers_p; //holds all the ints for rooms available to use
	std::vector <Room> *rooms_p; //holds all the Rooms in the Map

	void generate_map();
	void fill_rooms(int size, std::vector <Room>& rooms);
	void link_map_to_rooms(std::vector<Room>& r);
};

struct Room
{
	int number; // the number of the current room
    Room *link_1 = nullptr;
    Room *link_2 = nullptr;
    Room *link_3 = nullptr;
	Map *map = nullptr; // each room knows about the map it's on
	Enemy *enemy = nullptr; // each room knows if it has an enemy
    //~Room(){delete link_1; delete link_2; delete link_3; delete enemy;}
};

void fill_vector(std::vector <int>&);
