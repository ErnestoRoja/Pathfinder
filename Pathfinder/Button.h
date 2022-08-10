#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};
class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	// Private functions

public:
	Button();

	Button(float x, float y, float width, float height, std::string text, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	~Button();

	// Public Variables
	
	// Accessors
	const bool isPressed() const;

	// Public functions
	void assignFillColor();
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

