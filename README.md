# Software 3D Renderer
A 3D renderer I wrote during a games jam at work. The game is inspired by Monolith's Blood (1997). All rendering is done entirely in software on the CPU. As such it does not require an accelerated GPU and should work quite nicely in emulators and virtualisers.

To enable parallelisation in the renderer, set the corresponding flag in the CMakeLists.txt to enable OpenMP in capable compilers. Note that currently pthreads are also supported on compatible systems.

<img src="https://raw.githubusercontent.com/osen/software-3d-renderer/master/docs/ss1.png" width="250" />
<img src="https://raw.githubusercontent.com/osen/software-3d-renderer/master/docs/ss2.png" width="250" />

Everything was written pretty much from scratch in C++ and due to the fact that no GPU is needed the project has barely any dependencies and is fairly portable to most platforms. The only ones I have tested on are OpenBSD and Windows.

The renderer, engine and game can be built and run using the following:

    $ mkdir build
    $ cd build
    $ cmake .. -DCMAKE_BUILD_TYPE=Release
    $ cd ..
    $ cmake --build build
    $ build/blood

Controls are arrow keys to move around, space to attack and 't' and 'y' to change levels. The second level is basically a secret boss.

<img src="https://raw.githubusercontent.com/osen/software-3d-renderer/master/docs/ss3.png" width="250" />

Please note that the end boss in Monolith's 1997 Blood was not in fact Bongo Cat.

Enjoy!
