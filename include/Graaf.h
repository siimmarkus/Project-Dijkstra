#pragma once
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>

using namespace std;

class Graph
{

public:
	
	vector<shared_ptr<Node>> nodes;
	unordered_map<string, shared_ptr<Node>> node_map;
	unordered_map<string, vector<shared_ptr<Edge>>> edges;

	bool active = false;


	Graph() = default;
	shared_ptr<Node> findMinDistanceNode(unordered_map<string, shared_ptr<Node>> &worklist);
	double findMinDistanceDjikstra(shared_ptr<Node> algus, shared_ptr<Node> lopp);

};



