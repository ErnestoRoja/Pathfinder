#include "Button.h"

Button::Button()
{

}

Button::Button(float x, float y, float width, float height, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{

	this->buttonState = BTN_IDLE;

	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
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

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

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

void Button::updateButtons(const sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->button.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
}

void Button::update(const sf::Vector2f mousePos)
{
	this->updateButtons(mousePos);
	this->assignFillColor();
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->button);
	target->draw(this->text);
}
