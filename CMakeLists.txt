cmake_minimum_required(VERSION 3.18)

project(LAB3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SHARED shared.cpp)

add_executable(server server.cpp ${SHARED})
add_executable(client client.cpp ${SHARED})
