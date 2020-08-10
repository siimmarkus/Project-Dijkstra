#include "Graaf.h"



shared_ptr<Node> Graph::findMinDistanceNode(unordered_map<string, shared_ptr<Node>> &worklist)
{
	shared_ptr<Node> min = NULL;

	auto it = worklist.begin();
	while (it != worklist.end())
	{

		if (min == NULL || it->second->m_minDistance < min->m_minDistance) {
			min = it->second;
		}

		it++;
	}

	return min;
}



double Graph::findMinDistanceDjikstra(shared_ptr<Node> begining, shared_ptr<Node> end)
{
	begining->m_minDistance = 0;
	begining->m_previousNode = begining;

	shared_ptr<Node> minDistanceNode = begining;
	

	unordered_map<string, shared_ptr<Node>> worklist(node_map);

	while (!worklist.empty())
	{
		shared_ptr<Node> newMinDistanceNode = NULL;

		// Edges starting from minDistanceNode
		for (shared_ptr<Edge> edge : edges[minDistanceNode->m_name]) {
			shared_ptr<Node> destination = node_map[edge->m_node2->m_name];
			
			if (minDistanceNode->m_minDistance + edge->m_weight < destination->m_minDistance) {
				destination->m_minDistance = minDistanceNode->m_minDistance + edge->m_weight;
				destination->m_previousNode = minDistanceNode;
			}
		}

		// Don't have to look further if the endNode distance gets locked;
		if (minDistanceNode == end)
		{
			break;
		}

		worklist.erase(minDistanceNode->m_name);
		minDistanceNode = findMinDistanceNode(worklist);
	}

	return end->m_minDistance;
}
