#!/bin/bash
# Build script for Doom Bitcrusher on Fedora 34

set -e

echo "=== Doom Bitcrusher Build Script ==="
echo ""

# Check if we're in the right directory
if [ ! -f "DoomBitcrusher.jucer" ]; then
    echo "Error: Run this script from the vst-dev directory"
    echo "Usage: cd vst-dev && ./build_fedora.sh"
    exit 1
fi

# Find Projucer
if [ -f "JUCE/Projucer" ]; then
    PROJUCER="./JUCE/Projucer"
elif [ -f "/usr/bin/Projucer" ]; then
    PROJUCER="/usr/bin/Projucer"
else
    echo "Error: Projucer not found"
    exit 1
fi

echo "Step 1: Regenerating Makefile for local paths..."
$PROJUCER --resave DoomBitcrusher.jucer --fix-missing-dependencies

echo ""
echo "Step 2: Building with VST2 conflict workaround..."
cd build/linux

# Build with the VST2/VST3 conflict fix
make JUCE_CPPFLAGS="-DJUCE_VST3_CAN_REPLACE_VST2=0" -j4

echo ""
echo "=== Build Complete ==="
echo "VST3 Location: build/linux/build/DoomBitcrusher.vst3"
echo ""
echo "To install:"
echo "  cp -r build/linux/build/DoomBitcrusher.vst3 ~/.vst3/"
