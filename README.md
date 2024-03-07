<div align="center">
    <h1><code>🏆</code> Precious Moment</h1>
    <p>
        <strong>OpenGL 3D Model Viewer - Precious Moment with C++ and <a href="https://www.glfw.org/">GLFW</a></strong>
        <br />
        <sub>Created by <a href="https://pungrumpy.com">Pungrumpy</a></sub>
    </p>
    <p>
        <!-- <img src="./.github/images/preview.mp4" alt="Preview" /> -->
        <img src="./.github/images/preview.gif" alt="Preview" width="50%" height="auto" />
    </p>
    <p>
        <a href="https://img.shields.io/badge/OpenGL-3D%20Model%20Viewer-blue?style=for-the-badge&logo=opengl">
            <img src="https://img.shields.io/badge/OpenGL-3D%20Model%20Viewer-blue?style=for-the-badge&logo=opengl" alt="OpenGL 3D Model Viewer" />
        </a>
        <a href="https://img.shields.io/badge/C++-Programming%20Language-blue?style=for-the-badge&logo=c%2B%2B">
            <img src="https://img.shields.io/badge/C++-Programming%20Language-blue?style=for-the-badge&logo=c%2B%2B" alt="C++ Programming Language" />
        </a>
        <a href="https://img.shields.io/badge/GLFW-Library-blue?style=for-the-badge&logo=glfw">
            <img src="https://img.shields.io/badge/GLFW-Library-blue?style=for-the-badge&logo=glfw" alt="GLFW Library" />
        </a>
    </p>
</div>

## 📜 Description

This is a simple 3D model viewer using OpenGL and GLFW. The model is a Precious Moment figurine. The model is loaded from an OBJ file and the texture is loaded from a PNG file. The model can be rotated using the WASD keys.

## 🚀 Getting Started

### Prerequisites

- **[CMake](https://cmake.org/)** - Build system
- **[GLFW](https://www.glfw.org/)** - Library for creating windows with OpenGL contexts and receiving input and events
- **[GLAD](https://glad.dav1d.de/)** - OpenGL loader
- **[GLM](https://github.com/g-truc/glm)** - Mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications
- **[KHR](https://registry.khronos.org/EGL/api/KHR/khrplatform.h)** - Khronos header file

### Installing

1. Clone the repository

   ```sh
   git clone
   ```

2. Build the project

   ```sh
   cmake -S . -B build
   cmake --build build
   ```

3. Run the project
   ```sh
   cd build
   ./PreciousMoment
   ```

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details
