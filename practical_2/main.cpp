#include <SFML/Graphics.hpp>

//namespaces
using namespace sf;
using namespace std;

//variables
const int gameWidth = 800;
const int gameHeight = 600;

//fonts
Font font;
Text text;
Color red = Color::Green;
Color black = Color::Blue;

//sprites
Texture spritesheet;
Sprite invader;


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
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
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

}

void Render(RenderWindow &window)
{
	window.draw(text);
	window.draw(invader);
	// Draw Everything
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