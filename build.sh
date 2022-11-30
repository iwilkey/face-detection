#!/bin/bash
echo "Building latest ECE 426, Digital Image Processing project source..."
[ ! -d ./build/ ] && mkdir build
cd build
cmake ..
make -j 10
./FaceSpace