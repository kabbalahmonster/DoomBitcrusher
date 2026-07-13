cmake_minimum_required(VERSION 3.15)
project(DoomBitcrusher VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE
add_subdirectory(JUCE)

# Plugin configuration
juce_add_plugin(DoomBitcrusher
    COMPANY_NAME "Cult of the Shell"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Cult
    PLUGIN_CODE Doom
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "Doom Bitcrusher"
)

# Source files
target_sources(DoomBitcrusher
    PRIVATE
        src/BitcrusherPlugin.cpp
        src/BitcrusherEditor.cpp
)

# Header search paths
target_include_directories(DoomBitcrusher
    PRIVATE
        src
)

# Compile definitions
target_compile_definitions(DoomBitcrusher
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

# Link JUCE modules
target_link_libraries(DoomBitcrusher
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
