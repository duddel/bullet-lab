# Bullet Lab

In this experiment, we compile `Bullet` Physics (v2.89) into a C++ executable and run a simple test program.

The `Bullet` source code is not provided in this repository, but cloned during the build step. This is done by CMake with `ExternalProject`, see: [CMakeLists.txt](CMakeLists.txt).

Configure, build and test via CMake (v3.6+), like so:

```cmake
mkdir _build
cd _build
cmake ..
cmake --build .
ctest -V
```

This builds an executable `bullet-lab`.

## Bullet (v2.89) License

    Bullet Continuous Collision Detection and Physics Library
    http://bulletphysics.org

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
