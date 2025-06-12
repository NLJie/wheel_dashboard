rm build -rf
mkdir build && cd build && cmake ..
make -j10
make install