# cmake file
cmake_minimum_required(VERSION 3.10)

# set the project name
project(CppExample LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)