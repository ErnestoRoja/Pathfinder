#include "Node.h"

void Node::initVariables()
{
	this->isWall = false;
	this->isVisited = false;
	this->x = x;
	this->y = y;
	this->nodeState = NODE_IDLE;
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
	this->initVariables();
	this->initShapes(x, y);
}

Node::~Node()
{

}

const sf::FloatRect Node::getBounds() const
{
	return this->node.getGlobalBounds();
}

const bool Node::isPressed() const
{
	if (this->nodeState == NODE_ACTIVE_LEFT || this->nodeState == NODE_ACTIVE_RIGHT)
	{
		return true;
	}
	return false;
}

void Node::update(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		// Left-clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->nodeState = NODE_ACTIVE_LEFT;
				
		}
		// Right-clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->nodeState = NODE_ACTIVE_RIGHT;
		}
	}
	else
	{
		this->nodeState = NODE_IDLE;
	}
	
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
	default:
		this->node.setFillColor(sf::Color::Cyan);
		break;
	}
}

void Node::render(sf::RenderTarget* target)
{
	target->draw(this->node);
}
