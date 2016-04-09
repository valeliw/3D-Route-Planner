//contains the node and edge classes as well as the funcitons used in the main file

#pragma once
#ifndef DIJKSTRAS_HPP_
#define DIJKSTRAS_HPP_
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//functions withing the cpp
void DijkstrasTest();
int setStartingpoint();
int setDestinationPoint();
void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node*);
Node* ExtractSmallest(vector<Node*>&);
int Distance(Node*, Node*);
bool Contains(vector<Node*>&, Node*);
void PrintShortestRouteTo(Node*);

//Node and Edge classes
class Node
{
public:
	Node(string);
	string id;
	Node* previous;
	int distanceFromStart;
};

class Edge
{
public:
	Edge(Node*, Node*, int);
	bool Connects(Node*, Node*);
	Node* node1;
	Node* node2;
	int distance;
};

#endif /*DIJKSTRAS_HPP_*/