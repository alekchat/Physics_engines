#include <iostream>
#include <vector>

struct Vec2 {
    float x, y;
    
};

// operator + overloading for addition
inline Vec2 operator+(const Vec2& a, const Vec2 b){ // Returns a new Vec2, const so it doesn't modify the current object and reference to avoid copying
    return Vec2{a.x + b.x, a.y + b.y};
}
// operator - overloading for subtraction
inline Vec2 operator-(const Vec2& a, const Vec2 b){ // Returns a new Vec2, const so it doesn't modify the current object and reference to avoid copying
    return Vec2{a.x - b.x, a.y - b.y};
}
// operator * overloading for scalar multiplication
inline Vec2 operator*(const Vec2& a, float scalar){ // Returns a new Vec2, const so it doesn't modify the current object and reference to avoid copying
    return Vec2{a.x * scalar, a.y * scalar};
}

class ChainSystem{
    public:
        ChainSystem(int N, int k, float ball_radius, float x_pixels, float y_pixels); //Constructor
        void setk(int new_k){k = new_k;}
        int getk(){return k;}
        const std::vector<Vec2> getPos(){return pos;}
        void update(float dt);
    private:
        std::vector<Vec2> pos;
        std::vector<Vec2> vel;
        std::vector<Vec2> force;
        int k = 50; // spring constant
        int N; // number of balls
        float ball_radius; // radius of the balls
        float x_pixels; // width of the window
        float y_pixels; // height of the window
        int hx;  // overal distance that remains if we remove the diameter
        int hy;    // of the sum of the balls from the total height
        void computeForces();
        void integrate(float dt);
        Vec2 force_mag(Vec2 d, Vec2 du);

};

// Constructor for the ChainSystem class
ChainSystem::ChainSystem(int N, int k, float ball_radius, float x_pixels, float y_pixels){
    this->N = N;
    this->k = k;
    this->ball_radius = ball_radius;
    this->x_pixels = x_pixels;
    this->y_pixels = y_pixels;
    hx = (x_pixels - N*ball_radius*2)/(N+1);    // overal distance that remains if we remove the diameter
    hy = (x_pixels - N*ball_radius*2)/(N+1);    // of the sum of the balls from the total height

    int fin_dist = 0; // distance between the centers of the balls
    for (int i = 0; i < N; i++){
        if (i == 0){fin_dist = fin_dist + ball_radius + 2*hx;}
        else {fin_dist = fin_dist + ball_radius*2 + hx;}
        pos.push_back(Vec2{float(fin_dist), float(y_pixels/2)}); // distribute the balls evenly in the vertical direction
        vel.push_back(Vec2{0.f, 0.f});
        force.push_back(Vec2{0.f, 0.f});
    }
}


Vec2 ChainSystem::force_mag(Vec2 d, Vec2 du){ // num 15 is arbitrary (is in pixel units), it is the distance at which the force starts to be linear, before that it is quadratic to avoid instability
    return((d.x >= 15)||(d.y >= 15)) ? Vec2{k * (d.x - (hx+ball_radius*2)) + du.x * 0.5f, k * (d.y - (hy+ball_radius*2)) + du.y * 0.5f}
                    : Vec2{k * (d.x - (hx+ball_radius*2)) + 0.05f * (d.x - (hx+ball_radius*2)) * (d.x - (hx+ball_radius*2))+ du.x * 0.5f, k * (d.y - (hy+ball_radius*2)) + 0.05f * (d.y - (hy+ball_radius*2)) * (d.y - (hy+ball_radius*2))+ du.y * 0.5f};
}

void ChainSystem::computeForces(){
    // initialize forces to zero
    for (int i = 0; i < N; i++){
        force[i] = Vec2{0.f, 0.f};
    }
    for (int i = 0; i < N-1; i++) {
        Vec2 d = pos[i+1] - pos[i]; // distance between the centers of the balls
        Vec2 du = vel[i+1] - vel[i]; // relative velocity between the balls
        Vec2 f_vec = force_mag(d, du); 
        force[i] = force[i] + f_vec;
        force[i + 1] =force[i + 1] - f_vec; // Newton's third law
    }
}

void ChainSystem::integrate(float dt){
    for (int i = 0; i < N; i++){
        vel[i] = vel[i] + force[i]*dt;
        pos[i] = pos[i] + vel[i]*dt;

        // Boundary condition in the y direction 
        if (pos[i].x > (x_pixels - ball_radius)){
            pos[i].x = x_pixels - ball_radius;
            vel[i].x = -vel[i].x * 0.5f; // reverse velocity and apply damping
        }else if (pos[i].x < ball_radius){
            pos[i].x = ball_radius;
            vel[i].x = -vel[i].x * 0.5f; // reverse velocity and apply damping
        }else if (pos[i].y > (y_pixels - ball_radius)){
            pos[i].y = y_pixels - ball_radius;
            vel[i].y = -vel[i].y * 0.5f; // reverse velocity and apply damping
        }else if (pos[i].y < ball_radius){
            pos[i].y = ball_radius;
            vel[i].y = -vel[i].y * 0.5f; // reverse velocity and apply damping
        }
    }
}


void ChainSystem::update(float dt){
    computeForces();
    integrate(dt);
}



