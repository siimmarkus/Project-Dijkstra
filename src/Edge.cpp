#include "Edge.h"

Edge::Edge(shared_ptr<Node> node1, shared_ptr<Node> node2, double weight)
	: m_node1(node1), m_node2(node2), m_weight(weight){}

ostream& operator<<(ostream& out, const Edge& edge)
{
	out << "Edge(" << *edge.m_node1 << "->" << *edge.m_node2 << ", w=" << edge.m_weight << ")";
	return out;
}
