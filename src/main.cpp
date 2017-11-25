#include <SFML/Graphics.hpp>
#include "Particals.h"
#include "Consts.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(dim::width, dim::height), "Particals");

    Particals parts;

    printf("Controls:\n\n");
    printf("    Left Click  - Add Positive Partical\n");
    printf("    Right Click - Add Negitive Partical\n\n");
    printf("    W - Toggle Wrap\n\n");
    printf("    Space - Clear\n");


	// Start the game loop
	sf::Clock clock;
	float lastTime = 0;
	float currentTime = clock.restart().asSeconds();
	float fps = 1.f / currentTime;
	float tempFPS = 0;
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            parts.addPart(true, sf::Mouse::getPosition(app));
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){currentTime = clock.restart().asSeconds(); fps = 1.f / currentTime;}
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            parts.addPart(false, sf::Mouse::getPosition(app));
            while(sf::Mouse::isButtonPressed(sf::Mouse::Right)){currentTime = clock.restart().asSeconds(); fps = 1.f / currentTime;}
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            parts.reset();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            parts.wrap = !parts.wrap;
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){currentTime = clock.restart().asSeconds(); fps = 1.f / currentTime;}
        }

        // Clear screen
        if(parts.wrap){
            app.clear(sf::Color(32,0,32));
        } else {
            app.clear(sf::Color(0,32,0));
        }

        parts.update(fps, app);

        // Update the window
        app.display();

		currentTime = clock.restart().asSeconds();
		fps = 1.f / currentTime;
    }

    return EXIT_SUCCESS;
}









