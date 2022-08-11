#pragma once
#include "Node.h"
#include "Button.h"
#include <deque>
#include <stack>
#include <list>
#include <math.h>
#include <fstream>

class Game : private Node, private Button
{
private:
	// Window
	sf::RenderWindow* window;

	// Private resources
	std::vector<Node*> nodes;
	std::deque<Node*> nodeQueue;
	std::list<Node*> nodePriorityQueue;
	std::stack<Node*> nodeStack;

	// Private variables
	const float screenWidth = 2300.0f;
	const float screenHeight = 1000.0f;
	const size_t columns_X = 36;
	const size_t rows_Y = 20;
	sf::RectangleShape s;
	Node* startingNode;
	Node* endingNode;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	bool algActive;
	std::string activeMaze;

	Button* tutorialButton;
	Button* keybindsButton;
	Button* BFSButton;
	Button* DFSButton;
	Button* DijkstraButton;
	Button* AStarButton;
	Button* resetAlgButton;
	Button* resetAllButton;
	Button* customButton1;
	Button* customButton2;

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
	void update();
	void updateNodes(char algorithm);
	void updatePollEvents();
	void updateBFS();
	void updateDFS();
	void updateDijkstra();
	void updateAStar();
	void updatePath();
	void render();

	// Modifiers
	void updateNodeLocation();
	void updateMousePositions();
	void setCustomGrid(std::string filename);

	// Accessors
	float calculateDistance(Node* firstNode, Node* secondNode);
};

