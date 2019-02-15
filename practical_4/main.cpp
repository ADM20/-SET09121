#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "system_renderer.h"
#include "pacman.h"

using namespace sf;
using namespace std;

int gameWidth = 1600;
int gameHeight = 1200;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

void Load()
{
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
	
	activeScene->update(dt);
}
void Render(RenderWindow &window)
{
	Renderer::initialise(window);
	activeScene->render();
	Renderer::render();
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
	Load();

	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}