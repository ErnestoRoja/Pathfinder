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

const float Node::getPosX() const
{
	return this->node.getPosition().x;
}

const float Node::getPosY() const
{
	return this->node.getPosition().y;
}

const bool Node::isPressed() const
{
	if (this->nodeState == NODE_ACTIVE_LEFT || this->nodeState == NODE_ACTIVE_RIGHT)
	{
		return true;
	}
	return false;
}

void Node::resetNodes(const sf::Vector2f mousePos)
{
	if (this->node.getGlobalBounds().contains(mousePos))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->setStart == true && this->setEnd == true)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_RIGHT_ACTIVE = 0;
			CURRENT_LEFT_ACTIVE = 0;
			std::cout << "Both Reset" << CURRENT_RIGHT_ACTIVE << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_LEFT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_LEFT_ACTIVE = 0;
			std::cout << "Left active reset: " << CURRENT_LEFT_ACTIVE << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->nodeState == NODE_ACTIVE_RIGHT)
		{
			this->nodeState = NODE_IDLE;
			CURRENT_RIGHT_ACTIVE = 0;
			std::cout << "Right active reset: " << CURRENT_RIGHT_ACTIVE << std::endl;
		}
	}
}

void Node::updateNodes(const sf::Vector2f mousePos)
{
	if ((CURRENT_LEFT_ACTIVE < 1))
	{
		if (this->node.getGlobalBounds().contains(mousePos))
		{
			// Left-clicked
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->nodeState = NODE_ACTIVE_LEFT;
				this->setStart = true;
				CURRENT_LEFT_ACTIVE++;
				std::cout << "Left active: " << CURRENT_LEFT_ACTIVE << std::endl;
			}
		}
	}
	if ((CURRENT_RIGHT_ACTIVE < 1))
	{
		if (this->node.getGlobalBounds().contains(mousePos))
		{
			// Right-clicked
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				this->nodeState = NODE_ACTIVE_RIGHT;
				this->setEnd = true;
				CURRENT_RIGHT_ACTIVE++;
				std::cout << "Right active: " << CURRENT_RIGHT_ACTIVE << std::endl;
			}
		}
	}
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
	default:
		this->node.setFillColor(sf::Color::Cyan);
		break;
	}
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
