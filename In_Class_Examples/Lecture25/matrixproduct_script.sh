#!/bin/bash

gcc -fopenmp -o matrixproduct_shared matrixproduct_shared.c

echo "Non-optimized code, one thread..."
export OMP_NUM_THREADS="1"
./matrixproduct_shared
echo ""
echo "Non-optimized code, two threads..."
export OMP_NUM_THREADS="2"
./matrixproduct_shared
echo ""
echo "Non-optimized code, four threads..."
export OMP_NUM_THREADS="4"
./matrixproduct_shared
echo ""
echo "Non-optimized code, eight threads..."
export OMP_NUM_THREADS="8"
./matrixproduct_shared

echo ""

gcc -fopenmp -o matrixproduct_optimized_shared matrixproduct_optimized_shared.c

echo "Optimized code, one thread..."
export OMP_NUM_THREADS="1"
./matrixproduct_optimized_shared
echo ""
echo "Optimized code, two threads..."
export OMP_NUM_THREADS="2"
./matrixproduct_optimized_shared
echo ""
echo "Optimized code, four threads..."
export OMP_NUM_THREADS="4"
./matrixproduct_optimized_shared
echo ""
echo "Optimized code, eight threads..."
export OMP_NUM_THREADS="8"
./matrixproduct_optimized_shared
