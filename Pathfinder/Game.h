#pragma once
#include "Node.h"

class Game : private Node
{
private:
	// Window
	sf::RenderWindow* window;

	// Resources
	std::vector<Node*> nodes;
	sf::RectangleShape s;
	Node* start;
	Node* end;

	// Variables
	const float screenWidth = 1800.0f;
	const float screenHeight = 1000.0f;
	const size_t columns_X = screenWidth / nodeSize.x;
	const size_t rows_Y = screenHeight / nodeSize.y;

	sf::Vector2i mousePosWindow;

	// Private functions
	void initWindow();
	void initNodes();
	

public:
	Game();
	virtual ~Game();

	// Public functions
	void run();

	void updateMousePositions();
	void update();
	void updateNodes();
	void updatePollEvents();

	void render();
};

