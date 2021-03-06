#include "ship.h"
#include "game.h"
//namespaces
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed = 24;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
  _sprite = ir;
  setTexture(spritesheet);
  setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


//invader class inherits from ship
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 1; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}
}

//TODO ************************************
///***********************************************//
///aa/
///********************
//player class inheritst from ship
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	//Move left
	if ((Keyboard::isKeyPressed(Keyboard::A)) && getPosition().x < 16)
	{
		move(-100 * dt, 0);
	}

	//Move Right
	if ((Keyboard::isKeyPressed(Keyboard::D)))// && getPosition().x < 16)
	{
		move(100 * dt, 0);
	}
}