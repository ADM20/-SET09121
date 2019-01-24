#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::D,   // Player1 Down
	Keyboard::Left,  // Player2 UP
	Keyboard::Right // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];
void Reset()
{
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	//ball velocity
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}
void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	Reset();
	
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

	// handle paddle movement
	float p1Direction = 0.0f;
	float p2Direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y > paddleSize.y*0.5) 
	{
		p1Direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y < gameHeight - paddleSize.y*0.5) {
		p1Direction++;
	} 
	if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y > paddleSize.y*0.5) 
	{
		p2Direction--;
	} 
	if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y < gameHeight - paddleSize.y*0.5) {
		p2Direction++;
	}
	paddles[0].move(0, p1Direction * paddleSpeed * dt);
	paddles[1].move(0, p2Direction * paddleSpeed * dt);
	//move ball
	ball.move(ballVelocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) { //bottom wall
						   // bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) { //top wall
					   // top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// right wall
		server = true;
		Reset();
	}
	else if (bx < 0) {
		// left wall
		server = false;
		Reset();
	}
	else if (
		//ball is inline or behind paddle
		bx < 10+paddleSize.x && by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) 
	{
		// bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *=  1.1f;
		ball.move(0, 10);
	}
	else if (bx > (gameWidth-paddleSize.x-10) && by > paddles[1].getPosition().y - (paddleSize.y * 0.5) && by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
	{
		// bounce off right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *=  1.1f;
		ball.move(0, 10); 
	}
}

void Render(RenderWindow &window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}