# Physics engines
*The goal of this repo is to make varius physics engines to simulate different physical phenomena.
Starts with a train of spring oscillators:*

# 2D Spring-Mass Physics Engine

A real-time 2D physics simulation written in **C++** using the **SFML graphics library**, modeling the dynamic behavior of a one-dimensional chain of interconnected masses linked by virtual springs.

This project was developed as part of my effort to strengthen my understanding of:

- classical mechanics simulation,
- numerical integration,
- object-oriented software design,
- custom vector mathematics,
- and real-time graphical rendering.

The engine visualizes a system of particles that interact through spring-like restoring forces while obeying collision boundaries inside a finite simulation window.

<img width="720" height="600" alt="train" src="https://github.com/user-attachments/assets/21bf2c69-524e-4933-9555-b534df722b85" />

---

## Project Overview

The simulation consists of **N circular masses (balls)** arranged in a horizontal chain.  
Each mass is connected to its neighboring masses through a virtual elastic force based on a simplified **Hooke-like spring model**.

At every frame, the engine performs:

1. **Force computation** between adjacent particles,
2. **Velocity and position integration** using explicit time stepping,
3. **Boundary collision handling**, and
4. **Real-time rendering** of the updated state.

The spring stiffness coefficient `k` can be modified dynamically during runtime using keyboard input, allowing direct observation of the system's physical response.

---

## Features

- Real-time 2D particle simulation
- Interactive spring-mass chain dynamics
- Adjustable spring constant during execution
- Custom lightweight `Vec2` vector math implementation
- Object-oriented encapsulation of the physical system
- Collision handling with simulation boundaries
- SFML-based graphical rendering
- Frame-independent numerical update using `dt`

---

## Project Structure

```bash
├── Main_2D_Engine.cpp      # Main rendering loop, user interaction, SFML window management
├── SystemClass.hpp         # Physics engine core, vector math, force calculation, integration
└── README.md
```

---

## Core Architecture

### 1. Custom Vector Mathematics (`Vec2`)

A lightweight two-dimensional vector structure was implemented to support:

- vector addition,
- vector subtraction,
- scalar multiplication.

This allows clean mathematical manipulation of:

- particle positions,
- velocities,
- and force vectors.

Operator overloading was used to make the physics equations more intuitive and readable.

---

### 2. `ChainSystem` Physics Class

The `ChainSystem` class encapsulates the entire physical simulation state:

- particle positions,
- velocities,
- force accumulators,
- spring stiffness,
- simulation boundaries.

It is responsible for:

### `computeForces()`
Calculates the interaction forces between neighboring particles according to the current spacing and relative velocity.

### `integrate(dt)`
Updates the system state using time-based numerical integration:

- velocity ← velocity + force × dt
- position ← position + velocity × dt

Boundary collisions are also handled here with velocity reversal and damping.

### `update(dt)`
Main public function that advances the simulation by one frame.

---

## Physics Model

Neighboring particles interact through a simplified spring law:

- if the spring elongation remains in a stable region, a linear restoring force is applied,
- for very small distances, a nonlinear correction term is introduced to improve numerical stability and avoid oscillation divergence.

A velocity-dependent damping contribution is also included through the relative velocity term.

This creates a physically plausible oscillatory chain behavior while keeping the simulation computationally lightweight.

---

## Real-Time User Interaction

During runtime:

- `↑ Up Arrow` → Increase spring constant `k`
- `↓ Down Arrow` → Decrease spring constant `k`

This allows the user to observe how stiffness affects:

- oscillation frequency,
- propagation speed,
- and overall chain responsiveness.

The current value of `k` is displayed live on screen.

---

## How to Run

### Requirements

You need:

- C++17 or later
- SFML installed and linked properly

Official SFML website:

https://www.sfml-dev.org/

---

### Compile Example (g++)

```bash
g++ Main_2D_Engine.cpp -o PhysicsEngine -lsfml-graphics -lsfml-window -lsfml-system
```

---

## Learning Objectives of this Project

This project was built to practice and demonstrate:

- translating physical equations into software,
- designing reusable simulation classes,
- real-time rendering synchronization,
- handling numerical stability issues,
- and integrating user interaction into a simulation loop.

It also serves as a foundation for more advanced future extensions such as:

- gravity,
- multi-directional spring meshes,
- rigid body collisions,
- Verlet integration,
- constraint solvers,
- or game-oriented physics systems.

---

## Future Improvements

Planned future upgrades include:

- adding true mass parameters,
- introducing global damping/friction,
- supporting mouse interaction,
- adding gravity and external forces,
- implementing better numerical integrators,
- converting the chain into a full cloth/mesh simulator.
