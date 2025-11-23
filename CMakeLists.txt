# Title
cmake_minimum_required(VERSION 3.10.0)
project(mspvz VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ Standard To 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output Error Message, Such as Undefined Reference
add_compile_options(/W4)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# Set Exeutable Name
set(TARGET ${PROJECT_NAME}_${CMAKE_SYSTEM_NAME})


# Find SDL2, SDL2_image, SDL2_mixer, SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add New Include Path
add_executable(${TARGET} 
                        "src/main.cpp"
                        "src/hander/GameManager.h"
                        "src/hander/LogOutput.h"
                        "src/hander/SingletonInstanceTemplate.h"
                        "src/hander/ResourcesManager.h"
                        )


# Find libs
target_link_libraries(${TARGET} 
                        SDL2::SDL2
                        SDL2_image::SDL2_image
                        SDL2_mixer::SDL2_mixer
                        SDL2_ttf::SDL2_ttf
                        SDL2::SDL2main
                        )