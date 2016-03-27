#ifndef USER_HPP_
#define USER_HPP_
#include <iostream>
using namespace std;

struct xyz{ //type to workj with our coordinates
	int x; //x coordinate on the floor
	int y; //y coordinate on the floor
	int z; //floor number
};

xyz copy(xyz); //used in the constructors and setters in User.cpp


class User{
private:
	bool handicap; // if the user is hadicapped (ie no stairs)
	bool ynstop; // if the user has a stop to make or not

	xyz starting;
	xyz stop;
	xyz destination;
	
public:
	User();
	User(xyz, xyz);
	User(xyz, xyz, xyz); // initialise user with starting, stop, and destination info [starting coordinates, stop coordinates, destination coordinates]
	~User();

	bool getHandicap();
	void setHandicap(bool);

	xyz getStarting();
	void setStarting(xyz); //set location of starting x, y and z (box x, box y, floor number)

	xyz getStop();
	void setStop(xyz); //set location of stop x, y, z

	xyz getDestination();
	void setDestination(xyz); //set destination x,y,z


	///DEBUGGING


};
#endif /*USER_HPP_*/