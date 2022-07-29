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
	initNeighbors();

	/*for (auto* i : this->nodes)
	{
		if (i->isStart() == true)
		{
			Start = i;
		}
		else if (i->isEnd() == true)
		{
			End = i;
		}
	}*/

	Start = &nodes[0][0];
	End = &nodes[rows_Y - 1][columns_X - 1];
}

void Game::initNeighbors()
{
	for (unsigned int y = 0; y < rows_Y; y++)
	{
		for (unsigned int x = 0; x < columns_X; x++)
		{
			if (x > 0)
				nodes[x * rows_Y + y]->neighbors.push_back(nodes[(x - 1) * rows_Y + (y + 0)]);
			if (x < columns_X - 1)
				nodes[x * rows_Y + y]->neighbors.push_back(nodes[(x + 1) * rows_Y + (y + 0)]);
			if (y > 0)
				nodes[x * rows_Y + y]->neighbors.push_back(nodes[(x + 0) * rows_Y + (y - 1)]);
			if (y < rows_Y - 1)
				nodes[x * rows_Y + y]->neighbors.push_back(nodes[(x + 0) * rows_Y + (y + 1)]);
		}
	}
}

Game::Game()
{
	this->initWindow();
	this->initNodes();
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

void Game::updateNodes()
{
	for (auto* i : this->nodes)
	{
		i->update((sf::Vector2f)this->mousePosWindow);

		/*if (i->needsUpdate == true)
		{
			updateAStarAlg();
			std::cout << "Algo is updated" << std::endl;
			i->needsUpdate == false;
		}*/

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
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Left && lockLeftClick != true)
			{
				this->updateNodes();
				lockLeftClick = true;
			}

			if (ev.mouseButton.button == sf::Mouse::Right && lockRightClick != true)
			{
				this->updateNodes();
				lockRightClick = true;
			}
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Space && lockSpacebar != true)
			{
				this->updateNodes();
				lockSpacebar = true;
			}
		}
		if (ev.type == sf::Event::KeyReleased)
		{
			if (ev.key.code == sf::Keyboard::Space)
			{
				lockSpacebar = false;
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

void Game::updateAStarAlg()
{
	/*for (unsigned int y = 0; y < rows_Y; y++)
	{
		for (unsigned int x = 0; x < columns_X; x++)
		{
			nodes[y][x].isVisited = false;
			nodes[y][x].fCost = INFINITY;
			nodes[y][x].hCost = INFINITY;
		    nodes[y][x].parent = nullptr;
		}
	}*/
	for (auto* i : this->nodes)
	{
		i->isVisited = false;
		i->fCost = INFINITY;
		i->hCost = INFINITY;
		i->parent = nullptr;
	}

	auto getDist = [](Node* P1, Node* P2)
	{
		return sqrt(pow(P2->x - P1->x, 2) + pow(P2->y - P1->y, 2));
	};

	Node* currentNode = Start;
	Start->hCost = 0.0f;
	Start->fCost = getDist(Start, End);

	std::vector<Node*> nodesToTest;
	nodesToTest.push_back(Start);

	while (!nodesToTest.empty() && currentNode != End)
	{
		std::sort(nodesToTest.begin(), nodesToTest.end(), [](const Node* a, const Node* b) { return a->fCost < b->fCost; });
			
		while (!nodesToTest.empty() && nodesToTest.front()->isVisited)
			nodesToTest.erase(nodesToTest.begin());
			
		if (nodesToTest.empty())
			break;

		currentNode = nodesToTest.front();
		currentNode->isVisited = true;
		currentNode->colorPath();

		for (auto nodeNeighbor : currentNode->neighbors)
		{
			if (!nodeNeighbor->isVisited && !nodeNeighbor->isWall)
				nodesToTest.push_back(nodeNeighbor);

			auto bestNode = currentNode->hCost + getDist(currentNode, nodeNeighbor);
			
			if (bestNode < nodeNeighbor->hCost)
			{
				nodeNeighbor->parent = currentNode;
				nodeNeighbor->hCost = bestNode;

				nodeNeighbor->fCost = nodeNeighbor->hCost + getDist(nodeNeighbor, End);
			}
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
