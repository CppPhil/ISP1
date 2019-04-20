### GLOBAL SETTINGS
# CMake version
cmake_minimum_required(VERSION 3.7)

# C++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_STANDARD 17)
endif()

# Warning flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2 --Wundef")    
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wnull-dereference")
    endif()
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches -Wrestrict")
    endif()    
endif()

# disable undesirable g++ warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-noexcept-type -Wno-unused-function")
endif()

# Optimization flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -march=native -funroll-loops -flto")
endif()

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNDEBUG)
endif()

### PROJECT
# project name
project(isp1)

# Find platform specific multithreading support
find_package(Threads REQUIRED)

file(GLOB HEADERS
     ./include/*.hpp)
     
file(GLOB SOURCES
     ./src/*.cpp)
     
add_executable(${PROJECT_NAME}
               "${HEADERS}"
               "${SOURCES}")

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Include path for the include subdirectory
include_directories(${CMAKE_BINARY_DIR}/../include)

# Include path for philslib
include_directories(${CMAKE_BINARY_DIR}/../deps/philslib/include)

# Include path for nlohmann json
include_directories(${CMAKE_BINARY_DIR}/../deps/nlohmann_json/single_include)

# Include path for Graph library
include_directories(${CMAKE_BINARY_DIR}/../deps/Graph/single_include)

# Avoid windows problems
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
endif()
