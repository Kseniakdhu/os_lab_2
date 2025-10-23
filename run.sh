#!/bin/bash

echo "Building Monte Carlo project..."
mkdir -p build
cd build
cmake ..
make

echo
echo "Running tests..."
echo "=================="

./main -r 100000000 -t 2
echo "---"
./main -r 100000000 -t 4
echo "---"
./main -r 100000000 -t 8