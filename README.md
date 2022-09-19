# EyeEngine-Cpp

[![License][shield1]](./LICENSE)
<!-- ![Lines][shield2] -->

*FOA, sry for my poor English.*

## What is Eye Engine?
Eye Engine is my first Real-Time 3D Game Engine learning project. 

There are two editions: 
* [Rust Edition](https://github.com/fseeeye/EyeEngine-Rust). (suspend development until I found game-dev job.)
* [Cpp Edition](https://github.com/fseeeye/EyeEngine-Cpp). 

They are completely independent and have different architecture & development plan! 

As I say, **Building games above this engine is not the first level target**! The main purpose of those projects is helping me to learn modern 3D Game Engine, Graphic API & SL and practice Computer Grahpic theory. 

## About Cpp Edition
I will build it from the "bottom layer", such as Entry Point / Logging System. So, it will add advanced features slowly.😶‍🌫️

## Getting Started
Cpp Edition only support Windows + OpenGL yet, make sure you have the correct env.
1. `git clone --recursive https://github.com/fseeeye/EyeEngine-Cpp.git`
2. Open this repo by Visual Studio. (Recommanded using Visual Studio 2022)
3. Hit `F5` to run the Game Sandbox Example Project. 

## Dev Guide
* update submodules: `git submodule update --recursive --remote`.
* use [commitizen](https://www.npmjs.com/package/commitizen) commit changes.

## RoadMap
- [X] Basic System
  - [X] Logging System
  - [X] Build System
  - [X] Event System & Polling Input
  - [X] PCH
  - [X] OpenGL Support
  - [X] ImGUI
  - [X] Keycode & Mousecode
  - [X] Math Support
- [X] Abstract Rendering basis
  - [X] (Vertex & Index) Buffer
  - [X] Vertex Buffer Layout
  - [X] Vertex Array
  - [X] Shader
  - [X] Draw Call
  - [X] 2D Camera (View & Projection Transform)
  - [X] DeltaTime
  - [X] Model Transform
- [ ] Material System / Asset System
  - [X] Shader Asset
  - [X] Texture Asset
  - [X] Shader Library
  - [ ] Model Asset
- [ ] 2D Renderer (target: Batch Rendering + 60fps + with 100-200k textures)
	- [X] Orthographic Camera
	- [X] Handle resize properly
- [ ] Serialization
- [ ] Entity Component System
- [ ] Level Format
- [ ] Tools
- [ ] Scripting

## Mainly Used Librarys
* [glfw](https://github.com/glfw/glfw) : multi-platform library for OpenGL, OpenGL ES and Vulkan, which provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc. The only regret is that GLFW doesn't support DirectX.
* [glad](https://github.com/Dav1dde/glad) : modern OpenGL wrapper.
* [glm](https://github.com/g-truc/glm) : header only C++ mathematics library for graphics software which is like GLSL spec.
* [ImGui](https://github.com/ocornut/imgui) : amazing Graphic UI lib.
* [spdlog](https://github.com/gabime/spdlog) : fast, multi-threading supported, C++ logging library.
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) : single-file image loader.

## Dependence Binarys
* [premake](https://github.com/premake/premake-core/) : perform build configuration tasks or generate project files for toolsets like Visual Studio, Xcode, and GNU Make. 

## Reference
* [Hazel](https://github.com/TheCherno/Hazel) : Cherno have made a lot amazing Game Engine videos for that.
* [Unreal](https://github.com/EpicGames/UnrealEngine) : well-known Game Engine.


[crate]: https://crates.io/crates/eyengine
[shield1]: https://img.shields.io/github/license/fseeeye/EyeEngine-Cpp
<!-- [shield2]: https://tokei.rs/b1/github/fseeeye/EyeEngine-Cpp?category=lines -->
