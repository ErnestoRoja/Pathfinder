#include "Game.h"


void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Pathfinder", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initNodes()
{
	for (unsigned int y = 0; y < rows_Y; y++)
	{
		for (unsigned int x = 0; x < columns_X; x++)
		{
			nodes.push_back(new Node(x, y));
		}
	}
}

// Neighbors of a node are initialized in the following order: Top, Right, Down, Left (NESW)
void Game::initNeighbors()
{
	for (unsigned int x = 0; x < columns_X; x++)
	{
		for (unsigned int y = 0; y < rows_Y; y++)
		{
			if (y > 0)
				nodes[y * columns_X + x]->neighbors.push_back(nodes[(y - 1) * columns_X + (x + 0)]);
			if (x < columns_X - 1)
				nodes[y * columns_X + x]->neighbors.push_back(nodes[(y + 0) * columns_X + (x + 1)]);
			if (y < rows_Y - 1)
				nodes[y * columns_X + x]->neighbors.push_back(nodes[(y + 1) * columns_X + (x + 0)]);
			if (x > 0)
				nodes[y * columns_X + x]->neighbors.push_back(nodes[(y + 0) * columns_X + (x - 1)]);
			
		}
	}
}

void Game::initGUI()
{
	this->tutorialButton = new Button(1820.f, 5.f, 460.f, 240.f, 
		"Tutorial: \n 1. Set starting node. \n 2. Set end node. \n 3. Set any walls you would like. \n 4. Visualize the algorithm. \n 5. Reset and repeat.",
		sf::Color(9,211,230,255), sf::Color(9, 211, 230, 255), sf::Color(9, 211, 230, 255));

	this->keybindsButton = new Button(1820.f, 255.f, 460.f, 240.f,
		"Key Binds: \n Set Start - Left Click \n Set End - Right Click \n Set Wall - Left-shift Left Click \n Reset Specific Node - Spacebar",
		sf::Color(9, 211, 230, 255), sf::Color(9, 211, 230, 255), sf::Color(9, 211, 230, 255));

	this->BFSButton = new Button(1820.f, 500.f, 200.f, 70.f, "Visualize BFS",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->DFSButton = new Button(1820.f, 578.f, 200.f, 70.f, "Visualize DFS",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->DijkstraButton = new Button(1820.f, 656.f, 200.f, 70.f, "Visualize Dijkstra",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->AStarButton = new Button(1820.f, 734.f, 200.f, 70.f, "Visualize A*",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->resetAlgButton = new Button(2050.f, 500.f, 200.f, 70.f, "Reset Algorithm",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->resetAllButton = new Button(2050.f, 578.f, 200.f, 70.f, "Reset All",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->customButton1 = new Button(1820.f, 920.f, 200.f, 70.f, "Custom Maze 1",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

	this->customButton2 = new Button(2050.f, 920.f, 200.f, 70.f, "Custom Maze 2",
		sf::Color(0, 71, 171, 200), sf::Color(0, 71, 171, 255), sf::Color(8, 24, 168, 255));

}

Game::Game()
{
	this->initWindow();
	this->initGUI();
	this->initNodes();
	this->initNeighbors();
}

Game::~Game()
{
	delete this->window;

	for (auto* i : this->nodes)
	{
		delete i;
	}

	delete this->tutorialButton;
	delete this->keybindsButton;
	delete this->BFSButton;
	delete this->DFSButton;
	delete this->DijkstraButton;
	delete this->AStarButton;
	delete this->resetAlgButton;
	delete this->resetAllButton;
	delete this->customButton1;
	delete this->customButton2;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();

		this->updatePollEvents();

		this->render();
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Game::setCustomGrid(std::string filename)
{
	std::vector<int> testFileData;
	std::ifstream file(filename);
	char tempNumber;
	int index = 0;

	while (!file.eof())
	{
		file >> tempNumber;
		testFileData.push_back(tempNumber);
	}

	for (auto* i : this->nodes)
	{
		if (testFileData.at(index) == 49)
		{
			i->nodeState = NODE_ACTIVE_SHIFT;
			i->isWall = true;
			CURRENT_WALL_ACTIVE++;
		}
		else
		{
			i->nodeState = NODE_IDLE;
		}
		i->assignFillColor();
		index++;
	}
}

void Game::update()
{
	this->updateMousePositions();
	this->BFSButton->update(this->mousePosView);
	this->DFSButton->update(this->mousePosView);
	this->DijkstraButton->update(this->mousePosView);
	this->AStarButton->update(this->mousePosView);
	this->resetAlgButton->update(this->mousePosView);
	this->resetAllButton->update(this->mousePosView);
	this->customButton1->update(this->mousePosView);
	this->customButton2->update(this->mousePosView);
}

void Game::updateNodeLocation()
{
	for (auto* i : this->nodes)
	{
		if (i->isStart() == true)
			startingNode = i;
		else if (i->isEnd() == true)
			endingNode = i;
	}
}

void Game::updateNodes(char key)
{
	switch (key)
	{
	case 'A':  // (BFS)
		if (checkActive() == true)
		{
			this->updateBFS();
		}
		break;
	case 'B':  // (DFS)
		if (checkActive() == true)
		{
			this->updateDFS();
		}
		break;
	case 'C':  // (Dijkstra)
		if (checkActive() == true)
		{
			this->updateDijkstra();
		}
		break;
	case 'D':  // (A*)
		if (checkActive() == true)
		{
			this->updateAStar();
		}
		break;
	case 'P':   // Left or Right Clicked
		if (algActive == false)
		{
			for (auto* i : this->nodes)
			{
				i->update((sf::Vector2f)this->mousePosWindow);
			}
		}
		break;
	case 'N':    // N key (algorithm reset)
		if (algActive == true)
		{
			for (auto* i : this->nodes)
			{
				i->algorithmReset();
			}
			algActive = false;
		}
		break;
	case 'M':    // M key (complete rest)
		for (auto* i : this->nodes)
		{
			i->completeReset();
		}
		algActive = false;
		break;
	case 'K': // Custom maze
		for (auto* i : this->nodes)
		{
			i->completeReset();
		}
		if (activeMaze == "grid1")
			this->setCustomGrid("grids/grid1.txt");
		else
			this->setCustomGrid("grids/grid2.txt");
		algActive = false;
		break;
	default:
		std::cout << "switch default" << std::endl;
		break;
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();

		if (ev.type == sf::Event::MouseButtonPressed || ev.type == sf::Event::KeyPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Left || ev.mouseButton.button == sf::Mouse::Right || ev.key.code == sf::Keyboard::Space)
			{
				this->updateNodes('P');
			}
		}
		if (BFSButton->isPressed() == true)
		{
			this->updateNodes('A');
		}
		else if (DFSButton->isPressed() == true)
		{
			this->updateNodes('B');
		} 
		else if (DijkstraButton->isPressed() == true)
		{
			this->updateNodes('C');
		}
		else if (AStarButton->isPressed() == true)
		{
			this->updateNodes('D');
		}
		else if (resetAlgButton->isPressed() == true)
		{
			this->updateNodes('N');
		}
		else if (resetAllButton->isPressed() == true)
		{
			this->updateNodes('M');
		}
		else if (customButton1->isPressed() == true)
		{
			activeMaze = "grid1";
			this->updateNodes('K');
		}
		else if (customButton2->isPressed() == true)
		{
			activeMaze = "grid2";
			this->updateNodes('K');
		}
	}
}

void Game::updateBFS()
{
	this->updateNodeLocation();

	Node* srcNode = startingNode;
	nodeQueue.emplace_back(srcNode);
	srcNode->isVisited = true;

	while (!nodeQueue.empty() && (endingNode->checkVisited() == false))
	{
		Node* currentNode = nodeQueue.front();
		nodeQueue.pop_front();
		currentNode->colorVisitedNode();

		for (auto* neighbor : currentNode->neighbors)
		{
			if (neighbor->isVisited == false && neighbor->isWall == false)
			{
				neighbor->parent = currentNode;
				nodeQueue.emplace_back(neighbor);
				neighbor->isVisited = true;
				neighbor->colorVisitedNode();
			}
		}
	}

	nodeQueue.clear();
	this->updatePath();
	algActive = true;
}

void Game::updateDFS()
{
	this->updateNodeLocation();

	Node* srcNode = startingNode;
	nodeStack.push(srcNode);
	srcNode->isVisited = true;

	while (!nodeStack.empty() && (endingNode->checkVisited() == false))
	{
		Node* currentNode = nodeStack.top();
		nodeStack.pop();
		currentNode->colorVisitedNode();

		for (auto* neighbor : currentNode->neighbors)
		{
			if (neighbor->isVisited == false && neighbor->isWall == false)
			{
				neighbor->parent = currentNode;
				nodeStack.push(neighbor);
				neighbor->isVisited = true;
				neighbor->colorVisitedNode();
			}
		}
	}

	this->updatePath();
	algActive = true;
}

void Game::updateDijkstra()
{
	this->updateNodeLocation();

	auto distanceCompare = [](Node* leftNode, Node* rightNode)
	{
		return leftNode->distanceCost < rightNode->distanceCost;
	};

	Node* srcNode = startingNode;
	srcNode->distanceCost = 0;
	nodePriorityQueue.emplace_back(srcNode);

	while (!nodePriorityQueue.empty() && (endingNode->checkVisited() == false))
	{
		nodePriorityQueue.sort(distanceCompare);
		Node* currentNode = nodePriorityQueue.front();
		nodePriorityQueue.pop_front();
		currentNode->isVisited = true;
		currentNode->colorVisitedNode();

		for (auto* neighbor : currentNode->neighbors)
		{
			if (neighbor->isVisited == false && neighbor->isWall == false)
			{
				float updatedDistance = currentNode->distanceCost + this->calculateDistance(currentNode, neighbor);
				if (updatedDistance < neighbor->distanceCost)
				{
					neighbor->parent = currentNode;
					neighbor->distanceCost = updatedDistance;
					neighbor->isVisited = true;
					nodePriorityQueue.emplace_back(neighbor);
					neighbor->colorVisitedNode();
				}
			}
		}
	}
	nodePriorityQueue.clear();
	this->updatePath();
	algActive = true;
}

void Game::updateAStar()
{
	this->updateNodeLocation();

	auto globalCostCompare = [](Node* leftNode, Node* rightNode)
	{
		return leftNode->globalCost < rightNode->globalCost;
	};

	Node* srcNode = startingNode;
	srcNode->localCost = 0;
	srcNode->distanceCost = this->calculateDistance(srcNode, endingNode);
	nodePriorityQueue.emplace_back(srcNode);

	while (!nodePriorityQueue.empty() && (endingNode->checkVisited() == false))
	{
		nodePriorityQueue.sort(globalCostCompare);
		Node* currentNode = nodePriorityQueue.front();
		nodePriorityQueue.pop_front();
		currentNode->isVisited = true;
		currentNode->colorVisitedNode();

		for (auto* neighbor : currentNode->neighbors)
		{
			if (neighbor->isVisited == false && neighbor->isWall == false)
			{
				float updatedLocalCost = currentNode->localCost + this->calculateDistance(currentNode, neighbor);
				if (updatedLocalCost < neighbor->localCost)
				{
					neighbor->parent = currentNode;
					neighbor->localCost = updatedLocalCost;
					neighbor->distanceCost = this->calculateDistance(neighbor, endingNode);
					neighbor->globalCost = neighbor->localCost + neighbor->distanceCost;
					neighbor->isVisited = true;
					nodePriorityQueue.emplace_back(neighbor);
					neighbor->colorVisitedNode();
				}
			}
		}
	}
	nodePriorityQueue.clear();
	this->updatePath();
	algActive = true;
}

void Game::updatePath()
{
	Node* traverse = endingNode;

	if (traverse != nullptr)
	{
		while (traverse->parent != nullptr)
		{
			traverse->colorPathNode();
			traverse = traverse->parent;
		}
	}
}

float Game::calculateDistance(Node* targetNode, Node* referenceNode)
{
	float xDistance = targetNode->x - referenceNode->x;
	float yDistance = targetNode->y - referenceNode->y;

	// Euclidean distance
	return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}

void Game::render()
{
	this->window->clear(sf::Color(169, 169, 169, 255));

	for (auto* node : this->nodes)
	{
		node->render(this->window);
	}

	tutorialButton->render(this->window);
	keybindsButton->render(this->window);
	BFSButton->render(this->window);
	DFSButton->render(this->window);
	DijkstraButton->render(this->window);
	AStarButton->render(this->window);
	resetAlgButton->render(this->window);
	resetAllButton->render(this->window);
	customButton1->render(this->window);
	customButton2->render(this->window);

	this->window->display();
}
