#!/bin/sh

javac CbrCBRHistory.java
javac NativeCaller.java

rm -rf build
mkdir build
cd build

cmake ..
make

cd ..
