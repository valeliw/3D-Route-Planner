// Dijkstras.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "targetver.h"
#include <iostream>
#include <vector>
#include <string>
#include "Dijsktras.hpp"

extern std::vector<Node*> nodes;
extern std::vector<Node*> nodesFINAL;
extern std::vector<Edge*> edges;
extern std::vector<std::string> steps;


void DijkstrasTest();



//////////////

class Node;
class Edge;

///my own functions
int setStartingPoint();
int setDestinationPoint();

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
	//node constructor
	Node::Node(std::string id, int type, int building, int floor)
		: id(id), previous(NULL), distanceFromStart(INT_MAX), type(type), building(building), floor(floor)
	{
		nodes.push_back(this);
		nodesFINAL.push_back(this);
	}



	//edge constructor
	Edge::Edge(Node* node1, Node* node2, int distance)
		: node1(node1), node2(node2), distance(distance)
	{
		edges.push_back(this);
	}
	bool Edge::Connects(Node* node1, Node* node2)
	{
		return (
			(node1 == this->node1 &&
				node2 == this->node2) ||
			(node1 == this->node2 &&
				node2 == this->node1));
	};


/////////////////////////////////////////////////////////////
	

int setStartingPoint() //function for setting up the start point of the user
{
	std::string start;  
	int size = nodes.size();
	std::getline(std::cin, start);
	for (int i = 0; i < size; i++)
	{
		if (start == nodes.at(i)->id)
		{
			return i;
		}
	}
}

int setDestinationPoint()			//sets the destination of the user
{
	std::string destination;
	int size = nodes.size();
	std::getline(std::cin, destination);
	for (int i = 0; i < size; i++)
	{
		if (destination == nodes.at(i)->id)
		{
			return i;
		}
	}
}



///////////////////

void Dijkstras()						//dijkstras algorithum found at http://www.reviewmylife.co.uk/blog/2008/07/15/dijkstras-algorithm-code-in-c/
{
	while (nodes.size() > 0)
	{
		Node* smallest = ExtractSmallest(nodes);
		std::vector<Node*>* adjacentNodes =
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
Node* ExtractSmallest(std::vector<Node*>& nodes)
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
std::vector<Node*>* AdjacentRemainingNodes(Node* node)
{
	std::vector<Node*>* adjacentNodes = new std::vector<Node*>();
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
bool Contains(std::vector<Node*>& nodes, Node* node)
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
	int distance = (destination->distanceFromStart + 1) * 2; //added +1 from how we calculate our distance and *2 because each unit is 2m
	int time = distance / 1.4; //average speed is 1.4 m/s

	std::cout << "Distance from start: "
		<< distance << " meters." << std::endl;
	std::cout << "Average time to destination: " << time / 60 << " minutes " << time % 60 << " seconds." << std::endl;

	while (previous)
	{

		steps.push_back(previous->id.c_str()); //add all steps of the journey to the "steps" vector
		previous = previous->previous;
	}

	int size = steps.size();
	for (int i = size - 1; i >= 0; i--) // to print the steps NOT backwards
	{
		if (i == 0)
		{
			std::cout << steps[i].c_str() << std::endl;
		}
		else
		{
			std::cout << steps[i].c_str() << " --> "; //to print the arrows until the last member of vector steps
		}
	}

	std::cout << std::endl;
}

bool setHandicap() //returns a boolean to know if user is handicapped or not
{
	bool disability;
	bool looping = true;
	std::string handicap;
	while (looping == true)
	{
		looping = false;
		std::getline(std::cin, handicap);
		if ((handicap != "yes") && (handicap != "no") && (handicap != "Yes") && (handicap != "No"))
		{
			std::cout << "Please enter a correct value (yes or no)" << std::endl;
			looping = true;
		}
		else if ((handicap == "yes") || (handicap == "Yes"))
		{
			disability = true;
		}
		else if ((handicap == "no") || (handicap == "No"))
		{
			disability = false;
		}
	}
	return disability;
}

void deleteStairs(std::vector<Edge*>& edges) //deletes inter-stair edges,only use if handicap = true
{
	int size = edges.size();
	for (int i = 0; i < size; ++i)
	{
		Edge* current = edges.at(i);
		if ((current->node1->type == 3) && (current->node2->type == 3))
		{
			//cout << "The edge connecting " << current->node1->id << " and " << current->node2->id << " was 'deleted' (at i= " << i << endl;
			//^^ for testing purposes
			current->distance = 9999999; //deleting them gave out of range errors
		}
	}
}

	








