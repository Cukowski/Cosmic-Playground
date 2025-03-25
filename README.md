# COSMIC PLAYGROUND - C++ SFML + ImGui-SFML Gravity Simulation Game

A simple C++ game built with **SFML 2.6** and **ImGui-SFML**, powered by **CMake** for cross-platform support.

```
   ____   ____  _____  __  __   ____   ____   ____ 
  / ___| / ___|| ____||  \/  | |  _ \ / ___| / ___|
  \___ \ \___ \|  _|  | |\/| | | |_) | |  _  \___ \
   ___) | ___) | |___ | |  | | |  _ <| |_| |  ___) |
  |____/ |____/|_____||_|  |_| |_| \_\\____| |____/ 
```

---

## Project Structure

```
/MyProject
 ├── CMakeLists.txt
 ├── /src/
 │   ├── main.cpp
 │   ├── GravitySource.cpp
 │   ├── Particle.cpp
 │   ├── Renderer.cpp
 │
 ├── /include/
 │   ├── GravitySource.h
 │   ├── Particle.h
 │   ├── Renderer.h
 │
 ├── /external/
 │   ├── SFML/         # Contains SFML include and lib files
 │   ├── ImGui-SFML/   # Contains ImGui-SFML files
```

---

## Configure and Build the Project

### Approach 1
Run the following commands in your terminal or command prompt:

```sh
mkdir build
cd build
cmake ..
cmake --build . --config Debug
./build/Debug/GravitySimulationGame.exe  # On Windows
./build/GravitySimulationGame            # On Linux/macOS
```

**Note:** Do not reuse the `build` folder! If you recompile, delete the old build folder first.

### Approach 2
Alternatively, run:

```sh
cmake -S . -B build
cmake --build build --config Debug
./build/Debug/GravitySimulationGame.exe  # On Windows
./build/GravitySimulationGame            # On Linux/macOS
```

---

## Project Description

### GravitySource.h & GravitySource.cpp

- **GravitySource.h:**  
  Declares the `GravitySource` class—a celestial body that exerts gravitational influence over particles. It encapsulates properties such as position, gravitational strength, radius, and even orbital velocity. The header also defines the public interface to update its state, render itself, and adjust its attributes like color and strength.

- **GravitySource.cpp:**  
  Implements the functions declared in the header. It updates the source's position based on its velocity and renders it as a circle using SFML graphics. Any modification to attributes (e.g., radius or color) is immediately reflected in the visual representation, making this file the heartbeat of your gravitational entities.

---

### Particle.h & Particle.cpp

- **Particle.h:**  
  Outlines the `Particle` class. Particles are the tiny stars that dance under the gravitational influence. This header defines properties such as position, velocity, and a trail (a deque capturing the particle's path) that poetically traces its journey. It also declares methods for updating physics, rendering, and setting the particle’s color.

- **Particle.cpp:**  
  Brings the particle’s motion to life. It computes gravitational effects from all sources, updating velocity and position accordingly. The trail is managed by storing successive positions, resulting in a luminous path that narrates the particle’s orbit. This file transforms raw orbital mechanics into a visually engaging spectacle.

---

### Renderer.h & Renderer.cpp

- **Renderer.h:**  
  Declares a utility `Renderer` class, composed entirely of static methods. This class serves as the cosmic conductor, orchestrating the drawing of both particles and gravity sources. It also includes a special glow rendering function to adorn particles with an ethereal aura.

- **Renderer.cpp:**  
  Implements the rendering routines. It iterates over your collections of particles and gravity sources, drawing them onto the SFML window. The glow effect is achieved by drawing a series of concentric circles around each particle, lending a shimmering, comet-like appearance that adds depth and wonder to the simulation.

---

### main.cpp

- **main.cpp:**  
  Acts as the gateway to your application. It orchestrates the entire simulation through the following steps:
  
  - **Initialization:**  
    Sets up the SFML window and initializes ImGui for interactive settings.
  
  - **Game State Management:**  
    Implements a simple state machine (main menu vs. simulation) to separate the user interface from the simulation logic. In the main menu, users can start the simulation or exit. In simulation mode, users can dynamically create gravity sources via mouse clicks and adjust simulation parameters through ImGui.
  
  - **Update Loop:**  
    Processes events, updates the physics of particles and gravity sources, renders all entities, and overlays the ImGui interface.
  
  This file is your control center—a harmonious blend of art and computation that allows the cosmic dance to unfold interactively.

---

### CMakeLists.txt

- **CMakeLists.txt:**  
  The wizard behind the scenes that configures the build process. It performs the following functions:
  
  - Sets project settings (e.g., C++17 standard) and locates external libraries (SFML, ImGui-SFML, OpenGL).
  - Lists all source files and sets up the executable target.
  - **DLL Copying (Windows Only):** Automatically copies necessary SFML DLLs (choosing Debug or Release versions as appropriate) into the output directory, ensuring all dynamic dependencies are in place for the executable.
  
  Essentially, this file guarantees that every component of your project is in harmony, so the final executable launches smoothly with all its cosmic elements intact.

---

## Notes

- **Linux/macOS Users:**  
  Ensure SFML is installed via your package manager (`apt`, `brew`, etc.), or adjust the CMake configuration to link correctly.

- **Customizing the Project:**  
  Add your source files inside the `src/` directory and header files inside `include/`.

---

Enjoy your journey through the cosmos of code, where every line is a star and every build a new universe.

---