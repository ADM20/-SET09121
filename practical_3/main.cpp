#include <SFML/Graphics.hpp>
#include <iostream>
#include "levelsystem.h"
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

	ls::loadLevelFile("res/maze_2.txt");
	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
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
	ls::render(window);
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