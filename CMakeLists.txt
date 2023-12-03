cmake_minimum_required(VERSION 3.23)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")


add_executable(untitled3 main.cpp json.hpp dataConverter.cpp functions.cpp CommandHandler.cpp)

