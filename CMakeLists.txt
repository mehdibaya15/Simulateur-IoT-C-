cmake_minimum_required(VERSION 3.10)
project(AP4A_Simple LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_executable(simulator
    src/main.cpp
    src/Sensor.cpp
    src/Server.cpp
    src/Scheduler.cpp
)
