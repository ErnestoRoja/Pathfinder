#include "Button.h"

// Default constructor
Button::Button()
{

}

// Constructor
Button::Button(float x, float y, float width, float height, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	if (!this->font.loadFromFile("fonts/Roboto-Regular.ttf"))
		std::cout << "ERROR:BUTTON:INITFONTS::COULD NOT LOAD FONT" << std::endl;

	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));

	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(24);
	this->text.setPosition(
		this->button.getPosition().x + (this->button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->button.getPosition().y + (this->button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->button.setFillColor(this->idleColor);
}

// Destructor
Button::~Button()
{

}

// Returns whether a button is pressed
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

// Handles what color each button should be based on its state
void Button::assignFillColor()
{
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->button.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->button.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->button.setFillColor(this->activeColor);
		break;
	default:
		this->button.setFillColor(sf::Color::Red);
		break;
	}
}

// Changes the state of a button based on user input
void Button::updateButtons(const sf::Vector2f mousePos)
{
	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->button.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
}

// Handles any changes made to a button
void Button::update(const sf::Vector2f mousePos)
{
	this->updateButtons(mousePos);
	this->assignFillColor();
}

// Renders each button and text to the window
void Button::render(sf::RenderTarget* target)
{
	target->draw(this->button);
	target->draw(this->text);
}
