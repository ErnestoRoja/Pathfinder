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
	//Start = &nodes[0][0];
	//End = &nodes[rows_Y - 1][columns_X - 1];
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

void Game::render()
{
	this->window->clear();

	for (auto* node : this->nodes)
	{
		node->render(this->window);
	}

	this->window->display();
}
