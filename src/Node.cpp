#include "Node.h"

Node::Node(string name)
	: m_name(name), m_minDistance(INFINITY){}

Node::Node(string name, double minDistance)
	: m_name(name), m_minDistance(minDistance) {}


bool Node::operator<(const Node& other)
{
	return m_minDistance < other.m_minDistance;
}


bool operator<(const Node& lhs, const Node& rhs)
{
	return lhs.m_minDistance < rhs.m_minDistance;
}

ostream& operator<<(ostream& out, const Node& p)
{
	// TODO: insert return statement here
	out << p.m_name;
	return out;
}
