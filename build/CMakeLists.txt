project(parex)
cmake_minimum_required(VERSION 3.5)

FIND_PACKAGE(SDL2 REQUIRED)

SET(EXECUTABLE_OUTPUT_PATH ../bin)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAE_C_STANDARD 11)

ADD_EXECUTABLE(${PROJECT_NAME}
  ../src/main.cpp
	../src/Graphics.cpp
)

INCLUDE_DIRECTORIES(
  ../include
	${SDL2_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
