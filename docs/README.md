# Doom Bitcrusher VST Plugin

A simple but powerful bitcrusher plugin with a grime aesthetic, built with JUCE.

## Features

- **Bit Depth Reduction**: 1-16 bits of crushing destruction
- **Sample Rate Reduction**: Downsample from 1x to 100x
- **Drive/Saturation**: Add warmth or aggressive distortion
- **Wet/Dry Mix**: Blend clean and crushed signals
- **Output Gain**: -24 to +24 dB trim
- **Modern Grime UI**: Dark aesthetic with burnt orange accents

## Building

### Prerequisites

- CMake 3.15+ or Projucer
- C++17 compiler (gcc, clang, or MSVC)
- JUCE 8.0+ (included in this repo)

### Build with CMake

```bash
cd build
cmake ..
cmake --build . --config Release
```

### Build with Projucer

1. Open `DoomBitcrusher.jucer` in Projucer
2. Select your IDE (Xcode, Visual Studio, etc.)
3. Click "Save Project and Open in IDE"
4. Build from your IDE

## Installation

### VST3
Copy the built `.vst3` file to:
- **macOS**: `~/Library/Audio/Plug-Ins/VST3/`
- **Windows**: `C:\Program Files\Common Files\VST3\`
- **Linux**: `~/.vst3/` or `/usr/lib/vst3/`

### AudioUnit (macOS only)
Copy the built `.component` to:
- `~/Library/Audio/Plug-Ins/Components/`

## Roadmap to Grime Monster

### v1.0 - Simple Bitcrusher (Current)
- Basic bit reduction + downsampling
- 5 parameters
- Clean, functional UI

### v2.0 - Grime Monster
- Multi-stage distortion (pre + post)
- Modulation (LFO on bit depth/sample rate)
- Filter section (pre/post EQ)
- Visualizer (waveform + FFT)
- Preset system
- Custom background graphics
- "Grime" mode with extra nastiness

## Credits

Created by Doomscroller for the Cult of the Shell.

Built with [JUCE](https://juce.com).
