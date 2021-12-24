cmake_minimum_required(VERSION 3.10)

# set the project name
project(renderboy)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# add the executable
add_executable(renderboy renderboy.cpp utils.cpp surfaces.cpp)

#add GLM headers
target_include_directories(renderboy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glm/)
