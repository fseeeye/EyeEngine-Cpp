# EyeEngine-Cpp

[![License][shield1]](./LICENSE)
![Lines][shield2]

*FOA, sry for my poor English.*

## What is Eye Engine?
Eye Engine is my first Real-Time 3D Game Engine learning project. 

There are two editions: 
* [Rust Edition](https://github.com/fseeeye/EyeEngine-Rust).
* [Cpp Edition](https://github.com/fseeeye/EyeEngine-Cpp). 

They are completely independent and have different architecture & development plan! 

As I say, **Building games above this engine is not the first level target**! The main purpose of those projects is helping me to learn modern 3D Game Engine, Graphic API & SL and practice Computer Grahpic theory. 

## About Cpp Edition
I will build it from the "bottom layer", such as Entry Point / Logging System. So, it can't show any windows or render any model at run-time currently.

## Getting Started
Cpp Edition only support Windows + OpenGL yet, make sure you have the correct env.
1. Open this repo by Visual Studio. (Recommanded using Visual Studio 2022)
2. Hit `F5` to run the Game Sandbox Exe Project. 

> It will only run a `while(true)` loop yet.

## Mainly Used Librarys
* [spdlog](https://github.com/gabime/spdlog) : fast, multi-threading supported, C++ logging library.

## Reference
* [Hazel](https://github.com/TheCherno/Hazel) : Cherno have made a lot amazing Game Engine videos for that.
* [Unreal](https://github.com/EpicGames/UnrealEngine) : well-known Game Engine.


[crate]: https://crates.io/crates/eyengine
[shield1]: https://img.shields.io/github/license/fseeeye/EyeEngine-Cpp
[shield2]: https://tokei.rs/b1/github/fseeeye/EyeEngine-Cpp?category=lines
