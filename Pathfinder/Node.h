#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>

enum node_states {NODE_IDLE = 0, NODE_ACTIVE_LEFT, NODE_ACTIVE_RIGHT, NODE_ACTIVE_SHIFT, NODE_ACTIVE_PATH};
const unsigned int MAX_LEFT_ACTIVE = 1;
const unsigned int MAX_RIGHT_ACTIVE = 1;
static int CURRENT_LEFT_ACTIVE = 0;
static int CURRENT_RIGHT_ACTIVE = 0;
static int CURRENT_WALL_ACTIVE = 0;

class Node
{
private:

	bool setStart;
	bool setEnd;

	// Resources
	sf::RectangleShape node;

	// Variables
	sf::Color idleColor = sf::Color::White;
	sf::Color activeColorLeft = sf::Color::Green;
	sf::Color activeColorRight = sf::Color::Red;
	sf::Color wallColor = sf::Color::Blue;
	sf::Color pathColor = sf::Color::Cyan;

	// Private functions
	
public:
	Node();
	Node(float x, float y);
	virtual ~Node();

	// Public variables
	const sf::Vector2f nodeSize = { 50, 50 };
	std::vector<Node*> neighbors;
	Node* parent;
	bool isWall;
	bool isVisited;
	float fCost;
	float hCost;
	int x;
	int y;
	bool needsUpdate;
	bool startAlgo;
	short unsigned nodeState;

	// Accessors
	const sf::FloatRect getBounds() const;
	const bool isPressed() const;
	bool needsToBeUpdated();
	bool checkVisited();
	bool isStart();
	bool isEnd();

	// Modifiers
	void resetNodes(const sf::Vector2f mousePos);
	void updateNodes(const sf::Vector2f mousePos);
	void completeReset();
	void assignFillColor();
	void colorPath();

	// Public functions
	void update(const sf::Vector2f mousePos);

	void initVariables();
	void initShapes(float x, float y);

	void render(sf::RenderTarget* target);
};