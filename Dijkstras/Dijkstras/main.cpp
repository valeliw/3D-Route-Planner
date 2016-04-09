#include "stdafx.h"
#include "Dijkstras.hpp"
#include <iostream>
#include <vector>
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		DijkstrasTest();
	}
	catch (const out_of_range& oor)
	{
		cerr << "Out of range error: " << oor.what() << ", please input a correct room." << endl;
	}
	return 0;
}