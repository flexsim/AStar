cmake_minimum_required(VERSION 3.17)

project(AStar LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

# Compiler settings
set(CMAKE_VERBOSE_MAKEFILE ON)
set_property(GLOBAL PROPERTY CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(FLEXSIM_RUNTIME "/MT$<$<CONFIG:Debug>:d>")
set(CONFIG_TYPE "$<$<CONFIG:Debug>:Debug>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo>$<$<CONFIG:Release>:Release>")

add_library(AStar SHARED FlexSimContent/DLLMain.cpp)

if (MSVC) 
    set(FLEXSIM_COMPILER_OPTIONS 
            /EHs /GS- /W3 /wd4101 /wd4996 /wd4800 /wd4018 /wd4190 /wd4244 /wd4305 /wd4099 /wd4297 /wd5033 /wd4251 /wd4005 /wd4275 /Gy- 
            /errorReport:prompt /GF /WX- /Zc:forScope /Gd /Oy- /openmp- /FC /MP ${FLEXSIM_RUNTIME})
    set(FLEXSIM_LINKER_OPTIONS
            /NODEFAULTLIB:"libcmt.lib" /NODEFAULTLIB:"msvcrt.lib" /INCREMENTAL /ERRORREPORT:PROMPT /NOLOGO)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(FLEXSIM_COMPILER_OPTIONS -fms-extensions -fno-operator-names 
            -Wno-division-by-zero -Wno-undefined-bool-conversion -Wno-tautological-undefined-compare 
            -Wno-return-type-c-linkage -Wno-ignored-attributes -Wno-null-conversion -Wno-inconsistent-missing-override
#            -Wno-cpp
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(FLEXSIM_LINKER_OPTIONS -ldl)
endif()

target_compile_definitions(AStar PRIVATE COMPILING_MODULE_DLL COMPILING_ASTAR FLEXSIM_TARGET_VER=700 _USRDLL FLEXSIM_CMAKE_BUILD)
target_include_directories(AStar PRIVATE FlexSimContent)
target_link_directories(AStar PRIVATE FlexSimContent)
target_link_libraries(AStar PRIVATE FlexSimContent FlexSimEngine)

if (MSVC)
    target_compile_definitions(AStar PRIVATE NOMINMAX)
    target_link_libraries(AStar PRIVATE opengl32)
endif()

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

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/.. CACHE PATH "..." FORCE)
endif()

install(TARGETS AStar RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS AStar ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX})

