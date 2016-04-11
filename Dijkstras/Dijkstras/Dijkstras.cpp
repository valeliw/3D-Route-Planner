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

	//first floor of RC
	Node* rc101 = new Node("RC101", 1, 1, 1); //room 101, type room, RC building, floor 1
	Node* rc102 = new Node("RC102", 1, 1, 1);
	Node* rc103 = new Node("RC103", 1, 1, 1);
	Node* rc104 = new Node("RC104", 1, 1, 1);
	Node* rc105 = new Node("RC105", 1, 1, 1);
	Node* rc106 = new Node("RC106", 1, 1, 1);
	Node* rc107 = new Node("RC107", 1, 1, 1);
	Node* rc108 = new Node("RC108", 1, 1, 1);
	Node* rc109 = new Node("RC109", 1, 1, 1);
	Node* rc110 = new Node("RC110", 1, 1, 1);
	Node* rc111 = new Node("RC111", 1, 1, 1);
	Node* rc112 = new Node("RC112", 1, 1, 1);
	Node* rc113 = new Node("RC113", 1, 1, 1);
	Node* rc114 = new Node("RC114", 1, 1, 1);
	Node* rc115 = new Node("RC115", 1, 1, 1);
	Node* rc116 = new Node("RC116", 1, 1, 1);
	Node* rc117 = new Node("RC117", 1, 1, 1);
	Node* rc118 = new Node("RC118", 1, 1, 1);
	Node* rc119 = new Node("RC119", 1, 1, 1);
	Node* rc120 = new Node("RC120", 1, 1, 1);
	Node* rc121 = new Node("RC121", 1, 1, 1);
	Node* rc122 = new Node("RC122", 1, 1, 1);
	Node* rc123 = new Node("RC123", 1, 1, 1);
	Node* rc124 = new Node("RC124", 1, 1, 1);
	Node* rc125 = new Node("RC125", 1, 1, 1);
	Node* rctoilet101 = new Node("RCToilet101", 2, 1, 1);
	Node* rctoilet102 = new Node("RCToilet102", 2, 1, 1);
	Node* rcstairs101 = new Node("RCStairs101", 3, 1, 1);
	Node* rcstairs102 = new Node("RCStairs102", 3, 1, 1);
	Node* rclift101 = new Node("RCLift101", 4, 1, 1);
	Node* rclift102 = new Node("RCLift102", 4, 1, 1);
	Node* rclift103 = new Node("RCLift103", 4, 1, 1);
	Node* rclift104 = new Node("RCLift104", 4, 1, 1); //total number of nodes : 33



	Edge* erc101 = new Edge(rc101, rc102, 3);
	Edge* erc102 = new Edge(rc101, rcstairs101, 1);
	Edge* erc103 = new Edge(rc102, rctoilet101, 4);
	Edge* erc104 = new Edge(rctoilet101, rclift101, 10);
	Edge* erc105 = new Edge(rctoilet101, rc103, 3);
	Edge* erc106 = new Edge(rc103, rc104, 3);
	Edge* erc107 = new Edge(rc104, rc105, 3);
	Edge* erc108 = new Edge(rc105, rcstairs102, 1);
	Edge* erc109 = new Edge(rc105, rc106, 5);
	Edge* erc110 = new Edge(rcstairs102, rc106, 6);
	Edge* erc111 = new Edge(rc106, rc107, 3);
	Edge* erc112 = new Edge(rc107, rc108, 3);
	Edge* erc113 = new Edge(rc107, rc109, 10);
	Edge* erc114 = new Edge(rc108, rc109, 9);
	Edge* erc115 = new Edge(rc108, rc110, 3);
	Edge* erc116 = new Edge(rc108, rclift101, 10);
	Edge* erc117 = new Edge(rc108, rclift102, 10);
	Edge* erc118 = new Edge(rclift101, rclift102, 2);
	Edge* erc119 = new Edge(rc110, rc111, 6);
	Edge* erc120 = new Edge(rc110, rctoilet102, 5);
	Edge* erc121 = new Edge(rc110, rclift103, 7);
	Edge* erc122 = new Edge(rclift103, rctoilet102, 2);
	Edge* erc123 = new Edge(rctoilet102, rc111, 9);
	Edge* erc124 = new Edge(rctoilet102, rc113, 1);
	Edge* erc125 = new Edge(rc111, rc112, 2);
	Edge* erc126 = new Edge(rc112, rc113, 6);
	Edge* erc127 = new Edge(rc112, rc114, 5);
	Edge* erc128 = new Edge(rc113, rc114, 5);
	Edge* erc129 = new Edge(rc114, rc115, 2);
	Edge* erc130 = new Edge(rc115, rc116, 2);
	Edge* erc131 = new Edge(rc116, rc117, 2);
	Edge* erc132 = new Edge(rc117, rc118, 4);
	Edge* erc133 = new Edge(rc118, rc119, 1);
	Edge* erc134 = new Edge(rc119, rc120, 7);
	Edge* erc135 = new Edge(rc119, rc121, 7);
	Edge* erc136 = new Edge(rc119, rclift104, 10);
	Edge* erc137 = new Edge(rclift104, rc121, 11);
	Edge* erc138 = new Edge(rc120, rc121, 2);
	Edge* erc139 = new Edge(rc120, rc123, 3);
	Edge* erc140 = new Edge(rc121, rc122, 4);
	Edge* erc141 = new Edge(rc122, rc123, 1);
	Edge* erc142 = new Edge(rc122, rc125, 3);
	Edge* erc143 = new Edge(rc123, rc124, 3);
	Edge* erc144 = new Edge(rc124, rc125, 1);
	Edge* erc145 = new Edge(rc124, rcstairs101, 5);
	Edge* erc146 = new Edge(rc125, rcstairs101, 6);


	//second floor of RC
	Node* rc201 = new Node("RC201", 1, 1, 1); //room 101, type room, RC building, floor 1
	Node* rc202 = new Node("RC202", 1, 1, 2);
	Node* rc203 = new Node("RC203", 1, 1, 2);
	Node* rc204 = new Node("RC204", 1, 1, 2);
	Node* rc205 = new Node("RC205", 1, 1, 2);
	Node* rc206 = new Node("RC206", 1, 1, 2);
	Node* rc207 = new Node("RC207", 1, 1, 2);
	Node* rc208 = new Node("RC208", 1, 1, 2);
	Node* rc209 = new Node("RC209", 1, 1, 2);
	Node* rc210 = new Node("RC210", 1, 1, 2);
	Node* rc211 = new Node("RC211", 1, 1, 2);
	Node* rc212 = new Node("RC212", 1, 1, 2);
	Node* rc213 = new Node("RC213", 1, 1, 2);
	Node* rc214 = new Node("RC214", 1, 1, 2);
	Node* rc215 = new Node("RC215", 1, 1, 2);
	Node* rc216 = new Node("RC216", 1, 1, 2);
	Node* rc217 = new Node("RC217", 1, 1, 2);
	Node* rc218 = new Node("RC218", 1, 1, 2);
	Node* rc219 = new Node("RC219", 1, 1, 2);
	Node* rc220 = new Node("RC220", 1, 1, 2);
	Node* rc221 = new Node("RC221", 1, 1, 2);
	Node* rc222 = new Node("RC222", 1, 1, 2);
	Node* rc223 = new Node("RC223", 1, 1, 2);
	Node* rc224 = new Node("RC224", 1, 1, 2);
	Node* rc225 = new Node("RC225", 1, 1, 2);
	Node* rctoilet201 = new Node("RCToilet201", 2, 1, 2);
	Node* rctoilet202 = new Node("RCToilet202", 2, 1, 2);
	Node* rcstairs201 = new Node("RCStairs201", 3, 1, 2);
	Node* rcstairs202 = new Node("RCStairs202", 3, 1, 2);
	Node* rclift201 = new Node("RCLift201", 4, 1, 2);
	Node* rclift202 = new Node("RCLift202", 4, 1, 2);
	Node* rclift203 = new Node("RCLift203", 4, 1, 2);
	Node* rclift204 = new Node("RCLift204", 4, 1, 2); //total number of nodes : 33


	Edge* erc201 = new Edge(rc201, rc202, 3);
	Edge* erc202 = new Edge(rc201, rcstairs201, 1);
	Edge* erc203 = new Edge(rc202, rctoilet201, 4);
	Edge* erc204 = new Edge(rctoilet201, rclift201, 10);
	Edge* erc205 = new Edge(rctoilet201, rc203, 3);
	Edge* erc206 = new Edge(rc203, rc204, 3);
	Edge* erc207 = new Edge(rc204, rc205, 3);
	Edge* erc208 = new Edge(rc205, rcstairs202, 1);
	Edge* erc209 = new Edge(rc205, rc206, 5);
	Edge* erc210 = new Edge(rcstairs202, rc206, 6);
	Edge* erc211 = new Edge(rc206, rc207, 3);
	Edge* erc212 = new Edge(rc207, rc208, 3);
	Edge* erc213 = new Edge(rc207, rc209, 10);
	Edge* erc214 = new Edge(rc208, rc209, 9);
	Edge* erc215 = new Edge(rc208, rc210, 3);
	Edge* erc216 = new Edge(rc208, rclift201, 10);
	Edge* erc217 = new Edge(rc208, rclift202, 10);
	Edge* erc218 = new Edge(rclift201, rclift202, 2);
	Edge* erc219 = new Edge(rc210, rc211, 6);
	Edge* erc220 = new Edge(rc210, rctoilet202, 5);
	Edge* erc221 = new Edge(rc210, rclift203, 7);
	Edge* erc222 = new Edge(rclift203, rctoilet202, 2);
	Edge* erc223 = new Edge(rctoilet202, rc211, 9);
	Edge* erc224 = new Edge(rctoilet202, rc213, 1);
	Edge* erc225 = new Edge(rc211, rc212, 2);
	Edge* erc226 = new Edge(rc212, rc213, 6);
	Edge* erc227 = new Edge(rc212, rc214, 5);
	Edge* erc228 = new Edge(rc213, rc214, 5);
	Edge* erc229 = new Edge(rc214, rc215, 2);
	Edge* erc230 = new Edge(rc215, rc216, 2);
	Edge* erc231 = new Edge(rc216, rc217, 2);
	Edge* erc232 = new Edge(rc217, rc218, 4);
	Edge* erc233 = new Edge(rc218, rc219, 1);
	Edge* erc234 = new Edge(rc219, rc220, 7);
	Edge* erc235 = new Edge(rc219, rc221, 7);
	Edge* erc236 = new Edge(rc219, rclift204, 10);
	Edge* erc237 = new Edge(rclift204, rc221, 11);
	Edge* erc238 = new Edge(rc220, rc221, 2);
	Edge* erc239 = new Edge(rc220, rc223, 3);
	Edge* erc240 = new Edge(rc221, rc222, 4);
	Edge* erc241 = new Edge(rc222, rc223, 1);
	Edge* erc242 = new Edge(rc222, rc225, 3);
	Edge* erc243 = new Edge(rc223, rc224, 3);
	Edge* erc244 = new Edge(rc224, rc225, 1);
	Edge* erc245 = new Edge(rc224, rcstairs201, 5);
	Edge* erc246 = new Edge(rc225, rcstairs201, 6);

	//third floor of RC
	Node* rc301 = new Node("RC301", 1, 1, 3); //room 101, type room, RC building, floor 1
	Node* rc302 = new Node("RC302", 1, 1, 3);
	Node* rc303 = new Node("RC303", 1, 1, 3);
	Node* rc304 = new Node("RC304", 1, 1, 3);
	Node* rc305 = new Node("RC305", 1, 1, 3);
	Node* rc306 = new Node("RC306", 1, 1, 3);
	Node* rc307 = new Node("RC307", 1, 1, 3);
	Node* rc308 = new Node("RC308", 1, 1, 3);
	Node* rc309 = new Node("RC309", 1, 1, 3);
	Node* rc310 = new Node("RC310", 1, 1, 3);
	Node* rc311 = new Node("RC311", 1, 1, 3);
	Node* rc312 = new Node("RC312", 1, 1, 3);
	Node* rc313 = new Node("RC313", 1, 1, 3);
	Node* rc314 = new Node("RC314", 1, 1, 3);
	Node* rc315 = new Node("RC315", 1, 1, 3);
	Node* rc316 = new Node("RC316", 1, 1, 3);
	Node* rc317 = new Node("RC317", 1, 1, 3);
	Node* rc318 = new Node("RC318", 1, 1, 3);
	Node* rc319 = new Node("RC319", 1, 1, 3);
	Node* rc320 = new Node("RC320", 1, 1, 3);
	Node* rc321 = new Node("RC321", 1, 1, 3);
	Node* rc322 = new Node("RC322", 1, 1, 3);
	Node* rc323 = new Node("RC323", 1, 1, 3);
	Node* rc324 = new Node("RC324", 1, 1, 3);
	Node* rc325 = new Node("RC325", 1, 1, 3);
	Node* rctoilet301 = new Node("RCToilet301", 2, 1, 3);
	Node* rctoilet302 = new Node("RCToilet302", 2, 1, 3);
	Node* rcstairs301 = new Node("RCStairs301", 3, 1, 3);
	Node* rcstairs302 = new Node("RCStairs302", 3, 1, 3);
	Node* rclift301 = new Node("RCLift301", 4, 1, 3);
	Node* rclift302 = new Node("RCLift302", 4, 1, 3);
	Node* rclift303 = new Node("RCLift303", 4, 1, 3);
	Node* rclift304 = new Node("RCLift304", 4, 1, 3);

	Node* rcconnector = new Node("RCConnector", 5, 1, 3); //total number of nodes : 34



	Edge* erc301 = new Edge(rc301, rc302, 3);
	Edge* erc302 = new Edge(rc301, rcstairs301, 1);
	Edge* erc303 = new Edge(rc302, rctoilet301, 4);
	Edge* erc304 = new Edge(rctoilet301, rclift301, 10);
	Edge* erc305 = new Edge(rctoilet301, rc303, 3);
	Edge* erc306 = new Edge(rc303, rc304, 3);
	Edge* erc307 = new Edge(rc304, rc305, 3);
	Edge* erc308 = new Edge(rc305, rcstairs302, 1);
	Edge* erc309 = new Edge(rc305, rc306, 5);
	Edge* erc310 = new Edge(rcstairs302, rc306, 6);
	Edge* erc311 = new Edge(rc306, rc307, 3);
	Edge* erc312 = new Edge(rc307, rc308, 3);
	Edge* erc313 = new Edge(rc307, rc309, 10);
	Edge* erc314 = new Edge(rc308, rc309, 9);
	Edge* erc315 = new Edge(rc308, rc310, 3);
	Edge* erc316 = new Edge(rc308, rclift301, 10);
	Edge* erc317 = new Edge(rc308, rclift302, 10);
	Edge* erc318 = new Edge(rclift301, rclift302, 2);
	Edge* erc319 = new Edge(rc310, rc311, 6);
	Edge* erc320 = new Edge(rc310, rctoilet302, 5);
	Edge* erc321 = new Edge(rc310, rclift303, 7);
	Edge* erc322 = new Edge(rclift303, rctoilet302, 2);
	Edge* erc323 = new Edge(rctoilet302, rc311, 9);
	Edge* erc324 = new Edge(rctoilet302, rc313, 1);
	Edge* erc325 = new Edge(rc311, rc312, 2);
	Edge* erc326 = new Edge(rc312, rc313, 6);
	Edge* erc327 = new Edge(rc312, rc314, 5);
	Edge* erc328 = new Edge(rc313, rc314, 5);
	Edge* erc329 = new Edge(rc314, rc315, 2);
	Edge* erc330 = new Edge(rc315, rc316, 2);
	Edge* erc331 = new Edge(rc316, rc317, 2);
	Edge* erc332 = new Edge(rc317, rc318, 4);
	Edge* erc333 = new Edge(rc318, rc319, 1);
	Edge* erc334 = new Edge(rc319, rc320, 7);
	Edge* erc335 = new Edge(rc319, rc321, 7);
	Edge* erc336 = new Edge(rc319, rclift304, 10);
	Edge* erc337 = new Edge(rclift304, rc321, 11);
	Edge* erc338 = new Edge(rc320, rc321, 2);
	Edge* erc339 = new Edge(rc320, rc323, 3);
	Edge* erc340 = new Edge(rc321, rc322, 4);
	Edge* erc341 = new Edge(rc322, rc323, 1);
	Edge* erc342 = new Edge(rc322, rc325, 3);
	Edge* erc343 = new Edge(rc323, rc324, 3);
	Edge* erc344 = new Edge(rc324, rc325, 1);
	Edge* erc345 = new Edge(rc324, rcstairs301, 5);
	Edge* erc346 = new Edge(rc325, rcstairs301, 6);
	Edge* erc347 = new Edge(rcconnector, rclift303, 1);
	Edge* erc348 = new Edge(rcconnector, rctoilet302, 1);

	//first floor of TG
	Node* tg101 = new Node("TG101", 1, 1, 1); //room 101, type room, TG building, floor 1
	Node* tg102 = new Node("TG102", 1, 1, 1);
	Node* tg103 = new Node("TG103", 1, 1, 1);
	Node* tg104 = new Node("TG104", 1, 1, 1);
	Node* tg105 = new Node("TG105", 1, 1, 1);
	Node* tg106 = new Node("TG106", 1, 1, 1);
	Node* tg107 = new Node("TG107", 1, 1, 1);
	Node* tg108 = new Node("TG108", 1, 1, 1);
	Node* tg109 = new Node("TG109", 1, 1, 1);
	Node* tg110 = new Node("TG110", 1, 1, 1);
	Node* tg111 = new Node("TG111", 1, 1, 1);
	Node* tg112 = new Node("TG112", 1, 1, 1);
	Node* tg113 = new Node("TG113", 1, 1, 1);
	Node* tg114 = new Node("TG114", 1, 1, 1);
	Node* tg115 = new Node("TG115", 1, 1, 1);
	Node* tg116 = new Node("TG116", 1, 1, 1);
	Node* tg117 = new Node("TG117", 1, 1, 1);
	Node* tg118 = new Node("TG118", 1, 1, 1);
	Node* tg119 = new Node("TG119", 1, 1, 1);
	Node* tg120 = new Node("TG120", 1, 1, 1);
	Node* tg121 = new Node("TG121", 1, 1, 1);
	Node* tg122 = new Node("TG122", 1, 1, 1);
	Node* tg123 = new Node("TG123", 1, 1, 1);
	Node* tg124 = new Node("TG124", 1, 1, 1);
	Node* tg125 = new Node("TG125", 1, 1, 1);
	Node* tgtoilet101 = new Node("TGToilet101", 2, 1, 1);
	Node* tgtoilet102 = new Node("TGToilet102", 2, 1, 1);
	Node* tgstairs101 = new Node("TGStairs101", 3, 1, 1);
	Node* tgstairs102 = new Node("TGStairs102", 3, 1, 1);
	Node* tglift101 = new Node("TGLift101", 4, 1, 1);
	Node* tglift102 = new Node("TGLift102", 4, 1, 1);
	Node* tglift103 = new Node("TGLift103", 4, 1, 1);
	Node* tglift104 = new Node("TGLift104", 4, 1, 1); //total number of nodes : 33



	Edge* etg101 = new Edge(tg101, tg102, 3);
	Edge* etg102 = new Edge(tg101, tgstairs101, 1);
	Edge* etg103 = new Edge(tg102, tgtoilet101, 4);
	Edge* etg104 = new Edge(tgtoilet101, tglift101, 10);
	Edge* etg105 = new Edge(tgtoilet101, tg103, 3);
	Edge* etg106 = new Edge(tg103, tg104, 3);
	Edge* etg107 = new Edge(tg104, tg105, 3);
	Edge* etg108 = new Edge(tg105, tgstairs102, 1);
	Edge* etg109 = new Edge(tg105, tg106, 5);
	Edge* etg110 = new Edge(tgstairs102, tg106, 6);
	Edge* etg111 = new Edge(tg106, tg107, 3);
	Edge* etg112 = new Edge(tg107, tg108, 3);
	Edge* etg113 = new Edge(tg107, tg109, 10);
	Edge* etg114 = new Edge(tg108, tg109, 9);
	Edge* etg115 = new Edge(tg108, tg110, 3);
	Edge* etg116 = new Edge(tg108, tglift101, 10);
	Edge* etg117 = new Edge(tg108, tglift102, 10);
	Edge* etg118 = new Edge(tglift101, tglift102, 2);
	Edge* etg119 = new Edge(tg110, tg111, 6);
	Edge* etg120 = new Edge(tg110, tgtoilet102, 5);
	Edge* etg121 = new Edge(tg110, tglift103, 7);
	Edge* etg122 = new Edge(tglift103, tgtoilet102, 2);
	Edge* etg123 = new Edge(tgtoilet102, tg111, 9);
	Edge* etg124 = new Edge(tgtoilet102, tg113, 1);
	Edge* etg125 = new Edge(tg111, tg112, 2);
	Edge* etg126 = new Edge(tg112, tg113, 6);
	Edge* etg127 = new Edge(tg112, tg114, 5);
	Edge* etg128 = new Edge(tg113, tg114, 5);
	Edge* etg129 = new Edge(tg114, tg115, 2);
	Edge* etg130 = new Edge(tg115, tg116, 2);
	Edge* etg131 = new Edge(tg116, tg117, 2);
	Edge* etg132 = new Edge(tg117, tg118, 4);
	Edge* etg133 = new Edge(tg118, tg119, 1);
	Edge* etg134 = new Edge(tg119, tg120, 7);
	Edge* etg135 = new Edge(tg119, tg121, 7);
	Edge* etg136 = new Edge(tg119, tglift104, 10);
	Edge* etg137 = new Edge(tglift104, tg121, 11);
	Edge* etg138 = new Edge(tg120, tg121, 2);
	Edge* etg139 = new Edge(tg120, tg123, 3);
	Edge* etg140 = new Edge(tg121, tg122, 4);
	Edge* etg141 = new Edge(tg122, tg123, 1);
	Edge* etg142 = new Edge(tg122, tg125, 3);
	Edge* etg143 = new Edge(tg123, tg124, 3);
	Edge* etg144 = new Edge(tg124, tg125, 1);
	Edge* etg145 = new Edge(tg124, tgstairs101, 5);
	Edge* etg146 = new Edge(tg125, tgstairs101, 6);


	//second floor of TG
	Node* tg201 = new Node("TG201", 1, 1, 1); //room 101, type room, TG building, floor 1
	Node* tg202 = new Node("TG202", 1, 1, 2);
	Node* tg203 = new Node("TG203", 1, 1, 2);
	Node* tg204 = new Node("TG204", 1, 1, 2);
	Node* tg205 = new Node("TG205", 1, 1, 2);
	Node* tg206 = new Node("TG206", 1, 1, 2);
	Node* tg207 = new Node("TG207", 1, 1, 2);
	Node* tg208 = new Node("TG208", 1, 1, 2);
	Node* tg209 = new Node("TG209", 1, 1, 2);
	Node* tg210 = new Node("TG210", 1, 1, 2);
	Node* tg211 = new Node("TG211", 1, 1, 2);
	Node* tg212 = new Node("TG212", 1, 1, 2);
	Node* tg213 = new Node("TG213", 1, 1, 2);
	Node* tg214 = new Node("TG214", 1, 1, 2);
	Node* tg215 = new Node("TG215", 1, 1, 2);
	Node* tg216 = new Node("TG216", 1, 1, 2);
	Node* tg217 = new Node("TG217", 1, 1, 2);
	Node* tg218 = new Node("TG218", 1, 1, 2);
	Node* tg219 = new Node("TG219", 1, 1, 2);
	Node* tg220 = new Node("TG220", 1, 1, 2);
	Node* tg221 = new Node("TG221", 1, 1, 2);
	Node* tg222 = new Node("TG222", 1, 1, 2);
	Node* tg223 = new Node("TG223", 1, 1, 2);
	Node* tg224 = new Node("TG224", 1, 1, 2);
	Node* tg225 = new Node("TG225", 1, 1, 2);
	Node* tgtoilet201 = new Node("TGToilet201", 2, 1, 2);
	Node* tgtoilet202 = new Node("TGToilet202", 2, 1, 2);
	Node* tgstairs201 = new Node("TGStairs201", 3, 1, 2);
	Node* tgstairs202 = new Node("TGStairs202", 3, 1, 2);
	Node* tglift201 = new Node("TGLift201", 4, 1, 2);
	Node* tglift202 = new Node("TGLift202", 4, 1, 2);
	Node* tglift203 = new Node("TGLift203", 4, 1, 2);
	Node* tglift204 = new Node("TGLift204", 4, 1, 2); //total number of nodes : 33


	Edge* etg201 = new Edge(tg201, tg202, 3);
	Edge* etg202 = new Edge(tg201, tgstairs201, 1);
	Edge* etg203 = new Edge(tg202, tgtoilet201, 4);
	Edge* etg204 = new Edge(tgtoilet201, tglift201, 10);
	Edge* etg205 = new Edge(tgtoilet201, tg203, 3);
	Edge* etg206 = new Edge(tg203, tg204, 3);
	Edge* etg207 = new Edge(tg204, tg205, 3);
	Edge* etg208 = new Edge(tg205, tgstairs202, 1);
	Edge* etg209 = new Edge(tg205, tg206, 5);
	Edge* etg210 = new Edge(tgstairs202, tg206, 6);
	Edge* etg211 = new Edge(tg206, tg207, 3);
	Edge* etg212 = new Edge(tg207, tg208, 3);
	Edge* etg213 = new Edge(tg207, tg209, 10);
	Edge* etg214 = new Edge(tg208, tg209, 9);
	Edge* etg215 = new Edge(tg208, tg210, 3);
	Edge* etg216 = new Edge(tg208, tglift201, 10);
	Edge* etg217 = new Edge(tg208, tglift202, 10);
	Edge* etg218 = new Edge(tglift201, tglift202, 2);
	Edge* etg219 = new Edge(tg210, tg211, 6);
	Edge* etg220 = new Edge(tg210, tgtoilet202, 5);
	Edge* etg221 = new Edge(tg210, tglift203, 7);
	Edge* etg222 = new Edge(tglift203, tgtoilet202, 2);
	Edge* etg223 = new Edge(tgtoilet202, tg211, 9);
	Edge* etg224 = new Edge(tgtoilet202, tg213, 1);
	Edge* etg225 = new Edge(tg211, tg212, 2);
	Edge* etg226 = new Edge(tg212, tg213, 6);
	Edge* etg227 = new Edge(tg212, tg214, 5);
	Edge* etg228 = new Edge(tg213, tg214, 5);
	Edge* etg229 = new Edge(tg214, tg215, 2);
	Edge* etg230 = new Edge(tg215, tg216, 2);
	Edge* etg231 = new Edge(tg216, tg217, 2);
	Edge* etg232 = new Edge(tg217, tg218, 4);
	Edge* etg233 = new Edge(tg218, tg219, 1);
	Edge* etg234 = new Edge(tg219, tg220, 7);
	Edge* etg235 = new Edge(tg219, tg221, 7);
	Edge* etg236 = new Edge(tg219, tglift204, 10);
	Edge* etg237 = new Edge(tglift204, tg221, 11);
	Edge* etg238 = new Edge(tg220, tg221, 2);
	Edge* etg239 = new Edge(tg220, tg223, 3);
	Edge* etg240 = new Edge(tg221, tg222, 4);
	Edge* etg241 = new Edge(tg222, tg223, 1);
	Edge* etg242 = new Edge(tg222, tg225, 3);
	Edge* etg243 = new Edge(tg223, tg224, 3);
	Edge* etg244 = new Edge(tg224, tg225, 1);
	Edge* etg245 = new Edge(tg224, tgstairs201, 5);
	Edge* etg246 = new Edge(tg225, tgstairs201, 6);

	//third floor of TG
	Node* tg301 = new Node("TG301", 1, 1, 3); //room 101, type room, TG building, floor 1
	Node* tg302 = new Node("TG302", 1, 1, 3);
	Node* tg303 = new Node("TG303", 1, 1, 3);
	Node* tg304 = new Node("TG304", 1, 1, 3);
	Node* tg305 = new Node("TG305", 1, 1, 3);
	Node* tg306 = new Node("TG306", 1, 1, 3);
	Node* tg307 = new Node("TG307", 1, 1, 3);
	Node* tg308 = new Node("TG308", 1, 1, 3);
	Node* tg309 = new Node("TG309", 1, 1, 3);
	Node* tg310 = new Node("TG310", 1, 1, 3);
	Node* tg311 = new Node("TG311", 1, 1, 3);
	Node* tg312 = new Node("TG312", 1, 1, 3);
	Node* tg313 = new Node("TG313", 1, 1, 3);
	Node* tg314 = new Node("TG314", 1, 1, 3);
	Node* tg315 = new Node("TG315", 1, 1, 3);
	Node* tg316 = new Node("TG316", 1, 1, 3);
	Node* tg317 = new Node("TG317", 1, 1, 3);
	Node* tg318 = new Node("TG318", 1, 1, 3);
	Node* tg319 = new Node("TG319", 1, 1, 3);
	Node* tg320 = new Node("TG320", 1, 1, 3);
	Node* tg321 = new Node("TG321", 1, 1, 3);
	Node* tg322 = new Node("TG322", 1, 1, 3);
	Node* tg323 = new Node("TG323", 1, 1, 3);
	Node* tg324 = new Node("TG324", 1, 1, 3);
	Node* tg325 = new Node("TG325", 1, 1, 3);
	Node* tgtoilet301 = new Node("TGToilet301", 2, 1, 3);
	Node* tgtoilet302 = new Node("TGToilet302", 2, 1, 3);
	Node* tgstairs301 = new Node("TGStairs301", 3, 1, 3);
	Node* tgstairs302 = new Node("TGStairs302", 3, 1, 3);
	Node* tglift301 = new Node("TGLift301", 4, 1, 3);
	Node* tglift302 = new Node("TGLift302", 4, 1, 3);
	Node* tglift303 = new Node("TGLift303", 4, 1, 3);
	Node* tglift304 = new Node("TGLift304", 4, 1, 3);

	Node* tgconnector = new Node("TGConnector", 5, 1, 3); //total number of nodes : 34



	Edge* etg301 = new Edge(tg301, tg302, 3);
	Edge* etg302 = new Edge(tg301, tgstairs301, 1);
	Edge* etg303 = new Edge(tg302, tgtoilet301, 4);
	Edge* etg304 = new Edge(tgtoilet301, tglift301, 10);
	Edge* etg305 = new Edge(tgtoilet301, tg303, 3);
	Edge* etg306 = new Edge(tg303, tg304, 3);
	Edge* etg307 = new Edge(tg304, tg305, 3);
	Edge* etg308 = new Edge(tg305, tgstairs302, 1);
	Edge* etg309 = new Edge(tg305, tg306, 5);
	Edge* etg310 = new Edge(tgstairs302, tg306, 6);
	Edge* etg311 = new Edge(tg306, tg307, 3);
	Edge* etg312 = new Edge(tg307, tg308, 3);
	Edge* etg313 = new Edge(tg307, tg309, 10);
	Edge* etg314 = new Edge(tg308, tg309, 9);
	Edge* etg315 = new Edge(tg308, tg310, 3);
	Edge* etg316 = new Edge(tg308, tglift301, 10);
	Edge* etg317 = new Edge(tg308, tglift302, 10);
	Edge* etg318 = new Edge(tglift301, tglift302, 2);
	Edge* etg319 = new Edge(tg310, tg311, 6);
	Edge* etg320 = new Edge(tg310, tgtoilet302, 5);
	Edge* etg321 = new Edge(tg310, tglift303, 7);
	Edge* etg322 = new Edge(tglift303, tgtoilet302, 2);
	Edge* etg323 = new Edge(tgtoilet302, tg311, 9);
	Edge* etg324 = new Edge(tgtoilet302, tg313, 1);
	Edge* etg325 = new Edge(tg311, tg312, 2);
	Edge* etg326 = new Edge(tg312, tg313, 6);
	Edge* etg327 = new Edge(tg312, tg314, 5);
	Edge* etg328 = new Edge(tg313, tg314, 5);
	Edge* etg329 = new Edge(tg314, tg315, 2);
	Edge* etg330 = new Edge(tg315, tg316, 2);
	Edge* etg331 = new Edge(tg316, tg317, 2);
	Edge* etg332 = new Edge(tg317, tg318, 4);
	Edge* etg333 = new Edge(tg318, tg319, 1);
	Edge* etg334 = new Edge(tg319, tg320, 7);
	Edge* etg335 = new Edge(tg319, tg321, 7);
	Edge* etg336 = new Edge(tg319, tglift304, 10);
	Edge* etg337 = new Edge(tglift304, tg321, 11);
	Edge* etg338 = new Edge(tg320, tg321, 2);
	Edge* etg339 = new Edge(tg320, tg323, 3);
	Edge* etg340 = new Edge(tg321, tg322, 4);
	Edge* etg341 = new Edge(tg322, tg323, 1);
	Edge* etg342 = new Edge(tg322, tg325, 3);
	Edge* etg343 = new Edge(tg323, tg324, 3);
	Edge* etg344 = new Edge(tg324, tg325, 1);
	Edge* etg345 = new Edge(tg324, tgstairs301, 5);
	Edge* etg346 = new Edge(tg325, tgstairs301, 6);
	Edge* etg347 = new Edge(tgconnector, tglift303, 1);
	Edge* etg348 = new Edge(tgconnector, tgtoilet302, 1);


	///////////////////edges between lifts, stairs, and connectors
	//LIFTS AND STAIRS
	//JW first and second floor
	Edge* ejwlift101201 = new Edge(jwlift101, jwlift201, 2);//from jw lift 1 floor 1 --> lift 1 floor 2
	Edge* ejwlift102202 = new Edge(jwlift102, jwlift202, 2);//from jwlift 2 floor 1 --> lift 2 floor 2
	Edge* ejwlift103203 = new Edge(jwlift103, jwlift203, 2);//from jw lift 3 floor 1 --> lift 3 floor 2
	Edge* ejwlift104204 = new Edge(jwlift104, jwlift204, 2);//from jw lift 4 floor 1 --> lift 4 floor 2
	Edge* ejwstairs101201 = new Edge(jwstairs101, jwstairs201, 4);//jw stairs 1 floor 1-->stairs 1 floor 2
	Edge* ejwstairs102202 = new Edge(jwstairs102, jwstairs202, 4);//jw stairs 2 floor 1-->stairs2 floor 2
	//JW second and third floor
	Edge* ejwlift201301 = new Edge(jwlift201, jwlift301, 2);//from jw lift 1 floor 2 --> lift 1 floor 3
	Edge* ejwlift202302 = new Edge(jwlift202, jwlift302, 2);//from jwlift 2 floor 2 --> lift 2 floor 3
	Edge* ejwlift203303 = new Edge(jwlift203, jwlift303, 2);//from jw lift 3 floor 2 --> lift 3 floor 3
	Edge* ejwlift204304 = new Edge(jwlift204, jwlift304, 2);//from jw lift 4 floor 2 --> lift 4 floor 3
	Edge* ejwstairs201301 = new Edge(jwstairs201, jwstairs301, 4);//jw stairs 1 floor 2-->stairs 1 floor 3
	Edge* ejwstairs202302 = new Edge(jwstairs202, jwstairs302, 4);//jw stairs 2 floor 2-->stairs2 floor 3

	//RC first and second floor
	Edge* erclift101201 = new Edge(rclift101, rclift201, 2);//from rc lift 1 floor 1 --> lift 1 floor 2
	Edge* erclift102202 = new Edge(rclift102, rclift202, 2);//from rclift 2 floor 1 --> lift 2 floor 2
	Edge* erclift103203 = new Edge(rclift103, rclift203, 2);//from rc lift 3 floor 1 --> lift 3 floor 2
	Edge* erclift104204 = new Edge(rclift104, rclift204, 2);//from rc lift 4 floor 1 --> lift 4 floor 2
	Edge* ercstairs101201 = new Edge(rcstairs101, rcstairs201, 4);//rc stairs 1 floor 1-->stairs 1 floor 2
	Edge* ercstairs102202 = new Edge(rcstairs102, rcstairs202, 4);//rc stairs 2 floor 1-->stairs2 floor 2
	//RC second and third floor
	Edge* erclift201301 = new Edge(rclift201, rclift301, 2);//from rc lift 1 floor 2 --> lift 1 floor 3
	Edge* erclift202302 = new Edge(rclift202, rclift302, 2);//from rclift 2 floor 2 --> lift 2 floor 3
	Edge* erclift203303 = new Edge(rclift203, rclift303, 2);//from rc lift 3 floor 2 --> lift 3 floor 3
	Edge* erclift204304 = new Edge(rclift204, rclift304, 2);//from rc lift 4 floor 2 --> lift 4 floor 3
	Edge* ercstairs201301 = new Edge(rcstairs201, rcstairs301, 4);//rc stairs 1 floor 2-->stairs 1 floor 3
	Edge* ercstairs202302 = new Edge(rcstairs202, rcstairs302, 4);//rc stairs 2 floor 2-->stairs2 floor 3

	//TG first and second floor
	Edge* etglift101201 = new Edge(tglift101, tglift201, 2);//from tg lift 1 floor 1 --> lift 1 floor 2
	Edge* etglift102202 = new Edge(tglift102, tglift202, 2);//from tglift 2 floor 1 --> lift 2 floor 2
	Edge* etglift103203 = new Edge(tglift103, tglift203, 2);//from tg lift 3 floor 1 --> lift 3 floor 2
	Edge* etglift104204 = new Edge(tglift104, tglift204, 2);//from tg lift 4 floor 1 --> lift 4 floor 2
	Edge* etgstairs101201 = new Edge(tgstairs101, tgstairs201, 4);//tg stairs 1 floor 1-->stairs 1 floor 2
	Edge* etgstairs102202 = new Edge(tgstairs102, tgstairs202, 4);//tg stairs 2 floor 1-->stairs2 floor 2
	//TG second and third floor
	Edge* etglift201301 = new Edge(tglift201, tglift301, 2);//from tg lift 1 floor 2 --> lift 1 floor 3
	Edge* etglift202302 = new Edge(tglift202, tglift302, 2);//from tglift 2 floor 2 --> lift 2 floor 3
	Edge* etglift203303 = new Edge(tglift203, tglift303, 2);//from tg lift 3 floor 2 --> lift 3 floor 3
	Edge* etglift204304 = new Edge(tglift204, tglift304, 2);//from tg lift 4 floor 2 --> lift 4 floor 3
	Edge* etgstairs201301 = new Edge(tgstairs201, tgstairs301, 4);//tg stairs 1 floor 2-->stairs 1 floor 3
	Edge* etgstairs202302 = new Edge(tgstairs202, tgstairs302, 4);//tg stairs 2 floor 2-->stairs2 floor 3

	//CONNECTORS
	Edge* ejwrc = new Edge(jwconnector, rcconnector, 5);
	Edge* ejwtg = new Edge(jwconnector, tgconnector, 5);
	Edge* erctg = new Edge(rcconnector, tgconnector, 5);


	///////////////////////////////////START OF USER INPUT PHASE

	cout << "Input starting point id: " << endl;
	int startID = setStartingPoint();
	nodes.at(startID)->distanceFromStart = 0; // set beginning

	cout << "Input the destination point: " << endl;
	int destinationID = setDestinationPoint();
								
	Dijkstras();
	PrintShortestRouteTo(nodesFINAL.at(destinationID)); //set end node
	system("pause");

}

///////////////////

////done by me
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

//not done by me
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

//prints distance to destination, average time to get there walking, and every step of the way there
void PrintShortestRouteTo(Node* destination)
{
	Node* previous = destination;
	int distance = (destination->distanceFromStart + 1)*2; //added +1 from how we calculate our distance and *2 because each unit is 2m
	int time = distance/ 1.4; //average speed is 1.4 m/s

	cout << "Distance from start: "
		<< distance << " meters." << endl; 
	cout << "Average time to destination: " << time / 60 << " minutes " << time % 60 << " seconds." << endl;
	
	while (previous)																		
	{

		steps.push_back(previous->id.c_str()); //add all steps of the journey to the "steps" vector
		previous = previous->previous;
	}

	int size = steps.size();
	for (int i = size-1; i >= 0; i--) // to print the steps NOT backwards
	{
		if (i == 0)
		{
			cout << steps[i].c_str() << endl;
		}
		else
		{
			cout << steps[i].c_str() << " --> "; //to print the arrows until the last member of vector steps
		}
	}
	
	cout << endl;
}







