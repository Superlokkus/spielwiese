```
git submodule update  --init --recursive
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
ctest
```


```
cd /tmp/
git clone https://github.com/boostorg/boost.git
cd boost/
git submodule update  --init --recursive
./bootstrap.sh --prefix=$HOME
./b2 
./b2 install
``` 
