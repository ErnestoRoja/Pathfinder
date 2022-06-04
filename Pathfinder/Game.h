#pragma once
#include "Node.h"

class Game
{
private:
	// Window
	sf::RenderWindow* window;

	// Resources
	const float screenWidth = 1920.0f;
	const float screenHeight = 1080.0f;
	const sf::Vector2f nodeSize = { 50, 50 };
	//const size_t 

	// Private functions
	void initWindow();

public:
	Game();
	virtual ~Game();

	// Public functions
	void run();

	void update();
	void updatePollEvents();

	void render();
};

