#include <iostream>
#include "Building.hpp"

using namespace std;

int Building::getFloors()
{
	return this->Floors;
}


int Floor::getno_ofRooms()			//get the number of rooms
{
	return this->no_ofRooms;
}


void Floor::setFloornumber(int x)			//set number of floors
{
	x = 0;
	floorNumber = x;
	if (x > 25 & x < 5)
	{
		cout << "incorrect number of floors";
	}

}


int Floor::getFloornumber()			//get the floor numbers
{
	return this->floorNumber;
}


void Box::setBoxtype(string a)
{
	this->boxType = a;
}


string Box::getBoxtype()
{
	return this->boxType;
}