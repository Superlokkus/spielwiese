Spielwiese
==============

Bare modern C++ project template

Build & Test
--------
```
git submodule update --init --recursive
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
ctest -C Release
```

Boost
----------
```
cd /tmp/
git clone https://github.com/boostorg/boost.git
cd boost/
git submodule update  --init --recursive
./bootstrap.sh --prefix=$HOME
./b2 
./b2 install
``` 

CMake Tricks
-----------------------

You may have explicitly specify the build system generator, e.g.
```
-G"Visual Studio 15 2017 Win64"
```
Or just choose the command set since VS 2019:
```
-A"Win32" 
```
or adjust the cmake search path to find the dependencies, e.g.
```
-DCMAKE_PREFIX_PATH="C:\Boost" -DCMAKE_PREFIX_PATH="C:\Qt\5.12.2\msvc2017_64"
```
