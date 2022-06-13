#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum node_states {NODE_IDLE = 0, NODE_ACTIVE_LEFT, NODE_ACTIVE_RIGHT};

class Node
{
private:
	short unsigned nodeState;

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

	// Accessors
	const sf::FloatRect getBounds() const;
	const bool isPressed() const;

	// Modifiers

	// Public functions
	void update(const sf::Vector2f mousePos);

	void initVariables();
	void initShapes(float x, float y);

	void render(sf::RenderTarget* target);
};