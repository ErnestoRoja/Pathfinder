#pragma once
#include "Node.h"
#include "Button.h"
#include <deque>
#include <stack>
#include <list>
#include <math.h>
#include <Windows.h>
#include <ctime>

class Game : private Node, private Button
{
private:
	// Window
	sf::RenderWindow* window;

	// Resources
	std::vector<Node*> nodes;
	std::deque<Node*> nodeQueue;
	std::list<Node*> nodePriorityQueue;
	std::stack<Node*> nodeStack;

	// Variables
	const float screenWidth = 2300.0f;
	const float screenHeight = 1000.0f;
	const size_t columns_X = 36;
	const size_t rows_Y = 20;
	sf::RectangleShape s;
	Node* startingNode;
	Node* endingNode;
	sf::Vector2i mousePosWindow;
	bool algActive;

	Button* tutorialButton;
	Button* keybindsButton;

	// Private functions
	void initWindow();
	void initNodes();
	void initNeighbors();
	void initGUI();
	
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
	void updateDFS();
	void updateDijkstra();
	void updateAStar();
	void updatePath();

	float calculateDistance(Node* firstNode, Node* secondNode);

	void render();
};

