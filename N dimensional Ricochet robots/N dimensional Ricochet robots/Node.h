#pragma once
#include <iostream>
#include <list>

class Node {
public:
	bool visited;
	Node* previous;
	std::list<Node> neighbours;
};