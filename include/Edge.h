#pragma once
#include "Node.h"
class Edge
{
public:
	shared_ptr<Node> m_node1;
	shared_ptr<Node> m_node2;
	double m_weight;

	Edge(shared_ptr<Node> node1, shared_ptr<Node> node2, double weight);

	friend ostream& operator<<(ostream& out, const Edge& edge);
};

