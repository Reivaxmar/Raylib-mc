# Raylib mc
This project is an attempt to make a Minecraft clone in C++ using Raylib.

## Usage
### Prerequisites
Just some basic stuff:
- Modern C/C++ compiler
- CMake installed

### Building the project
You can either download the project as a ZIP file or clone the repository using Git:
```bash
> git clone https://github.com/Reivaxmar/Raylib-mc
> cd Raylib-mc
```

Once you have the project, build it with:
```bash
> bash ./setup.sh
> cmake --build build
> ./mc
...
```

The project should be up and running.


## External libraries
There is no need to have them installed, CMake will do it:
- [Raylib](https://www.raylib.com/), for the window, UI, controls, etc.
- [nlohmann/json](https://github.com/nlohmann/json) for parsing the block data.
- [siv::PerlinNoise](https://github.com/Reputeless/PerlinNoise), for generating the terrain.

## TODOs
- [x] Implement basic chunk
- [x] JSON block loading
- [x] Infinite terrain generation
- [ ] Remove faces between chunks
- [x] Multithreaded world generation
- [ ] Block placing/deleting
- [ ] Visuals (skybox, occlusion, etc)
- [x] Better player movement
- [ ] Basic inventory + UI