# TsunamiMaster

The TsunamiMaster is a C++ cross-platform application from numerical modeling of generation and propagation tsunami and
visualize results of modeling.
TsunamiMaster consists of two main part: C++ library (backend) and User Interface (frontend).

TMlib is C++ library consists of classes, functions that are implemented algorithms for numerical modeling of generation
and propagation tsunami.

For building the TsunamiMaster please follow instructions:

1. Install Qt (http://doc.qt.io/qt-5/gettingstarted.html)
    1.1. If you want to use cmake for building the project you should install cmake (https://cmake.org/download/)

2. Clone the repository with source code: `git clone git clone git@bitbucket.org:ArtyomTugaryov/tsunamimaster.git TsunamiMaster`

3. CD to TsunamiMaster folder

4. Initialize and update submodules (git submodule init && git submodule update)

5. If you use QtCreator open TsunamiMaster.pro in Creator. Done

6. If you want to build using cmake (without QtCreator) create build directory: `mkdir build && cd build`

7. Create Makefile: 'cmake ..'

8. Make the project: 'make -j8'

