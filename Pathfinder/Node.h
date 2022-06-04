#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Node
{
private:
	bool isWall;
	bool isVisited;
	float fCost;
	float hCost;
	int x;
	int y;

	sf::RectangleShape node;

	// Private functions
	void initVariables();
	void initShape();

public:
	Node(float pos_x, float pos_y);
	virtual ~Node();

	// Accessors
	const sf::FloatRect getBounds() const;

	// Modifiers

	// Public functions
	void update();
	
	void render(sf::RenderTarget* target);
};

