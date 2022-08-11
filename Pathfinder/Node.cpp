#include "Node.h"

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

void Node::initShapes(float x, float y)
{
	this->node.setSize(nodeSize);
	this->node.setPosition(sf::Vector2f(x * nodeSize.x, y * nodeSize.y));
	this->node.setOutlineThickness(nodeSize.x / 15);
	this->node.setOutlineColor(sf::Color::Red);
}

Node::Node()
{

}

Node::Node(float x, float y)
{
	this->initVariables(x, y);
	this->initShapes(x, y);
}

Node::~Node()
{

}

const bool Node::isPressed() const
{
	if (this->nodeState == NODE_ACTIVE_LEFT || this->nodeState == NODE_ACTIVE_RIGHT)
	{
		return true;
	}
	return false;
}

const bool Node::checkVisited() const
{
	return this->isVisited;
}

const bool Node::isStart() const
{
	return this->setStart;
}

const bool Node::isEnd() const
{
	return this->setEnd;
}

const bool Node::checkActive() const
{
	if (CURRENT_LEFT_ACTIVE == 1 && CURRENT_RIGHT_ACTIVE == 1)
		return true;

	return false;
}

void Node::resetNodes(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_LEFT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_LEFT_ACTIVE = 0;
			this->setStart = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_RIGHT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_RIGHT_ACTIVE = 0;
			this->setEnd = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_SHIFT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_WALL_ACTIVE--;
			this->isWall = false;
		}
	}
}

void Node::updateNodes(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		// Shift Left-clicked (sets a wall)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isWall == false && this->setStart == false && this->setEnd == false)
		{
			this->nodeState = NODE_ACTIVE_SHIFT;
			this->isWall = true;
			CURRENT_WALL_ACTIVE++;
		}
	}
	if ((CURRENT_LEFT_ACTIVE < 1))
	{
		if (this->node.getGlobalBounds().contains(mousePos))
		{
			// Left-clicked (sets the start point)
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
			// Right-clicked (sets the end point)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isWall == false && this->setStart == false)
			{
				this->nodeState = NODE_ACTIVE_RIGHT;
				this->setEnd = true;
				CURRENT_RIGHT_ACTIVE++;
			}
		}
	}
	
}

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

void Node::colorVisitedNode()
{
	if (this->isStart() == true)
		this->node.setFillColor(activeColorLeft);
	else if (this->isEnd() == true)
		this->node.setFillColor(activeColorRight);
	else
		this->node.setFillColor(pathColor);
}

void Node::colorPathNode()
{
	if (this->isEnd() == true)
		this->node.setFillColor(activeColorRight);
	else 
		this->node.setFillColor(sf::Color(244, 164, 96, 255));
}

void Node::update(const sf::Vector2f mousePos)
{
	this->resetNodes(mousePos);
	this->updateNodes(mousePos);
	this->assignFillColor();
}

void Node::render(sf::RenderTarget* target)
{
	target->draw(this->node);
}
