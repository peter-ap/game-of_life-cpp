cmake_minimum_required(VERSION 3.10)

# set the project name
project(GameOfLife)

# Enable pthread library 
set(CMAKE_C_FLAGS -pthread)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include_directories(include)
 
# set(SOURCE_FILES src/main.cpp src/Calibration.cpp)


add_executable(GameOfLife main.cpp)
# add_executable(Calibration ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

target_link_libraries(GameOfLife ${OpenCV_LIBS})
