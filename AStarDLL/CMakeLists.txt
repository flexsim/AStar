cmake_minimum_required(VERSION 3.17)

project(AStar LANGUAGES C CXX)

# Compiler settings
set(CMAKE_VERBOSE_MAKEFILE ON)
set_property(GLOBAL PROPERTY CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(FLEXSIM_RUNTIME "/MT$<$<CONFIG:Debug>:d>")
set(CONFIG_TYPE "$<$<CONFIG:Debug>:Debug>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo>$<$<CONFIG:Release>:Release>")

add_library(AStar SHARED FlexsimContent/dllmain.cpp)

if (MSVC) 
    set(FLEXSIM_COMPILER_OPTIONS 
            /EHs /GS- /W3 /wd4101 /wd4996 /wd4800 /wd4018 /wd4190 /wd4244 /wd4305 /wd4099 /wd4297 /wd5033 /Gy- 
            /errorReport:prompt /GF /WX- /Zc:forScope /Gd /Oy- /openmp- /std:c++latest /FC /MP ${FLEXSIM_RUNTIME})
    set(FLEXSIM_LINKER_OPTIONS
            /NODEFAULTLIB:"libcmt.lib" /NODEFAULTLIB:"msvcrt.lib" /INCREMENTAL /ERRORREPORT:PROMPT /NOLOGO)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(FLEXSIM_COMPILER_OPTIONS -fms-extensions -fno-operator-names 
            -Wno-division-by-zero -Wno-undefined-bool-conversion -Wno-tautological-undefined-compare 
            -Wno-return-type-c-linkage -Wno-ignored-attributes -Wno-null-conversion
#            -Wno-cpp
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(FLEXSIM_LINKER_OPTIONS -ldl)
endif()

if (MSVC)
    target_compile_definitions(AStar PRIVATE NOMINMAX)
endif()

target_compile_definitions(AStar PRIVATE COMPILING_MODULE_DLL COMPILING_ASTAR FLEXSIM_TARGET_VER=700 _USRDLL FLEXSIM_CMAKE_BUILD)
target_include_directories(AStar PRIVATE source FlexsimContent)

# Utilities sources
target_sources(AStar PRIVATE 
    AStar.cpp
    AStarNavigator.cpp
    AStarTypes.cpp
    Barrier.cpp
    Bridge.cpp
    BridgeRoutingData.cpp
    Divider.cpp
    ElevatorBridge.cpp
    ElevatorBridgeRoutingData.cpp
    Grid.cpp
    MandatoryPath.cpp
    Point.cpp
    PreferredPath.cpp
    TemporaryBarrier.cpp
    Traveler.cpp)

target_compile_options(AStar PRIVATE ${FLEXSIM_COMPILER_OPTIONS})
target_link_options(AStar PRIVATE ${FLEXSIM_LINKER_OPTIONS})

if (MSVC)
else()
    add_custom_command(TARGET AStar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/libAStar.so ${CMAKE_CURRENT_SOURCE_DIR}/bin/libAStar.so
    )
endif()