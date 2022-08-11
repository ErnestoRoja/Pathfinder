#include "Node.h"

// Blueprint for all initializes nodes
void Node::initVariables(float x, float y)
{
	this->parent = nullptr;
	this->isWall = false;
	this->isVisited = false;
	this->x = x;
	this->y = y;
	this->nodeState = NODE_IDLE;
	this->distanceCost = INFINITY;
	this->localCost = INFINITY;
	this->globalCost = INFINITY;
}

// How each node looks
void Node::initShapes(float x, float y)
{
	this->node.setSize(nodeSize);
	this->node.setPosition(sf::Vector2f(x * nodeSize.x, y * nodeSize.y));
	this->node.setOutlineThickness(nodeSize.x / 15);
	this->node.setOutlineColor(sf::Color::Black);
}

// Default constructor
Node::Node()
{

}

// Constructor
Node::Node(float x, float y)
{
	this->initVariables(x, y);
	this->initShapes(x, y);
}

// Destructor
Node::~Node()
{

}

// Returns whether a node is active
const bool Node::isPressed() const
{
	if (this->nodeState == NODE_ACTIVE_LEFT || this->nodeState == NODE_ACTIVE_RIGHT)
	{
		return true;
	}
	return false;
}

// Returns whether a node is visited
const bool Node::checkVisited() const
{
	return this->isVisited;
}

// Returns whether a node is the start
const bool Node::isStart() const
{
	return this->setStart;
}

// Returns whether a node is the end
const bool Node::isEnd() const
{
	return this->setEnd;
}

// Returns whether both nodes are active
const bool Node::checkActive() const
{
	if (CURRENT_LEFT_ACTIVE == 1 && CURRENT_RIGHT_ACTIVE == 1)
		return true;

	return false;
}

// Resets a node based on user input
void Node::resetNodes(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		// Spacebar while hovering starting node (removes the starting node)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_LEFT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_LEFT_ACTIVE = 0;
			this->setStart = false;
		}
		// Spacebar while hovering the end node (removes the end node)
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_RIGHT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_RIGHT_ACTIVE = 0;
			this->setEnd = false;
		}
		// Spacebar while hovering a wall (removes the wall)
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_SHIFT)
		{
			this->nodeState = NODE_IDLE;
			this->isWall = false;
		}
	}
}

// Updates a node based on user input
void Node::updateNodes(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		// Shift Left-clicked (sets a wall)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isWall == false && this->setStart == false && this->setEnd == false)
		{
			this->nodeState = NODE_ACTIVE_SHIFT;
			this->isWall = true;
		}
	}
	if ((CURRENT_LEFT_ACTIVE < 1))
	{
		if (this->node.getGlobalBounds().contains(mousePos))
		{
			// Left-clicked (sets the start node)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isWall == false && this->setEnd == false)
			{
				this->nodeState = NODE_ACTIVE_LEFT;
				this->setStart = true;
				CURRENT_LEFT_ACTIVE++;
			}
		}
	}
	if ((CURRENT_RIGHT_ACTIVE < 1))
	{
		if (this->node.getGlobalBounds().contains(mousePos))
		{
			// Right-clicked (sets the end node)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isWall == false && this->setStart == false)
			{
				this->nodeState = NODE_ACTIVE_RIGHT;
				this->setEnd = true;
				CURRENT_RIGHT_ACTIVE++;
			}
		}
	}
	
}

// Sets a node back to its initial conditions
void Node::completeReset()
{
	this->setStart = false;
	this->setEnd = false;
	this->parent = nullptr;
	this->isWall = false;
	this->isVisited = false;
	this->distanceCost = INFINITY;
	this->localCost = INFINITY;
	this->globalCost = INFINITY;
	this->nodeState = NODE_IDLE;
	CURRENT_LEFT_ACTIVE = 0;
	CURRENT_RIGHT_ACTIVE = 0;
	this->assignFillColor();
}

// Sets any variables used by the algorithms back to their initial conditions
void Node::algorithmReset()
{
	if (this->isVisited == true && this->setStart == false && this->setEnd == false)
		this->nodeState = NODE_IDLE;
	
	this->parent = nullptr;
	this->distanceCost = INFINITY;
	this->localCost = INFINITY;
	this->globalCost = INFINITY;
	this->assignFillColor();
	this->isVisited = false;
}

// Handles what color each node should be based on its state
void Node::assignFillColor()
{
	switch (this->nodeState)
	{
	case NODE_IDLE:
		this->node.setFillColor(this->idleColor);
		break;
	case NODE_ACTIVE_LEFT:
		this->node.setFillColor(this->activeColorLeft);
		break;
	case NODE_ACTIVE_RIGHT:
		this->node.setFillColor(this->activeColorRight);
		break;
	case NODE_ACTIVE_SHIFT:
		this->node.setFillColor(this->wallColor);
		break;
	default:
		this->node.setFillColor(sf::Color::Cyan);
		break;
	}
}

// Keeps the start and end node the same color, but changes the color of any visited node
void Node::colorVisitedNode()
{
	if (this->isStart() == true)
		this->node.setFillColor(activeColorLeft);
	else if (this->isEnd() == true)
		this->node.setFillColor(activeColorRight);
	else
		this->node.setFillColor(visitedNodeColor);
}

// Keeps the end node the same color, but changes the color of the path
void Node::colorPathNode()
{
	if (this->isEnd() == true)
		this->node.setFillColor(activeColorRight);
	else 
		this->node.setFillColor(sf::Color(244, 164, 96, 255));
}

// Handles any changes made to a node
void Node::update(const sf::Vector2f mousePos)
{
	this->resetNodes(mousePos);
	this->updateNodes(mousePos);
	this->assignFillColor();
}

// Renders each node to the window
void Node::render(sf::RenderTarget* target)
{
	target->draw(this->node);
}
