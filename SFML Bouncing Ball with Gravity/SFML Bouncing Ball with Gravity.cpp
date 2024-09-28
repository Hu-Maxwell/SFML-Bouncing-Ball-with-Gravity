#include <SFML/Graphics.hpp> 

#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");
	window.setFramerateLimit(60); 

	sf::CircleShape circle;
	circle.setRadius(50);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	sf::Vector2f position(window.getSize().x / 2, window.getSize().y / 2);
	circle.setPosition(position);

	const float gravity = +1.0f; 
	const float initialJumpVelocity = -10.0f;
	float velocityY = 0; 

	float jumpCooldown = .05f; 
	float timeSinceLastJump = 0.0f; 


	sf::Clock clock; 
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		timeSinceLastJump += deltaTime;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastJump > jumpCooldown) {
			velocityY = initialJumpVelocity;
			timeSinceLastJump = 0; 
			std::cout << velocityY; 
		}

		velocityY += gravity; 
		position.y += velocityY; 
		circle.setPosition(position.x, position.y); 
		


		window.clear(); 
		window.draw(circle);
		window.display(); 
	}
}
