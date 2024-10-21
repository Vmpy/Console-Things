cmake_minimum_required(VERSION 3.20.0)

project(Minessweep LANGUAGES C)

set(SRC User/main.c)

include_directories(User)

add_executable(Minessweep ${SRC})