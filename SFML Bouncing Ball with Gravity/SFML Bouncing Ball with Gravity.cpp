#include <SFML/Graphics.hpp> 

#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball"); 
	window.setFramerateLimit(60); 

	// initializing ball and its variables
	sf::CircleShape circle;
	circle.setRadius(50);
	circle.setOrigin(0, circle.getRadius() * 2); // at bottom left
	sf::Vector2f position(window.getSize().x / 2 - circle.getRadius(), window.getSize().y / 2 + circle.getRadius());
	circle.setPosition(position);

	// defining gravity, initial jump velocity, and ball's velocity variables
	const float gravity = +1.0f; 
	const float initialJumpVelocity = -10.0f;
	float velocityY = 0; 

	// defining jump cooldown variables
	float jumpCooldown = .15f; 
	float timeSinceLastJump = 0.0f; 

	// defining and drawing ground
	sf::RectangleShape rectangle(sf::Vector2f(800, 100)); 
	float groundHeight = 500; // 100 above the bottom
	rectangle.setPosition(0, groundHeight); 

	// turns true when the ball has jumped (for the flashing red color) 
	bool jumped = false; 


	sf::Clock clock; 
	while (window.isOpen()) {
		// calculates how much time has passed since last jump
		float deltaTime = clock.restart().asSeconds(); 
		timeSinceLastJump += deltaTime;  

		sf::Event event;
		while (window.pollEvent(event)) {
			// since this is a one time action (one time press) it is inside the polling loop
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// since this is a continuous action (not a one time press), it is outside the loop
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastJump > jumpCooldown) {
			velocityY = initialJumpVelocity;
			timeSinceLastJump = 0; 
			jumped = true; 
		}

		// sets the color to be red after jump
		if (timeSinceLastJump < .15 && jumped == true) {
			circle.setFillColor(sf::Color::Red);
		} else {
			circle.setFillColor(sf::Color::White);
		}

		// changes the position according to the velocity
		position.y += velocityY;

		// if it is on ground, stop its velocity
		if (position.y >= groundHeight) {
			position.y = groundHeight; 
			velocityY = 0;
		} // if it is touching roof, stop its velocity
		else if (position.y < circle.getRadius() * 2) {
			position.y = circle.getRadius() * 2; 
			velocityY = 0; 
		} else { // if it is neither on ground or touching roof, velocity is being affected by gravity
			velocityY += gravity;
		}

		circle.setPosition(position.x, position.y); 

		window.clear(); 
		window.draw(circle);
		window.draw(rectangle); 
		window.display(); 
	}
}
