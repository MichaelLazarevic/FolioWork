#include "Navigation.h"

Navigation* Navigation::pInstance = nullptr;

Navigation::Navigation()
{
}

int Navigation::getClosestNode(Vector2D position)
{
	float shortestDist = 999999;

	int closestID = 0;

	for (Node& n : nodeList)
	{
		if ((n.position - position).magnitude() < shortestDist)
		{
			closestID = n.nodeId;
			shortestDist = ((n.position - position).magnitude());
		}
	}
	return closestID;
}


std::vector<Vector2D> Navigation::getPath(Node* end)
{
	std::vector<Vector2D> path;

	Node* pNode = end;

	path.push_back(end->position);

	while (end->priorNode != nullptr)
	{
		end = end->priorNode;
		path.push_back(end->position);
	}

	return path;
}

void Navigation::start()
{
	nodeList.clear();
	Rectangle2D firstRect;
	firstRect.PlaceAt(botLeft, topRight);
	Partition(firstRect);
	createEdges();
}

void Navigation::Partition(Rectangle2D r)
{
	if (r.GetArea() < 5000.0f)
	{
		return;
	}
	else if (StaticMap::GetInstance()->IsInsideBlock(r))
	{
		// Divide r into r1, r2, r3, r4
		Rectangle2D r1;
		Rectangle2D r2;
		Rectangle2D r3;
		Rectangle2D r4;
		Vector2D rCenter = r.GetCentre();
		r1.PlaceAt(r.GetTopLeft(), rCenter);
		r2.PlaceAt(r.GetTopRight(), rCenter);
		r3.PlaceAt(r.GetBottomLeft(), rCenter);
		r4.PlaceAt(r.GetBottomRight(), rCenter);
		Partition(r1);
		Partition(r2);
		Partition(r3);
		Partition(r4);
	}
	else
	{
		Circle2D c;
		c.PlaceAt(r.GetCentre(), 25);
		if (!StaticMap::GetInstance()->IsInsideBlock(c))
		{
			Node node;
			node.position = r.GetCentre();
			node.nodeId = nodeList.size();
			nodeList.push_back(node);
		}
	}

}

void Navigation::createEdges()
{
	StaticMap* t_StaticMap = StaticMap::GetInstance();

	for (Node& n : nodeList)
	{
		for (Node& y : nodeList)
		{
			if (t_StaticMap->IsLineOfSight(n.position, y.position))
			{
				if (!(n.position == y.position))
				{
					Edge edge;
					edge.connectedNodeID = y.nodeId;
					edge.cost = Vector2D(n.position - y.position).magnitude();
					if (edge.cost < 450)
					{
						n.edgeList.push_back(edge);
					}
				}
			}
		}
	}
}

Navigation* Navigation::getInstance()
{
	if (!pInstance)
	{
		pInstance = new Navigation;
	}

	return pInstance;
}

void Navigation::debugDisplay()
{
	for (int i = 0; i < nodeList.size(); i++)
	{
		if (debugNode)
		{
			Renderer::GetInstance()->DrawCircle(nodeList[i].position, 25, 0);
		}
	}
}


//Generates the path from start to end position with A*
std::vector<Vector2D> Navigation::createPath(Vector2D start, Vector2D target)
{
	Node* currentNode = nullptr;
	int nodesOpen = 0;

	// Nearest node to the start position
	int startNum = getClosestNode(start);
	// Nearest node to the end position
	int endNum = getClosestNode(target);

	// Clears the initial values
	for (int i = 0; i < nodeList.size(); i++)
	{
		nodeList[i].aScore = 0;
		nodeList[i].bScore = 0;

		nodeList[i].currentState = UNUSED;

		nodeList[i].priorNode = nullptr;
	}

	// Opens the first node
	nodeList[startNum].currentState = OPEN;
	nodesOpen++;

	// Calculate out the travel cost of that node to the end
	nodeList[startNum].bScore = (nodeList[startNum].position - nodeList[endNum].position).magnitude();

	while (nodesOpen > 0)
	{
		float lowestbScore = 9999999;
		int index = startNum;

		for (int i = 0; i < nodeList.size(); i++)
		{
			if (nodeList[i].currentState == OPEN && nodeList[i].bScore < lowestbScore &&  nodeList[i].bScore > 0)
			{
				index = nodeList[i].nodeId;
				lowestbScore = nodeList[i].bScore;
			}
		}

		currentNode = &nodeList[index];

		if (currentNode->nodeId != endNum)
		{
			currentNode->currentState = CLOSED;
			nodesOpen--;

			for (int i = 0; i < currentNode->edgeList.size(); i++)
			{
				float bScore = 0;
				float aScore = 0;

				int t_connectedEdge = currentNode->edgeList[i].connectedNodeID;

				if (nodeList[t_connectedEdge].currentState != CLOSED)
				{
					aScore = currentNode->aScore + currentNode->edgeList[i].cost;
					if (aScore < nodeList[t_connectedEdge].aScore || nodeList[t_connectedEdge].currentState != OPEN)
					{
						nodeList[t_connectedEdge].priorNode = currentNode;
						nodeList[t_connectedEdge].aScore = aScore;

						nodeList[t_connectedEdge].bScore = nodeList[t_connectedEdge].aScore + (nodeList[t_connectedEdge].position - nodeList[endNum].position).magnitude();

						if (nodeList[t_connectedEdge].currentState != OPEN)
						{
							nodeList[t_connectedEdge].currentState = OPEN;
							nodesOpen++;
						}
					}
				}
			}
		}
		else
		{
			nodesOpen = 0;
		}
	}
	return getPath(currentNode);

}