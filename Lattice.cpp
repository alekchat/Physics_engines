#include <iostream>
#include <vector>
#include <SFML/System.hpp>

class Lattice {
public:
    int Nx, Ny;
    int N;

    float spacing;   // distance between atoms
    float mass;

    std::vector<sf::Vector2f> pos;
    std::vector<sf::Vector2f> vel;
    std::vector<sf::Vector2f> force;

    Lattice(int nx, int ny, float spacing_, float mass_); //Constructor

    int index(int i, int j) const{
        return i * Ny + j;
    }

    void get_lattice_dim(){
        std::cout<<"Lattice dimensions: "<<Nx<<" x "<<Ny<<std::endl;
    }
    void get_pos(int i, int j){
        int k = index(i,j);
        std::cout<<"Position of atom ("<<i<<","<<j<<"): "<<pos[k].x<<" , "<<pos[k].y<<std::endl;
    }

    void resetForces();
    void computeForces();   // we’ll fill this next
    void integrate(float dt);
};
//Constructor definition
Lattice::Lattice(int nx, int ny, float spacing_, float mass_):
    Nx(nx), Ny(ny), N(nx*ny), spacing(spacing_), mass(mass_){
        N = Nx * Ny;
        pos.resize(N);
        vel.resize(N);
        force.resize(N);
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Ny; j++) {
                int k = index(i,j);
                pos[k] = sf::Vector2f(i*spacing, j*spacing);
                vel[k] = sf::Vector2f(0.f, 0.f);
                force[k] = sf::Vector2f(0.f, 0.f);
            }
        }
    }
int main(){
    std::cout<<"Works!"<<std::endl;
    int i = 2;
    float j = 1;
    Lattice My_lattice(i, i, j, j);
    My_lattice.get_lattice_dim();
    My_lattice.get_pos(1, 1);
    return 0;
}