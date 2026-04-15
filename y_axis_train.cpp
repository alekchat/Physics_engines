#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


int ball_radious = 1.f; // defines also the boundaries
int N = 50; // number of balls, max_balls = y_pixels / (ball_radious*2)
int x_pixels = 800;
int y_pixels = 600;
int k = 50; // spring constant
//int b = 0.05f; // damping
bool flag = true;
std::vector<sf::Vector2f> pos;
std::vector<sf::Vector2f> vel;
std::vector<sf::Vector2f> force;

int h = (x_pixels - N*ball_radious*2)/(N+1);    // overal distance that remains if we remove the diameter
                                                // of the sum of the balls from the total height
// If h is negative, it means that the balls are too big to fit in the window, so we need to reduce the number of balls or the size of the balls
int fin_dist = 0; // distance between the centers of the balls

int h_x = (x_pixels - N*ball_radious*2)/(N+1);    // overal distance that remains if we remove the diameter
                                                // of the sum of the balls from the total width

// ----------- Compute forces and integration for y axis ----------- //

float force_mag(float d, float du){
    return (d >= 15) ? k * (d - (h+ball_radious*2)) + du * 0.5f
                    : k * (d - (h+ball_radious*2)) + 0.05 * (d - (h+ball_radious*2)) * (d - (h+ball_radious*2))+ du * 0.5f;
}

void computeForces(){

    // initialize forces to zero
    for (int i = 0; i < N; i++){
        force[i] = sf::Vector2f(0.f, 0.f);
    }
    for (int i = 0; i < N-1; i++) {
        float d = pos[i+1].x - pos[i].x; // distance between the centers of the balls
        float du = vel[i+1].x - vel[i].x; // relative velocity between the balls
        //float f = k * (d - (h+ball_radious*2));
        float f = force_mag(d, du);
        if (flag){
            std::cout << "Dist d: " << d << std::endl;
            std::cout << "h: " << h << std::endl;
            std::cout << d-h << std::endl;
            flag = false;
        }
        force[i].x = force[i].x + f;
        force[i + 1].x =force[i + 1].x - f; // Newton's third law
    }
}

void integrate(float dt){
    for (int i = 0; i < N; i++){
        vel[i].x = vel[i].x + (force[i].x)*dt;
        pos[i].x = pos[i].x + vel[i].x*dt;

        // Boundary condition in the y direction (bottom)
        if (pos[i].x > x_pixels - ball_radious){
            pos[i].x = x_pixels - ball_radious;
            vel[i].x = -vel[i].x * 0.5f; // reverse velocity and apply damping
        }else if (pos[i].x < ball_radious){
            pos[i].x = ball_radious;
            vel[i].x = -vel[i].x * 0.5f; // reverse velocity and apply damping
        }
    }
}
// ----------------------------------------------------------------- //

// --------- Compute forces and integrate for both axes ---------//
// void computeForces(){

//     // initialize forces to zero
//     for (int i = 0; i < N; i++){
//         force[i] = sf::Vector2f(0.f, 0.f);
//     }
//     for (int i = 0; i < N-1; i++) {
//         float d = pos[i+1].y - pos[i].y; // distance between the centers of the balls
        
//         float f = k * (d - (h+ball_radious*2));
//         if (flag){
//             std::cout << "Dist d: " << d << std::endl;
//             std::cout << "h: " << h << std::endl;
//             std::cout << d-h << std::endl;
//             flag = false;
//         }
//         force[i].y = force[i].y + f;
//         force[i + 1].y =force[i + 1].y - f; // Newton's third law
//     }
// }

// void integrate(float dt){
//     for (int i = 0; i < N; i++){
//         vel[i].y = vel[i].y + (force[i].y)*dt;
//         pos[i].y = pos[i].y + vel[i].y*dt;

//         // Boundary condition in the y direction (bottom)
//         if (pos[i].y > y_pixels - ball_radious){
//             pos[i].y = y_pixels - ball_radious;
//             vel[i].y = -vel[i].y * 0.5f; // reverse velocity and apply damping
//         }
//     }
// }



int main() {
    
    // ----------- Initialize the positions of the balls on y axis ----------- //
    for (int i = 0; i < N; i++){
        if (i == 0){fin_dist = fin_dist + ball_radious + 2*h;}
        else {fin_dist = fin_dist + ball_radious*2 + h;}
        pos.push_back(sf::Vector2f(fin_dist*0.2, y_pixels/2)); // distribute the balls evenly in the vertical direction
        vel.push_back(sf::Vector2f(0.f, 0.f));
        force.push_back(sf::Vector2f(0.f, 0.f));
    }
    // ------------------------------------------------------------------------- //

    // ---------- Initialize the positions of the balls on both axes ----------- //
    // There should also be ways of initializing velocities and forces.
    // for (int i = 0; i < N; i++){
    //     if (i == 0){fin_dist = fin_dist + ball_radious + h;}
    //     else {fin_dist = fin_dist + ball_radious*2 + h;}
    //     pos.push_back(sf::Vector2f(x_pixels/2, fin_dist)); // distribute the balls evenly in the vertical direction
    //     vel.push_back(sf::Vector2f(0.f, 0.f));
    //     force.push_back(sf::Vector2f(0.f, 0.f));
    // }
    // -------------------------------------------------------------------------- //


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
                    k += 10.f;}
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
                    k -= 10.f;
                }
            
            }
        }
        computeForces();
        integrate(dt);
        window.clear();
        for (const auto& p : pos) {
            circle.setPosition(p);
            window.draw(circle);
        }
        window.draw(text);
        
        

        // set the string to display
        text.setString("k = " + std::to_string(k));
        // Set position (x, y)
        text.setPosition({700.f, 10.f});
        window.display();
    }

}



// int main()
// {


//     float k = 50.0f;              // Hooke's law spring constant
//     float m = 1.0f;              // mass
//     float b = 0.05f;             // damping
//     float F, F1, F2 = 0.0f;              // external force
//     float a = 0.0f;              // acceleration
//     float la = 100.f;             // equilibrium position
//     float lb = 200.f;             // initial position2
//     float va = 100.0f;              // initial velocity
//     float vb = -50.0f;              // initial velocity2
//     float y1 = la;
//     float v1 = va;
//     float y2 = lb;
//     float v2 = vb;

//     sf::RenderWindow window(sf::VideoMode({800, 600}), "Physics");
//     sf::CircleShape ball(10.f);
//     sf::CircleShape ball2(10.f);
//     ball.setFillColor(sf::Color::Green);
//     ball.setPosition({400.f, la});
//     ball2.setFillColor(sf::Color::Green);
//     ball2.setPosition({400.f, la});
//     sf::Clock clock;

//     while (window.isOpen())
//     {
//         float dt = clock.restart().asSeconds();

//         while (const std::optional event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();
//         }

//         // Move the ball as it is in a spring (simple harmonic motion)
//         // ---- Physics ----
//         // Compute distance
//         float d = y2 - y1; // distance between the two balls
//         // Compute spring force
//         F = k*(d - (lb - la)) - b * (v2 - v1); // F = -k(x - x0) - b(v2 - v1)
//         F1 = F;
//         F2 = -F; // Newton's third law

//         v1 = v1 + (F1 / m)*dt;
//         v2 = v2 + (F2 / m)*dt;
//         y1 = y1 + v1*dt;
//         y2 = y2 + v2*dt;
//         // Boundary condition in the y direction (bottom)
//         if (y1 > 560){
//             y1 = 560;
//             v1 = -v1 * 0.5f; // reverse velocity and apply damping
//         }

//         ball.setPosition({400.f, y1});
//         ball2.setPosition({400.f, y2});


//         auto pos1 = ball.getPosition();
//         auto pos2 = ball2.getPosition();
//         if (pos1.y > 560){
//             ball.setPosition({pos1.x, 560});}
//         else if (pos2.y > 560){
//             ball2.setPosition({pos2.x, 560});
//         }

//         //std::cout << "Ball position: (" << pos.x << ", " << pos.y << ")\n";
//         window.clear();
//         window.draw(ball);
//         window.draw(ball2);
//         window.display();
//     }
// }


