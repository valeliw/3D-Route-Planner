#ifndef DIJSKTRAS_HPP_
#define DIJSKTRAS_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <tchar.h>


//node class 
class Node
{
private:

public:
	Node(std::string, int, int, int);
	Node* previous;
	std::string id;
	int distanceFromStart;
	int type;
	int building;
	int floor;
	
};


// edge class with constructor
class Edge
{
public:	
	Edge(Node*, Node*, int);
	int distance;
	bool Connects(Node*,Node*);
	Node* node1;
	Node* node2;
};



//function declarations
bool setHandicap();
void deleteStairs(std::vector<Edge*>& edges);
void DijkstrasTest();
void Dijkstras();
std::vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(std::vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(std::vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);
void RemoveEdge(std::vector<Edge*>& edges, Edge* edge);
std::vector<Edge*>* AdjacentEdges(std::vector<Edge*>& edges, Node* node);
//Edge(Node* node1, Node* node2, int distance);

///my own functions
int setStartingpoint();
int setDestinationPoint();


#endif DIJSKTRAS_HPP_