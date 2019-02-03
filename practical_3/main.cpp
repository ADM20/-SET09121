#include <SFML/Graphics.hpp>
#include <iostream>
//headers
#include "entity.h"
#include "player.h"
#include "game.h"
//namespaces
using namespace sf;
using namespace std;

vector<Entity *> entity;

void Load()
{
	//load the things
	auto player = new Player();
	entity.push_back(player);

}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}


	for (auto &e : entity)
	{
		e->update(dt);
	}
}

void Render(RenderWindow &window)
{
	// Draw Everything

	for (const auto e : entity)
	{
		e->render(window);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}