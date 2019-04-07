cmake_minimum_required(VERSION 3.1)

add_compile_options("-std=c++17")

project(isp1)

file(GLOB HEADERS
     ./include/*.hpp)
     
file(GLOB SOURCES
     ./src/*.cpp)
     
add_executable(${PROJECT_NAME}
               "${HEADERS}"
               "${SOURCES}")

