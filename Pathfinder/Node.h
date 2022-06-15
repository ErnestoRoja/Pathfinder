#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum node_states {NODE_IDLE = 0, NODE_ACTIVE_LEFT, NODE_ACTIVE_RIGHT};
const unsigned int MAX_LEFT_ACTIVE = 1;
const unsigned int MAX_RIGHT_ACTIVE = 1;
static int CURRENT_LEFT_ACTIVE = 0;
static int CURRENT_RIGHT_ACTIVE = 0;

class Node
{
private:
	short unsigned nodeState;
	
	bool setStart;
	bool setEnd;

	bool isWall;
	bool isVisited;
	float fCost;
	float hCost;
	int x;
	int y;

	// Resources
	sf::RectangleShape node;

	// Variables
	sf::Color idleColor = sf::Color::White;
	sf::Color activeColorLeft = sf::Color::Green;
	sf::Color activeColorRight = sf::Color::Red;

	// Private functions
	

public:
	Node();
	Node(float x, float y);
	virtual ~Node();

	// Public variables
	const sf::Vector2f nodeSize = { 50, 50 };
	std::vector<Node*> neighbors;

	// Accessors
	const sf::FloatRect getBounds() const;
	const float getPosX() const;
	const float getPosY() const;
	const bool isPressed() const;

	// Modifiers
	void resetNodes(const sf::Vector2f mousePos);
	void updateNodes(const sf::Vector2f mousePos);
	void assignFillColor();

	// Public functions
	void update(const sf::Vector2f mousePos);

	void initVariables();
	void initShapes(float x, float y);

	void render(sf::RenderTarget* target);
};