#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Game
{
private:
	// Window
	sf::RenderWindow* window;

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

