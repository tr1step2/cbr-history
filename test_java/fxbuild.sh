#!/bin/sh

javac CurrencyData.java
javac CurrencyDataContainer.java
javac CBRHistory.java
javac NativeCaller.java

if [ ! -d "build" ]; then
  mkdir build
fi

cd build

cmake ..
make

cd ..