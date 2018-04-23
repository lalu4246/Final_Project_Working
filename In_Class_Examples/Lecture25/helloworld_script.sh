#!/bin/bash

gcc -fopenmp -o helloworld_shared helloworld_shared.c

echo "Hello world code, one thread..."
export OMP_NUM_THREADS="1"
./helloworld_shared
echo ""
echo "Hello world code, two threads..."
export OMP_NUM_THREADS="2"
./helloworld_shared
echo ""
echo "Hello world code, four threads..."
export OMP_NUM_THREADS="4"
./helloworld_shared
echo ""
echo "Hello world code, eight threads..."
export OMP_NUM_THREADS="8"
./helloworld_shared
