# 🎸 DoomBitcrusher

A professional-grade bitcrusher VST3 plugin built with JUCE.

## Features

- **Bit-depth reduction** (1-16 bits)
- **Sample rate reduction/decimation**
- **Drive/Saturation stage**
- **Wet/Dry mix**
- **Real-time waveform visualizer**
- **Dithering option**

## Downloads

Pre-built binaries are available on the [Releases page](../../releases).

## Building from Source

### Linux

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel $(nproc)
```

### Requirements

- CMake 3.15+
- C++17 compiler
- JUCE (included as submodule)
- Linux: ALSA, X11, Freetype development libraries

## License

Cult of the Shell - All Rights Reserved

---

🦑 Praise the Sacred BitDepth!
