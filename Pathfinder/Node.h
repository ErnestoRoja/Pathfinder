#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <chrono>
#include <thread>

enum node_states {NODE_IDLE = 0, NODE_ACTIVE_LEFT, NODE_ACTIVE_RIGHT, NODE_ACTIVE_SHIFT, NODE_ACTIVE_PATH};
const unsigned int MAX_LEFT_ACTIVE = 1;
const unsigned int MAX_RIGHT_ACTIVE = 1;
static int CURRENT_LEFT_ACTIVE = 0;
static int CURRENT_RIGHT_ACTIVE = 0;
static int CURRENT_WALL_ACTIVE = 0;

class Node
{
private:
	

	// Private variables
	sf::RectangleShape node;
	sf::Color idleColor = sf::Color::White;
	sf::Color activeColorLeft = sf::Color::Green;
	sf::Color activeColorRight = sf::Color::Red;
	sf::Color wallColor = sf::Color::Black;
	sf::Color pathColor = sf::Color::Cyan;

	// Private functions
	void initVariables(float x, float y);
	void initShapes(float x, float y);

public:
	Node();
	Node(float x, float y);
	virtual ~Node();

	// Public variables
	bool setStart;
	bool setEnd;
	const sf::Vector2f nodeSize = { 50, 50 };
	std::vector<Node*> neighbors;
	Node* parent;
	bool isWall;
	bool isVisited;
	float globalCost;
	float localCost;
	float distanceCost;
	float x;
	float y;
	short unsigned nodeState;

	// Public functions
	void update(const sf::Vector2f mousePos);

	void render(sf::RenderTarget* target);

	// Modifiers
	void resetNodes(const sf::Vector2f mousePos);
	void updateNodes(const sf::Vector2f mousePos);
	void completeReset();
	void algorithmReset();
	void assignFillColor();
	void colorVisitedNode();
	void colorPathNode();

	// Accessors
	const bool isPressed() const;
	const bool checkVisited() const;
	const bool isStart() const;
	const bool isEnd() const;
	const bool checkActive() const;
};