#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{


    float k = 50.0f;              // Hooke's law spring constant
    float m = 1.0f;              // mass
    float b = 0.05f;             // damping
    float F, F1, F2 = 0.0f;              // external force
    float a = 0.0f;              // acceleration
    float la = 100.f;             // equilibrium position
    float lb = 200.f;             // initial position2
    float va = 100.0f;              // initial velocity
    float vb = -50.0f;              // initial velocity2
    float y1 = la;
    float v1 = va;
    float y2 = lb;
    float v2 = vb;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Physics");
    sf::CircleShape ball(10.f);
    sf::CircleShape ball2(10.f);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition({400.f, la});
    ball2.setFillColor(sf::Color::Green);
    ball2.setPosition({400.f, la});
    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Move the ball as it is in a spring (simple harmonic motion)
        // ---- Physics ----
        // Compute distance
        float d = y2 - y1; // distance between the two balls
        // Compute spring force
        F = k*(d - (lb - la)) - b * (v2 - v1); // F = -k(x - x0) - b(v2 - v1)
        F1 = F;
        F2 = -F; // Newton's third law

        v1 = v1 + (F1 / m)*dt;
        v2 = v2 + (F2 / m)*dt;
        y1 = y1 + v1*dt;
        y2 = y2 + v2*dt;
        // Boundary condition in the y direction (bottom)
        if (y1 > 560){
            y1 = 560;
            v1 = -v1 * 0.5f; // reverse velocity and apply damping
        }

        ball.setPosition({400.f, y1});
        ball2.setPosition({400.f, y2});


        auto pos1 = ball.getPosition();
        auto pos2 = ball2.getPosition();
        if (pos1.y > 560){
            ball.setPosition({pos1.x, 560});}
        else if (pos2.y > 560){
            ball2.setPosition({pos2.x, 560});
        }

        //std::cout << "Ball position: (" << pos.x << ", " << pos.y << ")\n";
        window.clear();
        window.draw(ball);
        window.draw(ball2);
        window.display();
    }
}

// How to run the compiler:
// clang++ test.cpp -o app \
// -I /Users/alex/Downloads/SFML-3.0.2/include/ \
// -lsfml-graphics \
// -lsfml-window \
// -lsfml-system \
// -std=c++17 -L /Users/alex/Downloads/SFML-3.0.2/lib -Wl,-rpath,/Users/alex/Downloads/SFML-3.0.2/lib