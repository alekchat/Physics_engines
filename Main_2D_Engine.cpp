#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "SystemClass.hpp"

int ball_radious = 1.f; // defines also the boundaries
int N = 50; // number of balls, max_balls = y_pixels / (ball_radious*2)
int x_pixels = 800;
int y_pixels = 600;
int k = 50; // spring constant
//int b = 0.05f; // damping

int main() {
    ChainSystem system(N, k, ball_radious, x_pixels, y_pixels);
    
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Physics");
    window.setVerticalSyncEnabled(true); // call it once after creating the window
    sf::CircleShape circle(ball_radious);
    circle.setOrigin({float(ball_radious), float(ball_radious)}); // set the origin to the center of the circle
    circle.setFillColor(sf::Color::White);
    sf::Clock clock; 

    // ------- Initialize the fonts and texts -------- //
    sf::Font font("/System/Library/Fonts/SFNS.ttf");
    sf::Text text(font);
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);


    // ---------------------------------------------- //
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {                                                //check if the event is a key press
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {          // If pressing the up key, increase the spring const
                    system.setk(system.getk() + 10.f);}
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
                    system.setk(system.getk() - 10.f);
                }
            
            }
        }
        
        window.clear();
        const auto& pos = system.getPos();
        for (const auto& p : pos) {
            circle.setPosition(sf::Vector2f(p.x, p.y));
            window.draw(circle);
        }
        window.draw(text);
        system.update(dt);
    

        // set the string to display
        //text.setString("Use up and down keys to change the spring constant. \n ");
        text.setString("k = " + std::to_string(system.getk())+" \nUse up and down keys \nto change the spring constant.");
        // Set position (x, y)
        text.setPosition({600.f, 10.f});
        window.display();
    }

}
