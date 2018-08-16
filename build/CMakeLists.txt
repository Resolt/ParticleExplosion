project(parex)
cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE_OUTPUT_PATH ../bin)

set (CMAKE_CXX_STANDARD 11)
set (CMAE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
  ../src/main.cpp
)

include_directories(
  ../include
)
