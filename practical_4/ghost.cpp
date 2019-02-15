#include "ghost.h"
using namespace std;
using namespace sf;


// Constructor
Ghost::Ghost(sf::Color c) : _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.0f))
{
	_shape->setFillColor(c);
	_shape->setOrigin(sf::Vector2f(25.0f, 25.0f));
}

void Ghost::update(double dt)
{
	

	Entity::update(dt);
}

void Ghost::render(sf::RenderWindow &window) const
{
	window.draw(*_shape);
}