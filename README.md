# WyvernEngine

[![Build status](https://ci.appveyor.com/api/projects/status/4ylftugcf8tkay3e/branch/master?svg=true)](https://ci.appveyor.com/project/NebulousDev/wyvernengine/branch/master)   <- This will likely be broken until I fix dependency issues

Wyvern Engine is a 2D and 3D game engine developed in C/C++

## Features

**Available:**
- Platforms
    - Windows x86 / x64
- Render APIs
    - OpenGL 3+
        - Context Creation
    - Direct3D 11
        - Context Creation
        - Input Layouts (Shader-Independent)
        - Vertex / Index Buffers
        - Vertex Shaders
        - Pixel Shaders
- Hot-loadable DLLs
- Hot-swappable Render APIs
- Platform Independant DLL Loading (runtime)
- Separated Platform - Engine code
- Separated Engine - Game code
- Multiple Window Support

**Planned:**
- Platforms
    - Linux x86 / x64
    - MacOS
    - Consoles (?)
- Render APIs
    - OpenGL ES
    - Vulkan
    - Direct3D 9 (maybe for older platforms)
    - Direct3D 12
- Geometry / Tesselation
- Full Render Pipeline
- Component Render/Entity System
- Physics Engine (Bullet or maybe custom?)
- OBJ/FBX/DAE Loading
- Custom Texture and Model formats
- Tools
    - Full UI/ World Editor
    - Texture Editor
    - Visual Shaders
    - Shader Material Graph
- Plugin/Mod support

## Build

**Git:**

    git clone https://github.com/NebulousDev/WyvernEngine.git

**Dependencies:**

(Build path in progress)

- Windows SDK (W8+)
- Vulkan SDK
- GLEW

## Versioning

Versioning is as follows:

    [Release].[Major].[Minor]<Patch>


## Copyright

Copyright 2018 Ben Ratcliff. All rights reserved.
WyvernEngine is protected under the Apache License 2.0. [[LICENSE](LICENSE)]
