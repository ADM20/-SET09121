#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Entity
{
protected:
	unique_ptr<Shape> _shape;
	Vector2f _position;
	Entity(unique_ptr<Shape> shp);
public:
	Entity() = delete;
	virtual ~Entity() = default;
	
	virtual void update(const double dt);
	virtual void render(RenderWindow &window) const = 0;

	const Vector2f getPosition();
	void setPosition(const Vector2f &pos);
	void move(const Vector2f &pos);
};

struct EntityManager
{
	vector<shared_ptr<Entity>> list;
	void update(double dt);
	void render(RenderWindow &window);
};