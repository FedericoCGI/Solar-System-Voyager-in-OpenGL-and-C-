# Solar Systemm Voyager in OpenGL and C++

'Solar System Voyager' is a computer graphics project that simulates a spacecraft exploring the Solar System. The program's output takes you on a journey across our Solar System aboard a spaceship. This project developed in C++ and OpenGL, incorporating a variety of custom classes and libraries to manage different aspects of the 3D environment. 

![Solar System Voyager Intro](https://github.com/FedericoCGI/Solar-System-Voyager-in-OpenGL-and-Cpp/blob/main/images/solarsystemintro.png)         ![Solar System Voyager Preview](https://github.com/FedericoCGI/Solar-System-Voyager-in-OpenGL-and-Cpp/blob/main/images/solarsystempreview.png)

## Features

- Interactive Camera: Control the camera to explore planets, fly through asteroid belts, and orbit around celestial bodies.
- Realistic Texturing and Lighting: Uses OpenGL shaders to provide realistic lighting effects and detailed textures.
- Audio Integration: Background music enhances this immersive experience.
- Asteroid Belt and Planets: Asteroids Belt and Planets have been modeled and positioned in order to reproduce the Solar System as accurately as possible.

## Classes

The custom classes developed for this project are listed as follows:

- Audio: Uses the IrrKlang library to play audio during program execution
- Camera: Manages the camera's creation, settings, and movements, allowing for a 360-degree exploration of the scene.
- Mesh: Handles the 3D mesh data for imported models, including vertices, normals, and textures.
- Model: Imports 3D models into the project using the Assimp library, storing data in objects of the Mesh class.
- My Algebra: Manages mathematical operations on vectors and matrices, providing the tools needed for 3D transformations.
- Planet: Manages the rotation and revolution of each planet, simulating their real-world movements.
- Shader & ShaderLinker: Handles vertex and fragment shaders and links them to form shader programs for rendering the scene.
- Skybox: Creates a cubemap used as the background, giving the effect of an expansive universe.
- Texture: Manages texture creation and application to 3D models.
- Window: Creates and manages the window where the program runs, including user input handling.

## How It Works

The demo.cpp file contains the main() method, which brings together all the components to run the program. The scene includes models of celestial bodies that make up the solar system, such as planets, the sun, and asteroid belts. Each planet's rotation and revolution are dynamically managed to provide a realistic experience.

![SSV Window]()

