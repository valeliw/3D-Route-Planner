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
	catch (const out_of_range& oor)
	{
		cerr << "Out of range error: " << oor.what() << ", please input a correct room name (ie Room23)." << endl;
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
int setStartingpoint();
int setDestinationPoint();


vector<Node*> nodes;
vector<Node*> nodesFINAL;
vector<Edge*> edges;

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

///////////////////

///done by me
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
//note: Node(id, type, building, floor)
{	//first floor of JW
	Node* room1 = new Node("JWRoom101", 1, 1, 1);
	Node* room2 = new Node("Room2", 1, 1, 1);
	Node* room3 = new Node("Room3", 1, 1, 1);
	Node* room4 = new Node("Room4", 1, 1, 1);
	Node* room5 = new Node("Room5", 1, 1, 1);
	Node* room6 = new Node("Room6", 1, 1, 1);
	Node* room7 = new Node("Room7", 1, 1, 1);
	Node* room8 = new Node("Room8", 1, 1, 1);
	Node* room9 = new Node("Room9", 1, 1, 1);
	Node* room10 = new Node("Room10", 1, 1, 1);
	Node* room11 = new Node("Room11", 1, 1, 1);
	Node* room12 = new Node("Room12", 1, 1, 1);
	Node* room13 = new Node("Room13", 1, 1, 1);
	Node* room14 = new Node("Room14", 1, 1, 1);
	Node* room15 = new Node("Room15", 1, 1, 1);
	Node* room16 = new Node("Room16", 1, 1, 1);
	Node* room17 = new Node("Room17", 1, 1, 1);
	Node* room18 = new Node("Room18", 1, 1, 1);
	Node* room19 = new Node("Room19", 1, 1, 1);
	Node* room20 = new Node("Room20", 1, 1, 1);
	Node* room21 = new Node("Room21", 1, 1, 1);
	Node* room22 = new Node("Room22", 1, 1, 1);
	Node* room23 = new Node("Room23", 1, 1, 1);
	Node* room24 = new Node("Room24", 1, 1, 1);
	Node* room25 = new Node("Room25", 1, 1, 1);
	Node* toilet1 = new Node("Toilet1", 2, 1, 1);
	Node* toilet2 = new Node("Toilet2", 2, 1, 1);
	Node* stairs1 = new Node("Stairs1", 3, 1, 1);
	Node* stairs2 = new Node("Stairs2", 3, 1, 1);
	Node* elevator1 = new Node("Elevator1", 4, 1, 1);
	Node* elevator2 = new Node("Elevator2", 4, 1, 1);
	Node* elevator3 = new Node("Elevator3", 4, 1, 1);
	Node* elevator4 = new Node("Elevator4", 4, 1, 1); //total number of nodes : 33



	Edge* e1 = new Edge(room1, room2, 3);
	Edge* e2 = new Edge(room1, stairs1, 1);
	Edge* e3 = new Edge(room2, toilet1, 4);
	Edge* e4 = new Edge(toilet1, elevator1, 10);
	Edge* e5 = new Edge(toilet1, room3, 3);
	Edge* e6 = new Edge(room3, room4, 3);
	Edge* e7 = new Edge(room4, room5, 3);
	Edge* e8 = new Edge(room5, stairs2, 1);
	Edge* e9 = new Edge(room5, room6, 5);
	Edge* e10 = new Edge(stairs2, room6, 6);
	Edge* e11 = new Edge(room6, room7, 3);
	Edge* e12 = new Edge(room7, room8, 3);
	Edge* e13 = new Edge(room7, room9, 10);
	Edge* e14 = new Edge(room8, room9, 9);
	Edge* e15 = new Edge(room8, room10, 3);
	Edge* e16 = new Edge(room8, elevator1, 10);
	Edge* e17 = new Edge(room8, elevator2, 10);
	Edge* e18 = new Edge(elevator1, elevator2, 2);
	Edge* e19 = new Edge(room10, room11, 6);
	Edge* e20 = new Edge(room10, toilet2, 5);
	Edge* e21 = new Edge(room10, elevator3, 7);
	Edge* e22 = new Edge(elevator3, toilet2, 2);
	Edge* e23 = new Edge(toilet2, room11, 9);
	Edge* e24 = new Edge(toilet2, room13, 1);
	Edge* e25 = new Edge(room11, room12, 2);
	Edge* e26 = new Edge(room12, room13, 6);
	Edge* e27 = new Edge(room12, room14, 5);
	Edge* e28 = new Edge(room13, room14, 5);
	Edge* e29 = new Edge(room14, room15, 2);
	Edge* e30 = new Edge(room15, room16, 2);
	Edge* e31 = new Edge(room16, room17, 2);
	Edge* e32 = new Edge(room17, room18, 4);
	Edge* e33 = new Edge(room18, room19, 1);
	Edge* e34 = new Edge(room19, room20, 7);
	Edge* e35 = new Edge(room19, room21, 7);
	Edge* e36 = new Edge(room19, elevator4, 10);
	Edge* e37 = new Edge(elevator4, room21, 11);
	Edge* e38 = new Edge(room20, room21, 2);
	Edge* e39 = new Edge(room20, room23, 3);
	Edge* e40 = new Edge(room21, room22, 4);
	Edge* e41 = new Edge(room22, room23, 1);
	Edge* e42 = new Edge(room22, room25, 3);
	Edge* e43 = new Edge(room23, room24, 3);
	Edge* e44 = new Edge(room24, room25, 1);
	Edge* e45 = new Edge(room24, stairs1, 5);
	Edge* e46 = new Edge(room25, stairs1, 6);



	


	//reveresed order to give correct output
	cout << "Input starting point id: " << endl;
	int destinationID = setDestinationPoint(); //set destination point

	cout << "Input the destination point: " << endl;
	int startID = setStartingPoint();
	nodes.at(startID)->distanceFromStart = 0; // set starting point

	Dijkstras();


	PrintShortestRouteTo(nodesFINAL.at(destinationID)); //set end node
	system("pause");


														// TODO: Node / Edge memory cleanup not included
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
		<< destination->distanceFromStart + 1 << endl;
	while (previous)
	{
		cout << previous->id.c_str() << " ";
		previous = previous->previous;
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
