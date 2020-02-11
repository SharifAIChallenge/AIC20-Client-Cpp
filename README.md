# Requirements 

## Build
###Unix-Like (Ubuntu, MacOS)

```
cd /tmp
git clone --depth=1 https://github.com/nlohmann/json
cd json
mkdir build
cd build
cmake ..
make
sudo make install

```
###Windows

# Test
##Valgrind
*Valgrind* has been used to test the memory leak. 
For more information visit: 
[www.valgrind.org](http://valgrind.org)

##Travis


