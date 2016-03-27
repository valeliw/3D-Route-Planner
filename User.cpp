#include "User.hpp"
#include <iostream>

using namespace std;


xyz copy(xyz a) //used in constructors and in setters to set arguments as object variables
{
	xyz b;
	a.x = b.x;
	a.y = b.y;
	a.z = b.z;
	return b;
}

User::User() //with no info
{
	handicap = 0;
	ynstop = 0;
	starting.x = 0; starting.y = 0; starting.z = 0;
	stop.x = 0; stop.y = 0; stop.z = 0;
	destination.x = 0; destination.y = 0; destination.z = 0;
}
User::User(xyz starting, xyz destination) //with start and finish info
{
	this->starting = copy(starting);
	//this->starting.x = starting.x; this->starting.y = starting.y; this->starting.z = starting.z;
	this->destination = copy(destination);
	stop.x = 0; stop.y = 0; stop.z = 0;
	handicap = 0;
	ynstop = 0;
}
User::User(xyz starting, xyz stop, xyz destination) //with start, stop, and finish info
{
	this->starting = copy(starting);
	//this->starting.x = starting.x; this->starting.y = starting.y; this->starting.z = starting.z;
	this->destination = copy(destination);
	this->stop = copy(stop);
	ynstop = 1;
	handicap = 0;
}
User::~User(){};


bool User::getHandicap()
{
	return this->handicap;
}
void User::setHandicap(bool a)
{
	this->handicap = a;
}

xyz User::getStarting()
{
	return this->starting;
}
void User::setStarting(xyz coordinates)
{
	this->starting = copy(coordinates);
}

xyz User::getStop()
{
	return this->stop;
}
void User::setStop(xyz coordinates)
{
	this->stop = copy(coordinates);
}

xyz User::getDestination()
{
	return this->destination;
}
void User::setDestination(xyz coordinates)
{
	this->destination = copy(coordinates);
}

////////////////////////////////////////////////////////////////////////////DEBUGGING


