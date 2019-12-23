cmake_minimum_required(VERSION 3.12.0)
project(vide)

# extend module path for custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# include modules here
#include(CMakeModule)
include(PreventInSourceBuilds)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add subdirectories here
#add_subdirectory(directory)
