#include <SFML/Graphics.hpp>
#include <iostream>
//headers
#include "ship.h"
#include "game.h"
//namespaces
using namespace sf;
using namespace std;
//fonts
Font font;
Text text;
Color red = Color::Transparent;
Color black(0,28,255,100);
//sprites
Texture spritesheet;

vector<Ship *> ships;

void Load()
{
	//load the things

	//text
	text.setString("SPACE INVADERS");
	// Load font-face from res dir
	font.loadFromFile("res/fonts/BebasNeue Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(126);
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), gameHeight / 2 - (text.getLocalBounds().height));
	text.setFillColor(red);
	text.setOutlineThickness(2);
	text.setOutlineColor(black);

	//spritesheet
	if (!spritesheet.loadFromFile("res/img/invaders/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0 + (r * 32), 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = Vector2f((((gameWidth / 2) - ((invaders_columns / 2) *40)) + 16) + (c * 40), 100 + (r * 40));
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
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

	for (auto &s : ships) {
		s->Update(dt);
	};

}

void Render(RenderWindow &window)
{
	// Draw Everything
	window.draw(text);

	for (const auto s : ships) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}