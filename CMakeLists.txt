cmake_minimum_required(VERSION 3.5)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyApp main.cpp acl.h)