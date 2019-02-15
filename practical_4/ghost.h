#pragma once

#include "entity.h"

class Ghost : public Entity
{
private:
	float _speed;
	static int amount;
	int _g_id;
	static std::vector<sf::Color> _colours;
public:
	Ghost();
	void update(double dt) override;
	void render(sf::RenderWindow &window) const override;
};