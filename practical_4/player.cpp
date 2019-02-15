#include "player.h"
using namespace std;
using namespace sf;

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f))
{
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::update(double dt)
{
	//movement
	if ((Keyboard::isKeyPressed(Keyboard::W)))
	{
		move(Vector2f(0, -_speed * dt));
	}
	if ((Keyboard::isKeyPressed(Keyboard::A)))
	{
		move(Vector2f(-_speed * dt, 0));
	}
	if ((Keyboard::isKeyPressed(Keyboard::S)))
	{
		move(Vector2f(0, _speed * dt));
	}
	if ((Keyboard::isKeyPressed(Keyboard::D)))
	{
		move(Vector2f(_speed * dt, 0));
	}
	Entity::update(dt);
}

void Player::render(sf::RenderWindow &window) const
{
	window.draw(*_shape);
}