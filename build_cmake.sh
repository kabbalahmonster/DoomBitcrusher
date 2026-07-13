#!/bin/bash
# CMake build script for Doom Bitcrusher (no Projucer needed)

set -e

echo "=== Doom Bitcrusher CMake Build ==="
echo ""

# Create build directory
mkdir -p build/cmake
cd build/cmake

# Configure with CMake
echo "Configuring with CMake..."
cmake ../.. -DCMAKE_BUILD_TYPE=Release

# Build
echo "Building..."
make -j4

echo ""
echo "=== Build Complete ==="
echo "VST3 should be in: build/cmake/DoomBitcrusher_artefacts/Release/"
