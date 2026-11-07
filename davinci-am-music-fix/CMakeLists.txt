cmake_minimum_required(VERSION 3.22)
project(AMMusicFix VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
if(DEFINED JUCE_DIR)
    add_subdirectory(${JUCE_DIR} juce)
else()
    FetchContent_Declare(juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.4
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(juce)
endif()

if(APPLE)
    set(AMF_FORMATS VST3 AU)
else()
    set(AMF_FORMATS VST3)
endif()

juce_add_plugin(AMMusicFix
    COMPANY_NAME "Akashi"
    BUNDLE_ID "com.akashi.ammusicfix"
    PLUGIN_MANUFACTURER_CODE Akas
    PLUGIN_CODE AmFx
    FORMATS ${AMF_FORMATS}
    PRODUCT_NAME "AM Music Fix"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    VST3_CATEGORIES Fx EQ
    AU_MAIN_TYPE kAudioUnitType_Effect
    COPY_PLUGIN_AFTER_BUILD FALSE)

target_sources(AMMusicFix PRIVATE
    Source/PluginProcessor.cpp)

target_compile_definitions(AMMusicFix PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0)

target_link_libraries(AMMusicFix
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
