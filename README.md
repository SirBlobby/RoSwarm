# ROSWARM 
A simple 2D game using Raylib.

## Building the Project
To build the project, ensure you have CMake and a C compiler installed. Then run the following commands in your terminal:

```bash
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

This will generate the necessary build files and compile the project.

## Running the Game
After building the project, you can run the game executable located in the `build` directory:
```bash
./build/game
```