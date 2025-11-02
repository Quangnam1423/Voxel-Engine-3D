# 🚀 Voxel Engine OpenGL

![Engine Demo](assets/engine.gif)

A lightweight **voxel engine** written in **C++** using **OpenGL** for real-time rendering and visualization.  
The project focuses on creating a foundational rendering framework that can be extended for game engines, simulation systems, or visualization tools.

---

## 📦 Dependencies

This project relies on three core libraries:

### 🧱 [GLFW3](https://www.glfw.org/)
- Used for window creation, OpenGL context management, and input handling (keyboard, mouse).
- Recommended version: **3.3 or higher**

### ⚙️ [GLAD](https://glad.dav1d.de/)
- Used for loading and managing OpenGL functions dynamically.
- Compatible with **OpenGL 4.5 Core Profile** and newer.

### 📐 [GLM](https://github.com/g-truc/glm)
- A header-only math library that mirrors GLSL syntax.
- Provides matrix, vector, quaternion operations, and 3D transformations.

---

## 🗂️ Project Structure

The general structure of the project is as follows:

``` tree directory
Source
|   Engine.cpp
|   Engine.h
|   fastnoiselifeImpl.cpp
|   glad.c
|   main.cpp
|   movement.h
|   Singleton.h
|   tsb_image_imple.cpp
|   WindowConfig.h
|
+---EngineManager
|       CameraManager.cpp
|       CameraManager.h
|       InputManager.cpp
|       InputManager.h
|       ResourceManager.cpp
|       ResourceManager.h
|       WindowManager.cpp
|       WindowManager.h
|
+---Ingredient
|       Material.h
|       Mesh.cpp
|       Mesh.h
|       Model.cpp
|       Model.h
|       ModelVertex.h
|       Texture.h
|
\---Objects
        Camera.cpp
        Camera.h
        Chunk.cpp
        Chunk.h
        ChunkManager.cpp
        ChunkManager.h
        ChunkMesh.cpp
        ChunkMesh.h
        Shader.cpp
        Shader.h
        Skybox.cpp
        Skybox.h
        Vertex.h
        Voxel.cpp
        Voxel.h
        VoxelFace.h
        WoodBox.cpp
        WoodBox.h
        World.cpp
        World.h
```

## 📜 License

This project is licensed under the [MIT License](LICENSE).