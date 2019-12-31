cmake_minimum_required(VERSION 3.12.0)
project(clotho)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")

find_package(Git QUIET)
if(GIT_FOUND)
  include(GetGitRevisionDescription)
  get_git_head_revision(GIT_REVISION)
  message(STATUS "GIT revision count ${GIT_REVISION}")
  set(PROJECT_VERSION_TWEAK "${GIT_REVISION}")
  set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${PROJECT_VERSION_TWEAK}")
else()
  set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  )

enable_testing()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
