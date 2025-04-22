#!/bin/bash

set -e

echo "[*] Cleaning build directory..."
rm -rf build
mkdir build
cd build

echo "[*] Configuring project with CMake..."
cmake ..

echo "[*] Building..."
make

echo "[✔] Build complete. Running..."
./minecraft2
