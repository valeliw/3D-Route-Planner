#ifndef BUILDING_HPP_
#define BUILDING_HPP_
#include <string>
#include <iostream>

using namespace std;

class Building						//class building which has the number of floors
{
private:
	int Floors;
public:								//constrcut,destruct,set and get number of floors
	Building();
	~Building();
	int getFloors();				//gets the number of floors
};

class Floor : public Building		//class floors contains the number of rooms
{
private:
	int no_ofRooms;					//number of floors	
	int floorNumber;				//floor number
public:
	Floor();
	~Floor();
	void setno_ofRooms(int);		//set number of rooms
	int getno_ofRooms();			//get the number of rooms
	void setFloornumber(int);			//set number of floors
	int getFloornumber();			//get the floor numbers
};

class Box : public Building			//box class this sets the type that each element of the matrix contains such as room,hallway and impassable
{
private:
	Box();							//construct/destruct
	~Box();
	string boxType;
	int length;						//data to store the box length eg 2m also to decide if a box is impassable wall will have value 10000m so its never the shortest route
public:
	void setBoxtype(string);		//sets the the box type room/hall/wall/toilet/elevator/stairs
	string getBoxtype();			//returns the box type
	};
#endif BUILDING_HPP_