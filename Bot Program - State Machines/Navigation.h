#ifndef __NAVIGATION__
#define __NAVIGATION__

#include <vector>
#include "vector2D.h"
#include "Shapes.h"
#include "Renderer.h"
#include "staticmap.h"

// Const defaults for initial square
const Vector2D botLeft = Vector2D(-1500, -1500);
const Vector2D topRight = Vector2D(1500, 1500);

// Enums to represent a viable pathway in the node chain
enum nodeState {UNUSED, OPEN, CLOSED};

// Edges. Links between nodes
struct Edge
{
	int connectedNodeID;
	float cost;
};

// Node. A location on the map that can be
// chained to another Node for pathfinding
struct Node
{
	std::vector<Edge> edgeList;
	Vector2D position;
	int nodeId;
	float aScore; // Travel Cost
	float bScore; // Potential Travel Cost
	Node* priorNode;
	nodeState currentState;
};

// This class makes use of Nodes and Edges
// to find the fastest path between any
// two locations given.
class Navigation
{
private:
	static Navigation* pInstance;
	std::vector<Node> nodeList;

	Navigation();
	~Navigation();

	int getClosestNode(Vector2D position);
	void Partition(Rectangle2D rect);
	void createEdges();
	std::vector<Vector2D> getPath(Node* end);

public:
	static Navigation* getInstance();

	boolean debugNode = true;

	void start();
	void debugDisplay();

	std::vector<Vector2D> createPath(Vector2D start, Vector2D end);
};

#endif // !__NAVIGATION__

