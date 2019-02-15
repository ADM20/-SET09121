#include "pacman.h"
#include "system_renderer.h"
#include "player.h"
#include "ghost.h"

//pacman.cpp
void Scene::update(double dt){_ents.update(dt);}
void Scene::render() { _ents.render(Renderer::getWindow()); }

vector<shared_ptr<Entity>> &Scene::getEnts() { return _ents.list; }


//game
void GameScene::load()
{
	// Player
	std::shared_ptr<Entity> player = std::make_shared<Player>();
	_ents.list.push_back(std::move(player));

	// Ghosts
	std::shared_ptr<Entity> ghost1 = std::make_shared<Ghost>(sf::Color::Red);
	_ents.list.push_back(std::move(ghost1));
	std::shared_ptr<Entity> ghost2 = std::make_shared<Ghost>(sf::Color::Green);
	_ents.list.push_back(std::move(ghost2));
	std::shared_ptr<Entity> ghost3 = std::make_shared<Ghost>(sf::Color::Magenta);
	_ents.list.push_back(std::move(ghost3));
	std::shared_ptr<Entity> ghost4 = std::make_shared<Ghost>(sf::Color::Blue);
	_ents.list.push_back(std::move(ghost4));
}
void GameScene::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}
void GameScene::render()
{
	Scene::render();
}

void GameScene::respawn(){}

//menu
void MenuScene::load()
{
	font.loadFromFile("res/fonts/BebasNeue Regular.ttf");
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(64);
	// Set text position
	text.setPosition((gameWidth * .5f) , gameHeight * 0.5f);
}
void MenuScene::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}
void MenuScene::render()
{
  Renderer::queue(&text);
  Scene::render();
}
