// Dijkstras.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void DijkstrasTest();

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		DijkstrasTest();
	}
	catch (const out_of_range& oor) //check if the user inputs something wrong
	{
		cerr << "Out of range error: " << oor.what() << ", please input a correct room name (ie JW101 or JWToilet101)." << endl;
	}
	catch (const exception& str)
	{
		cerr << "Exception error: " << str.what() << ", please input a correct room name" << endl;
	}
	catch (...)
	{
		cerr << "Can't read ID of node, error: " << "..." << ", please input a correct room name (ie JW101 or JWToilet101." << endl;
	}
	return 0;
}


//////////////

class Node;
class Edge;

void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);

///my own functions
//Node* setStartingpoint();
//Node* setDestinationPoint();
int setStartingPoint();
int setDestinationPoint();


vector<Node*> nodes;
vector<Node*> nodesFINAL;
vector<Edge*> edges;
vector<string> steps;

/*Node types:
1 -> room
2 -> toilet
3 -> stairs
4 -> elevators
5 -> connectors

Buildings:
1 -> JW
2 -> RC
3 -> TG
*/

class Node
{
public:
	Node(string id)
		: id(id), previous(NULL), distanceFromStart(INT_MAX)
	{
		nodes.push_back(this);
		nodesFINAL.push_back(this);
	}
	Node(string id, int type, int building, int floor)
		: id(id), previous(NULL), distanceFromStart(INT_MAX), type(type), building(building), floor(floor)
	{
		nodes.push_back(this);
		nodesFINAL.push_back(this);
	}
public:
	string id;
	Node* previous;
	int distanceFromStart;
	int type;
	int building;
	int floor;


};


class Edge
{
public:
	Edge(Node* node1, Node* node2, int distance)
		: node1(node1), node2(node2), distance(distance)
	{
		edges.push_back(this);
	}
	bool Connects(Node* node1, Node* node2)
	{
		return (
			(node1 == this->node1 &&
				node2 == this->node2) ||
			(node1 == this->node2 &&
				node2 == this->node1));
	}
public:
	Node* node1;
	Node* node2;
	int distance;
};

/////////////////////////////////////////////////////////////

////done by me
/*Node* setStartingPoint()
{
	string start;
	int size = nodes.size();
	//Enter id of starting point: 
	getline(cin, start);
	for (int i = 0; i < size; i++)
	{
		if (start == nodes.at(i)->id)
		{
			return nodes.at(i);
		}
	}
}

Node* setDestinationPoint()
{
	string destination;
	int size = nodes.size();
	//Enter id of destination point:
	getline(cin, destination);
	for (int i = 0; i < size; i++)
	{
		if (destination == nodes.at(i)->id)
		{
			return nodes.at(i);
		}
	}
}*/
int setStartingPoint()
{
	string start;
	int size = nodes.size();
	//cout << "Enter id of starting point: " << endl;
	getline(cin, start);
	for (int i = 0; i < size; i++)
	{
		if (start == nodes.at(i)->id)
		{
			return i;
		}
	}
}

int setDestinationPoint()
{
	string destination;
	int size = nodes.size();
	//cout << "Enter id of starting point: " << endl;
	getline(cin, destination);
	for (int i = 0; i < size; i++)
	{
		if (destination == nodes.at(i)->id)
		{
			return i;
		}
	}
}

void DijkstrasTest()
/////////////FLOOR DECLARATIONS!////////////////////////

//note: Node(id, type, building, floor)
{	
	//first floor of JW
	Node* jw101 = new Node("JW101", 1, 1, 1); //room 101, type room, JW building, floor 1
	Node* jw102 = new Node("JW102", 1, 1, 1);
	Node* jw103 = new Node("JW103", 1, 1, 1);
	Node* jw104 = new Node("JW104", 1, 1, 1);
	Node* jw105 = new Node("JW105", 1, 1, 1);
	Node* jw106 = new Node("JW106", 1, 1, 1);
	Node* jw107 = new Node("JW107", 1, 1, 1);
	Node* jw108 = new Node("JW108", 1, 1, 1);
	Node* jw109 = new Node("JW109", 1, 1, 1);
	Node* jw110 = new Node("JW110", 1, 1, 1);
	Node* jw111 = new Node("JW111", 1, 1, 1);
	Node* jw112 = new Node("JW112", 1, 1, 1);
	Node* jw113 = new Node("JW113", 1, 1, 1);
	Node* jw114 = new Node("JW114", 1, 1, 1);
	Node* jw115 = new Node("JW115", 1, 1, 1);
	Node* jw116 = new Node("JW116", 1, 1, 1);
	Node* jw117 = new Node("JW117", 1, 1, 1);
	Node* jw118 = new Node("JW118", 1, 1, 1);
	Node* jw119 = new Node("JW119", 1, 1, 1);
	Node* jw120 = new Node("JW120", 1, 1, 1);
	Node* jw121 = new Node("JW121", 1, 1, 1);
	Node* jw122 = new Node("JW122", 1, 1, 1);
	Node* jw123 = new Node("JW123", 1, 1, 1);
	Node* jw124 = new Node("JW124", 1, 1, 1);
	Node* jw125 = new Node("JW125", 1, 1, 1);
	Node* jwtoilet101 = new Node("JWToilet101", 2, 1, 1);
	Node* jwtoilet102 = new Node("JWToilet102", 2, 1, 1);
	Node* jwstairs101 = new Node("JWStairs101", 3, 1, 1);
	Node* jwstairs102 = new Node("JWStairs102", 3, 1, 1);
	Node* jwlift101 = new Node("JWLift101", 4, 1, 1);
	Node* jwlift102 = new Node("JWLift102", 4, 1, 1);
	Node* jwlift103 = new Node("JWLift103", 4, 1, 1);
	Node* jwlift104 = new Node("JWLift104", 4, 1, 1); //total number of nodes : 33



	Edge* ejw101 = new Edge(jw101, jw102, 3);
	Edge* ejw102 = new Edge(jw101, jwstairs101, 1);
	Edge* ejw103 = new Edge(jw102, jwtoilet101, 4);
	Edge* ejw104 = new Edge(jwtoilet101, jwlift101, 10);
	Edge* ejw105 = new Edge(jwtoilet101, jw103, 3);
	Edge* ejw106 = new Edge(jw103, jw104, 3);
	Edge* ejw107 = new Edge(jw104, jw105, 3);
	Edge* ejw108 = new Edge(jw105, jwstairs102, 1);
	Edge* ejw109 = new Edge(jw105, jw106, 5);
	Edge* ejw110 = new Edge(jwstairs102, jw106, 6);
	Edge* ejw111 = new Edge(jw106, jw107, 3);
	Edge* ejw112 = new Edge(jw107, jw108, 3);
	Edge* ejw113 = new Edge(jw107, jw109, 10);
	Edge* ejw114 = new Edge(jw108, jw109, 9);
	Edge* ejw115 = new Edge(jw108, jw110, 3);
	Edge* ejw116 = new Edge(jw108, jwlift101, 10);
	Edge* ejw117 = new Edge(jw108, jwlift102, 10);
	Edge* ejw118 = new Edge(jwlift101, jwlift102, 2);
	Edge* ejw119 = new Edge(jw110, jw111, 6);
	Edge* ejw120 = new Edge(jw110, jwtoilet102, 5);
	Edge* ejw121 = new Edge(jw110, jwlift103, 7);
	Edge* ejw122 = new Edge(jwlift103, jwtoilet102, 2);
	Edge* ejw123 = new Edge(jwtoilet102, jw111, 9);
	Edge* ejw124 = new Edge(jwtoilet102, jw113, 1);
	Edge* ejw125 = new Edge(jw111, jw112, 2);
	Edge* ejw126 = new Edge(jw112, jw113, 6);
	Edge* ejw127 = new Edge(jw112, jw114, 5);
	Edge* ejw128 = new Edge(jw113, jw114, 5);
	Edge* ejw129 = new Edge(jw114, jw115, 2);
	Edge* ejw130 = new Edge(jw115, jw116, 2);
	Edge* ejw131 = new Edge(jw116, jw117, 2);
	Edge* ejw132 = new Edge(jw117, jw118, 4);
	Edge* ejw133 = new Edge(jw118, jw119, 1);
	Edge* ejw134 = new Edge(jw119, jw120, 7);
	Edge* ejw135 = new Edge(jw119, jw121, 7);
	Edge* ejw136 = new Edge(jw119, jwlift104, 10);
	Edge* ejw137 = new Edge(jwlift104, jw121, 11);
	Edge* ejw138 = new Edge(jw120, jw121, 2);
	Edge* ejw139 = new Edge(jw120, jw123, 3);
	Edge* ejw140 = new Edge(jw121, jw122, 4);
	Edge* ejw141 = new Edge(jw122, jw123, 1);
	Edge* ejw142 = new Edge(jw122, jw125, 3);
	Edge* ejw143 = new Edge(jw123, jw124, 3);
	Edge* ejw144 = new Edge(jw124, jw125, 1);
	Edge* ejw145 = new Edge(jw124, jwstairs101, 5);
	Edge* ejw146 = new Edge(jw125, jwstairs101, 6);


	//second floor of JW
	Node* jw201 = new Node("JW201", 1, 1, 1); //room 101, type room, JW building, floor 1
	Node* jw202 = new Node("JW202", 1, 1, 2);
	Node* jw203 = new Node("JW203", 1, 1, 2);
	Node* jw204 = new Node("JW204", 1, 1, 2);
	Node* jw205 = new Node("JW205", 1, 1, 2);
	Node* jw206 = new Node("JW206", 1, 1, 2);
	Node* jw207 = new Node("JW207", 1, 1, 2);
	Node* jw208 = new Node("JW208", 1, 1, 2);
	Node* jw209 = new Node("JW209", 1, 1, 2);
	Node* jw210 = new Node("JW210", 1, 1, 2);
	Node* jw211 = new Node("JW211", 1, 1, 2);
	Node* jw212 = new Node("JW212", 1, 1, 2);
	Node* jw213 = new Node("JW213", 1, 1, 2);
	Node* jw214 = new Node("JW214", 1, 1, 2);
	Node* jw215 = new Node("JW215", 1, 1, 2);
	Node* jw216 = new Node("JW216", 1, 1, 2);
	Node* jw217 = new Node("JW217", 1, 1, 2);
	Node* jw218 = new Node("JW218", 1, 1, 2);
	Node* jw219 = new Node("JW219", 1, 1, 2);
	Node* jw220 = new Node("JW220", 1, 1, 2);
	Node* jw221 = new Node("JW221", 1, 1, 2);
	Node* jw222 = new Node("JW222", 1, 1, 2);
	Node* jw223 = new Node("JW223", 1, 1, 2);
	Node* jw224 = new Node("JW224", 1, 1, 2);
	Node* jw225 = new Node("JW225", 1, 1, 2);
	Node* jwtoilet201 = new Node("JWToilet201", 2, 1, 2);
	Node* jwtoilet202 = new Node("JWToilet202", 2, 1, 2);
	Node* jwstairs201 = new Node("JWStairs201", 3, 1, 2);
	Node* jwstairs202 = new Node("JWStairs202", 3, 1, 2);
	Node* jwlift201 = new Node("JWLift201", 4, 1, 2);
	Node* jwlift202 = new Node("JWLift202", 4, 1, 2);
	Node* jwlift203 = new Node("JWLift203", 4, 1, 2);
	Node* jwlift204 = new Node("JWLift204", 4, 1, 2); //total number of nodes : 33


	Edge* ejw201 = new Edge(jw201, jw202, 3);
	Edge* ejw202 = new Edge(jw201, jwstairs201, 1);
	Edge* ejw203 = new Edge(jw202, jwtoilet201, 4);
	Edge* ejw204 = new Edge(jwtoilet201, jwlift201, 10);
	Edge* ejw205 = new Edge(jwtoilet201, jw203, 3);
	Edge* ejw206 = new Edge(jw203, jw204, 3);
	Edge* ejw207 = new Edge(jw204, jw205, 3);
	Edge* ejw208 = new Edge(jw205, jwstairs202, 1);
	Edge* ejw209 = new Edge(jw205, jw206, 5);
	Edge* ejw210 = new Edge(jwstairs202, jw206, 6);
	Edge* ejw211 = new Edge(jw206, jw207, 3);
	Edge* ejw212 = new Edge(jw207, jw208, 3);
	Edge* ejw213 = new Edge(jw207, jw209, 10);
	Edge* ejw214 = new Edge(jw208, jw209, 9);
	Edge* ejw215 = new Edge(jw208, jw210, 3);
	Edge* ejw216 = new Edge(jw208, jwlift201, 10);
	Edge* ejw217 = new Edge(jw208, jwlift202, 10);
	Edge* ejw218 = new Edge(jwlift201, jwlift202, 2);
	Edge* ejw219 = new Edge(jw210, jw211, 6);
	Edge* ejw220 = new Edge(jw210, jwtoilet202, 5);
	Edge* ejw221 = new Edge(jw210, jwlift203, 7);
	Edge* ejw222 = new Edge(jwlift203, jwtoilet202, 2);
	Edge* ejw223 = new Edge(jwtoilet202, jw211, 9);
	Edge* ejw224 = new Edge(jwtoilet202, jw213, 1);
	Edge* ejw225 = new Edge(jw211, jw212, 2);
	Edge* ejw226 = new Edge(jw212, jw213, 6);
	Edge* ejw227 = new Edge(jw212, jw214, 5);
	Edge* ejw228 = new Edge(jw213, jw214, 5);
	Edge* ejw229 = new Edge(jw214, jw215, 2);
	Edge* ejw230 = new Edge(jw215, jw216, 2);
	Edge* ejw231 = new Edge(jw216, jw217, 2);
	Edge* ejw232 = new Edge(jw217, jw218, 4);
	Edge* ejw233 = new Edge(jw218, jw219, 1);
	Edge* ejw234 = new Edge(jw219, jw220, 7);
	Edge* ejw235 = new Edge(jw219, jw221, 7);
	Edge* ejw236 = new Edge(jw219, jwlift204, 10);
	Edge* ejw237 = new Edge(jwlift204, jw221, 11);
	Edge* ejw238 = new Edge(jw220, jw221, 2);
	Edge* ejw239 = new Edge(jw220, jw223, 3);
	Edge* ejw240 = new Edge(jw221, jw222, 4);
	Edge* ejw241 = new Edge(jw222, jw223, 1);
	Edge* ejw242 = new Edge(jw222, jw225, 3);
	Edge* ejw243 = new Edge(jw223, jw224, 3);
	Edge* ejw244 = new Edge(jw224, jw225, 1);
	Edge* ejw245 = new Edge(jw224, jwstairs201, 5);
	Edge* ejw246 = new Edge(jw225, jwstairs201, 6);

	//third floor of JW
	Node* jw301 = new Node("JW301", 1, 1, 3); //room 101, type room, JW building, floor 1
	Node* jw302 = new Node("JW302", 1, 1, 3);
	Node* jw303 = new Node("JW303", 1, 1, 3);
	Node* jw304 = new Node("JW304", 1, 1, 3);
	Node* jw305 = new Node("JW305", 1, 1, 3);
	Node* jw306 = new Node("JW306", 1, 1, 3);
	Node* jw307 = new Node("JW307", 1, 1, 3);
	Node* jw308 = new Node("JW308", 1, 1, 3);
	Node* jw309 = new Node("JW309", 1, 1, 3);
	Node* jw310 = new Node("JW310", 1, 1, 3);
	Node* jw311 = new Node("JW311", 1, 1, 3);
	Node* jw312 = new Node("JW312", 1, 1, 3);
	Node* jw313 = new Node("JW313", 1, 1, 3);
	Node* jw314 = new Node("JW314", 1, 1, 3);
	Node* jw315 = new Node("JW315", 1, 1, 3);
	Node* jw316 = new Node("JW316", 1, 1, 3);
	Node* jw317 = new Node("JW317", 1, 1, 3);
	Node* jw318 = new Node("JW318", 1, 1, 3);
	Node* jw319 = new Node("JW319", 1, 1, 3);
	Node* jw320 = new Node("JW320", 1, 1, 3);
	Node* jw321 = new Node("JW321", 1, 1, 3);
	Node* jw322 = new Node("JW322", 1, 1, 3);
	Node* jw323 = new Node("JW323", 1, 1, 3);
	Node* jw324 = new Node("JW324", 1, 1, 3);
	Node* jw325 = new Node("JW325", 1, 1, 3);
	Node* jwtoilet301 = new Node("JWToilet301", 2, 1, 3);
	Node* jwtoilet302 = new Node("JWToilet302", 2, 1, 3);
	Node* jwstairs301 = new Node("JWStairs301", 3, 1, 3);
	Node* jwstairs302 = new Node("JWStairs302", 3, 1, 3);
	Node* jwlift301 = new Node("JWLift301", 4, 1, 3);
	Node* jwlift302 = new Node("JWLift302", 4, 1, 3);
	Node* jwlift303 = new Node("JWLift303", 4, 1, 3);
	Node* jwlift304 = new Node("JWLift304", 4, 1, 3);

	Node* jwconnector = new Node("JWConnector", 5, 1, 3); //total number of nodes : 34



	Edge* ejw301 = new Edge(jw301, jw302, 3);
	Edge* ejw302 = new Edge(jw301, jwstairs301, 1);
	Edge* ejw303 = new Edge(jw302, jwtoilet301, 4);
	Edge* ejw304 = new Edge(jwtoilet301, jwlift301, 10);
	Edge* ejw305 = new Edge(jwtoilet301, jw303, 3);
	Edge* ejw306 = new Edge(jw303, jw304, 3);
	Edge* ejw307 = new Edge(jw304, jw305, 3);
	Edge* ejw308 = new Edge(jw305, jwstairs302, 1);
	Edge* ejw309 = new Edge(jw305, jw306, 5);
	Edge* ejw310 = new Edge(jwstairs302, jw306, 6);
	Edge* ejw311 = new Edge(jw306, jw307, 3);
	Edge* ejw312 = new Edge(jw307, jw308, 3);
	Edge* ejw313 = new Edge(jw307, jw309, 10);
	Edge* ejw314 = new Edge(jw308, jw309, 9);
	Edge* ejw315 = new Edge(jw308, jw310, 3);
	Edge* ejw316 = new Edge(jw308, jwlift301, 10);
	Edge* ejw317 = new Edge(jw308, jwlift302, 10);
	Edge* ejw318 = new Edge(jwlift301, jwlift302, 2);
	Edge* ejw319 = new Edge(jw310, jw311, 6);
	Edge* ejw320 = new Edge(jw310, jwtoilet302, 5);
	Edge* ejw321 = new Edge(jw310, jwlift303, 7);
	Edge* ejw322 = new Edge(jwlift303, jwtoilet302, 2);
	Edge* ejw323 = new Edge(jwtoilet302, jw311, 9);
	Edge* ejw324 = new Edge(jwtoilet302, jw313, 1);
	Edge* ejw325 = new Edge(jw311, jw312, 2);
	Edge* ejw326 = new Edge(jw312, jw313, 6);
	Edge* ejw327 = new Edge(jw312, jw314, 5);
	Edge* ejw328 = new Edge(jw313, jw314, 5);
	Edge* ejw329 = new Edge(jw314, jw315, 2);
	Edge* ejw330 = new Edge(jw315, jw316, 2);
	Edge* ejw331 = new Edge(jw316, jw317, 2);
	Edge* ejw332 = new Edge(jw317, jw318, 4);
	Edge* ejw333 = new Edge(jw318, jw319, 1);
	Edge* ejw334 = new Edge(jw319, jw320, 7);
	Edge* ejw335 = new Edge(jw319, jw321, 7);
	Edge* ejw336 = new Edge(jw319, jwlift304, 10);
	Edge* ejw337 = new Edge(jwlift304, jw321, 11);
	Edge* ejw338 = new Edge(jw320, jw321, 2);
	Edge* ejw339 = new Edge(jw320, jw323, 3);
	Edge* ejw340 = new Edge(jw321, jw322, 4);
	Edge* ejw341 = new Edge(jw322, jw323, 1);
	Edge* ejw342 = new Edge(jw322, jw325, 3);
	Edge* ejw343 = new Edge(jw323, jw324, 3);
	Edge* ejw344 = new Edge(jw324, jw325, 1);
	Edge* ejw345 = new Edge(jw324, jwstairs301, 5);
	Edge* ejw346 = new Edge(jw325, jwstairs301, 6);
	Edge* ejw347 = new Edge(jwconnector, jwlift303, 1);
	Edge* ejw348 = new Edge(jwconnector, jwtoilet302, 1);


	///////////////////edges between lifts, stairs, and connectors
	//LIFTS AND STAIRS
	//JW first and second floor
	Edge* ejwlift101201 = new Edge(jwlift101, jwlift201, 1);//from jw lift 1 floor 1 --> lift 1 floor 2
	Edge* ejwlift102202 = new Edge(jwlift102, jwlift202, 1);//from jwlift 2 floor 1 --> lift 2 floor 2
	Edge* ejwlift103203 = new Edge(jwlift103, jwlift203, 1);//from jw lift 3 floor 1 --> lift 3 floor 2
	Edge* ejwlift104204 = new Edge(jwlift104, jwlift204, 1);//from jw lift 4 floor 1 --> lift 4 floor 2
	Edge* ejwstairs101201 = new Edge(jwstairs101, jwstairs201, 2);//jw stairs 1 floor 1-->stairs 1 floor 2
	Edge* ejwstairs102202 = new Edge(jwstairs102, jwstairs202, 2);//jw stairs 2 floor 1-->stairs2 floor 2
	//JW second and third floor
	Edge* ejwlift201301 = new Edge(jwlift201, jwlift301, 1);//from jw lift 1 floor 2 --> lift 1 floor 3
	Edge* ejwlift202302 = new Edge(jwlift202, jwlift302, 1);//from jwlift 2 floor 2 --> lift 2 floor 3
	Edge* ejwlift203303 = new Edge(jwlift203, jwlift303, 1);//from jw lift 3 floor 2 --> lift 3 floor 3
	Edge* ejwlift204304 = new Edge(jwlift204, jwlift304, 1);//from jw lift 4 floor 2 --> lift 4 floor 3
	Edge* ejwstairs201301 = new Edge(jwstairs201, jwstairs301, 2);//jw stairs 1 floor 2-->stairs 1 floor 3
	Edge* ejwstairs202302 = new Edge(jwstairs202, jwstairs302, 2);//jw stairs 2 floor 2-->stairs2 floor 3
	//CONNECTORS
	/*Edge* ejwrc = new Edge(jwconnector, rcconnector, 5);
	Edge* ejwtg = new Edge(jwconnector, tgconnector, 5);
	Edge* erctg = new Edge(rcconnector, tgconnector, 5);*/




	///////////////////////////////////start of user input phase
	/*cout << "Input the starting point id: " << endl;
	Node* begin = setStartingPoint(); //user inputs starting node "begin"
	begin->distanceFromStart = 0; // set starting point


	cout << "Input destination point id: " << endl;
	Node* end = setDestinationPoint(); //user inputs destination node "end"*/



	cout << "Input starting point id: " << endl;
	int startID = setStartingPoint();
	nodes.at(startID)->distanceFromStart = 0; // set beginning

	cout << "Input the destination point: " << endl;
	int destinationID = setDestinationPoint();

									   
								
	Dijkstras();
	//PrintShortestRouteTo(end); //print shortest route to end node
	PrintShortestRouteTo(nodesFINAL.at(destinationID)); //set end node
	system("pause");

}

///////////////////

void Dijkstras()
{
	while (nodes.size() > 0)
	{
		Node* smallest = ExtractSmallest(nodes);
		vector<Node*>* adjacentNodes =
			AdjacentRemainingNodes(smallest);

		const int size = adjacentNodes->size();
		for (int i = 0; i<size; ++i)
		{
			Node* adjacent = adjacentNodes->at(i);
			int distance = Distance(smallest, adjacent) +
				smallest->distanceFromStart;

			if (distance < adjacent->distanceFromStart)
			{
				adjacent->distanceFromStart = distance;
				adjacent->previous = smallest;
			}
		}
		delete adjacentNodes;
	}
}

// Find the node with the smallest distance,
// remove it, and return it.
Node* ExtractSmallest(vector<Node*>& nodes)
{
	int size = nodes.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Node* smallest = nodes.at(0);
	for (int i = 1; i<size; ++i)
	{
		Node* current = nodes.at(i);
		if (current->distanceFromStart <
			smallest->distanceFromStart)
		{
			smallest = current;
			smallestPosition = i;
		}
	}
	nodes.erase(nodes.begin() + smallestPosition);
	return smallest;
}

// Return all nodes adjacent to 'node' which are still
// in the 'nodes' collection.
vector<Node*>* AdjacentRemainingNodes(Node* node)
{
	vector<Node*>* adjacentNodes = new vector<Node*>();
	const int size = edges.size();
	for (int i = 0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		Node* adjacent = NULL;
		if (edge->node1 == node)
		{
			adjacent = edge->node2;
		}
		else if (edge->node2 == node)
		{
			adjacent = edge->node1;
		}
		if (adjacent && Contains(nodes, adjacent))
		{
			adjacentNodes->push_back(adjacent);
		}
	}
	return adjacentNodes;
}

// Return distance between two connected nodes
int Distance(Node* node1, Node* node2)
{
	const int size = edges.size();
	for (int i = 0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->Connects(node1, node2))
		{
			return edge->distance;
		}
	}
	return -1; // should never happen
}

// Does the 'nodes' vector contain 'node'
bool Contains(vector<Node*>& nodes, Node* node)
{
	const int size = nodes.size();
	for (int i = 0; i<size; ++i)
	{
		if (node == nodes.at(i))
		{
			return true;
		}
	}
	return false;
}

///////////////////

void PrintShortestRouteTo(Node* destination)
{
	Node* previous = destination;
	cout << "Distance from start: "
		<< destination->distanceFromStart + 1 << endl; //added +1
	while (previous)
	{

		steps.push_back(previous->id.c_str()); //add all steps of the journey to the "steps" vector
		previous = previous->previous;
	}

	int size = steps.size();
	for (int i = size-1; i >= 0; i--) // to print the steps NOT backwards
	{
		cout << steps[i].c_str() << " ";
	}
	
	cout << endl;
}







// these two not needed
vector<Edge*>* AdjacentEdges(vector<Edge*>& Edges, Node* node);
void RemoveEdge(vector<Edge*>& Edges, Edge* edge);

vector<Edge*>* AdjacentEdges(vector<Edge*>& edges, Node* node)
{
	vector<Edge*>* adjacentEdges = new vector<Edge*>();

	const int size = edges.size();
	for (int i = 0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->node1 == node)
		{
			cout << "adjacent: " << edge->node2->id.c_str() << endl;
			adjacentEdges->push_back(edge);
		}
		else if (edge->node2 == node)
		{
			cout << "adjacent: " << edge->node1->id.c_str() << endl;
			adjacentEdges->push_back(edge);
		}
	}
	return adjacentEdges;
}

void RemoveEdge(vector<Edge*>& edges, Edge* edge)
{
	vector<Edge*>::iterator it;
	for (it = edges.begin(); it<edges.end(); ++it)
	{
		if (*it == edge)
		{
			edges.erase(it);
			return;
		}
	}
}
