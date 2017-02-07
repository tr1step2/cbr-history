#!/bin/sh

javac CBRHistory.java
javac NativeCaller.java

if [ ! -d "build" ]; then
  mkdir build
fi

cd build

cmake ..
make

cd ..