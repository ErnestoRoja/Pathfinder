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

Game::Game()
{
	this->initWindow();
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
}

void Game::update()
{
	this->updateMousePositions();
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
	case 'A':  // Num1 (BFS)
		if (checkActive() == true)
		{
			this->updateBFS();
		}
		break;
	case 'B':  // Num2 (DFS)
		if (checkActive() == true)
		{
			this->updateDFS();
		}
		break;
	case 'L':   // Left Clicked
		if (algActive == false)
		{
			for (auto* i : this->nodes)
			{
				i->update((sf::Vector2f)this->mousePosWindow);
			}
		}
		break;
	case 'R':   // Right Clicked
		if (algActive == false)
		{
			for (auto* i : this->nodes)
			{
				i->update((sf::Vector2f)this->mousePosWindow);
			}
		}
		break;
	case 'S':    // Spacebar
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
			std::cout << "partial reset" << std::endl;
			algActive = false;
		}
		break;
	case 'M':    // M key (complete rest)
		for (auto* i : this->nodes)
		{
			i->completeReset();
		}
		std::cout << "complete reset" << std::endl;
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
		if (ev.Event::type == sf::Event::Closed || ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

		bool lockLeftClick = false;
		bool lockRightClick = false;
		bool lockSpacebar = false;
		bool lockM = false;
		bool lockN = false;
		bool lockNum1 = false;
		bool lockNum2 = false;
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Left && lockLeftClick != true)
			{
				this->updateNodes('L');
				lockLeftClick = true;
			}
			else if (ev.mouseButton.button == sf::Mouse::Right && lockRightClick != true)
			{
				this->updateNodes('R');
				lockRightClick = true;
			}
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Space && lockSpacebar != true)
			{
				this->updateNodes('S');
				lockSpacebar = true;
			}
			else if (ev.key.code == sf::Keyboard::M && lockM != true)
			{
				this->updateNodes('M');
				lockM = true;
			}
			else if (ev.key.code == sf::Keyboard::N && lockN != true)
			{
				this->updateNodes('N');
				lockN = true;
			}
			else if (ev.key.code == sf::Keyboard::Num1 && lockNum1 != true)
			{
				std::cout << "1 pressed" << std::endl;
				this->updateNodes('A');
				lockNum1 = true;
			}
			else if (ev.key.code == sf::Keyboard::Num2 && lockNum2 != true)
			{
				std::cout << "2 pressed" << std::endl;
				this->updateNodes('B');
				lockNum2 = true;
			}
		}
		if (ev.type == sf::Event::KeyReleased)
		{
			if (ev.key.code == sf::Keyboard::Space)
			{
				lockSpacebar = false;
			}
			else if (ev.key.code == sf::Keyboard::A)
			{
				lockNum1 = false;
			}
			else if (ev.key.code == sf::Keyboard::Num1)
			{
				lockNum2 = false;
			}
			else if (ev.key.code == sf::Keyboard::M)
			{
				lockM = false;
			}
			else if (ev.key.code == sf::Keyboard::N)
			{
				lockN = false;
			}
		}
		if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				lockLeftClick = false;
			}
			else if (ev.mouseButton.button == sf::Mouse::Right)
			{
				lockRightClick = false;
			}
		}
	}
}

// Time Complexity O(V+E) in a graph
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
	std::cout << "BFS updated" << std::endl;
}

// Time Complexity O(V+E) in a graph
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
	std::cout << "DFS updated" << std::endl;
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

void Game::render()
{
	this->window->clear();

	for (auto* node : this->nodes)
	{
		node->render(this->window);
	}

	this->window->display();
}
