#pragma once

#include <string>
#include <iostream>
#include <math.h>
#include <memory>

using namespace std;
class Node
{
public:
	string m_name;

	double m_minDistance;	// Shortest current path from starting node to this node.
	shared_ptr<Node> m_previousNode; // Previous node in the shortest path to this node.


	Node(string name);
	Node(string name, double minDistance);
    bool operator <(const Node& other);
	friend bool operator< (const Node& lhs, const Node& rhs);
	friend ostream& operator<<(ostream& out, const Node& p);


};

