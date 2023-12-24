cmake_minimum_required(VERSION 3.19)

project(takeaway)
set(CMAKE_CXX_STANDARD 20)



include_directories(${PROJECT_SOURCE_DIR}/src)
# include_directories(${PROJECT_SOURCE_DIR}/include)
# set(PROJ ${PROJECT_SOURCE_DIR}/src/*.cc)
# add_compile_options("-Wall")
# add_compile_options("-O2")

file(GLOB_RECURSE everything ./src/*.cpp)
add_executable(gen_map ${PROJECT_SOURCE_DIR}/exec/gen_map.cpp ${everything})