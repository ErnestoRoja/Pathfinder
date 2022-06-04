#include "Node.h"

void Node::initVariables()
{

}

void Node::initShape()
{

}

Node::Node(float pos_x, float pos_y)
{

}

Node::~Node()
{

}

const sf::FloatRect Node::getBounds() const
{
	return this->node.getGlobalBounds();
}

void Node::update()
{

}

void Node::render(sf::RenderTarget* target)
{
	target->draw(this->node);
}
