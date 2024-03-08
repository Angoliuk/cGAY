cmake_minimum_required(VERSION 3.22)

project(cGAY)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
./src/main.cpp
./src/renderer.cpp
./src/resources.cpp
./src/window.cpp
)

set(HEADERS
./include/cGAY/indecludes.h
./include/cGAY/renderer.h
./include/cGAY/resources.h
./include/cGAY/window.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set(SDK_ROOT "/home/neutrinozh/libs/ultralight/")
set(ULTRALIGHT_INCLUDE_DIR "${SDK_ROOT}/include")
set(ULTRALIGHT_BINARY_DIR "${SDK_ROOT}/bin")
set(ULTRALIGHT_INSPECTOR_DIR "${SDK_ROOT}/inspector")
set(ULTRALIGHT_RESOURCES_DIR "${SDK_ROOT}/resources")

target_include_directories(${PROJECT_NAME} PRIVATE "${ULTRALIGHT_INCLUDE_DIR}")
target_link_directories(${PROJECT_NAME} PRIVATE "${ULTRALIGHT_BINARY_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE UltralightCore AppCore Ultralight WebCore)

include_directories(./include)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

message("Building with CMake version: ${CMAKE_VERSION}")
