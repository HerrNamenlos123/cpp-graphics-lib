# Welcome to cppgfx!

## What is cppgfx?

cppgfx is a C++17 graphics library, which is heavily inspired by [Processing](https://processing.org/). 
It is designed to be easy to use, while still being fast and flexible. The main goal is to encourage beginner programmers
to program their own ideas while having a ton of features at their fingertips. 

It was created because usually students are taught programming by using the command line, which is not very exciting.
cppgfx tries to change this so that students already have a boilerplate project and can bring their own ideas to life.
Projects can range from simple visual effects to fully featured games and scientific data visualization.

### What's under the hood?

cppgfx is based on some of the best supported C++ libraries, such as [SFML](https://www.sfml-dev.org/)
and [Dear ImGui](https://github.com/ocornut/imgui). The bridge is provided by [ImGui-SFML](https://github.com/SFML/imgui-sfml).

SFML is a graphics framework targeted at 2D game development, while ImGui is a GUI library. This allows you to
create gorgeous minigames with pretty GUI, or whatever you would like to visualize.

There are more libraries in cppgfx, for example [spdlog](https://github.com/gabime/spdlog) for logging and
[glm](https://github.com/g-truc/glm) for vector math and matrix operations. Many others are not yet listed or yet to come.

Additionally, a serial library for Arduino communication is planned, as well as one for 3D rendering.
Feel free to file an issue if you have any feature ideas or suggestions for future libraries!

## When NOT to use cppgfx?

cppgfx is NOT a fully featured game engine or alike, and is not intended to be used for any sort of production. You
can use it however you like, but it was never designed for more than mid-sized educational projects on a single computer.

## How to use cppgfx?

cppgfx is designed to be as simple to use as possible, while still adhering to best practices and teaching proper
project layout. 

### Installation

#### Prerequisites

To use cppgfx, you need:

- CMake 3.16 or higher
  - [Download Windows Installer](https://github.com/Kitware/CMake/releases/download/v3.28.0-rc2/cmake-3.28.0-rc2-windows-x86_64.msi)
  - Installing on Linux: `sudo apt update && sudo apt install -y cmake`

```bash
to be done
```