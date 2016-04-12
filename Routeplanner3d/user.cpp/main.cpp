#include "stdafx.h"
#include "targetver.h"
#include <iostream>
#include <vector>
#include <string>
#include "Dijsktras.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	try {
		DijkstrasTest();
	}
	catch (const std::exception& str)
	{
		std::cerr << "Exception error: " << str.what() << ", please input a correct room name" << std::endl;
		system("pause");
		try {
			DijkstrasTest();
		}
		catch (const std::out_of_range& oor) //check if the user inputs something wrong
		{
			std::cerr << "Out of range error: " << oor.what() << ", please input a correct room name (ie JW101 or JWToilet101)." << std::endl;
			system("pause");
		}
		try {
			DijkstrasTest();
		}
		catch (const std::out_of_range& oor) //check if the user inputs something wrong
		{
			std::cerr << "Out of range error: " << oor.what() << ", please input a correct room name (ie JW101 or JWToilet101)." << std::endl;
			system("pause");
		}
	}
	return 0;
}
