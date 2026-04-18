#include <iostream>

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
        ChainSystem(int N, float ball_radius, float x_pixels, float y_pixels); //Constructor
    private:
        std::vector<Vec2> pos;
        std::vector<Vec2> vel;
        std::vector<Vec2> force;

};

// Constructor for the ChainSystem class
ChainSystem::ChainSystem(int N, float ball_radius, float x_pixels, float y_pixels){
    int h = (x_pixels - N*ball_radius*2)/(N+1);    // overal distance that remains if we remove the diameter
                                                 // of the sum of the balls from the total height
    int fin_dist = 0; // distance between the centers of the balls
    for (int i = 0; i < N; i++){
        if (i == 0){fin_dist = fin_dist + ball_radius + 2*h;}
        else {fin_dist = fin_dist + ball_radius*2 + h;}
        pos.push_back(Vec2{float(fin_dist*0.2), float(y_pixels/2)}); // distribute the balls evenly in the vertical direction
        vel.push_back(Vec2{0.f, 0.f});
        force.push_back(Vec2{0.f, 0.f});
    }
}

int main() {
    Vec2 v1{1.0f, 2.0f};
    Vec2 v2 =  v1* 0.2f; // Scalar multiplication

    std::cout << "v3: (" << v2.x << ", " << v2.y << ")" << std::endl;

    return 0;
}