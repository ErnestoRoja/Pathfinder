#pragma once
#include "Node.h"
#include <deque>

class Game : private Node
{
private:
	// Window
	sf::RenderWindow* window;

	// Resources
	std::vector<Node*> nodes;
	std::deque<Node*> nodeQueue;

	// Variables
	const float screenWidth = 1800.0f;
	const float screenHeight = 1000.0f;
	const size_t columns_X = screenWidth / nodeSize.x;
	const size_t rows_Y = screenHeight / nodeSize.y;
	sf::RectangleShape s;
	Node* startingNode;
	Node* endingNode;
	sf::Vector2i mousePosWindow;
	bool algActive;

	// Private functions
	void initWindow();
	void initNodes();
	void initNeighbors();
	
public:
	Game();
	virtual ~Game();

	// Public functions
	void run();

	void updateMousePositions();
	void update();
	void updateNodes(char algorithm);
	void updatePollEvents();
	void updateNodeLocation();
	void updateBFS();
	void updatedDFS();
	void updatePath();

	void render();
};

