# ISP1
## General description
This repository serves as an implementation of the A* algorithm.  

## Warning
Currently only GNU/Linux operating systems are supported!  

## Prerequisites
* git
* CMake
* g++-7
* doxygen
* clang-format

To install the prerequisites run:  
`sudo apt-get install git cmake gcc-7 doxygen clang-format -y`  

## Cloning the repository
Use  
`git clone https://github.com/CppPhil/ISP1.git --recursive`  
to clone the repository.  
The `--recursive` flag is important!  


## Building
To build run  
`bash ./build.sh`  
from the project's root directory.  
The `isp1` executable will be placed in the `build` subdirectory.  

## Dependencies
The projects dependencies are managed throug git submodules.  
Their files are placed in the `deps` subdirectory.  

### "clang-format" dependency
Contains clang-format stuff, nothing to worry about.  

### "Graph" dependency
Repository: `https://github.com/Terae/Graph/`  
Documentation: `https://terae.github.io/graph/`  
The documentation is subpar, you will have to consult the source files yourself if the documentation proves insufficient / incomplete.  

### "nlohmann_json" dependency
The Graph library depends on this JSON library...  
Repository: `https://github.com/nlohmann/json`  
Documentation: `https://nlohmann.github.io/json/`  

### "philslib" dependency
Repository: `https://github.com/CppPhil/philslib/`  
Documentation: Run `doxygen ./deps/philslib/Doxyfile` from the project's root directory to generate the HTML documentation for this library.  

## Overview
`build`: Automatically generated directory containing the build artifacts generated, including the executable.  
`buildAndRun.sh`: Shell script to build and then run the application.  
`build.sh`: Shell script to build the application.  
`CMakeLists.txt`: Configuration file of the CMake build system generator.  
`deps`: Directory containing the git submodule dependencies.  
`format.sh`: Shell script to format the source code of the project.  
`.git`: Directory of the git software configuration management software.  
`.gitignore`: File containing information as to which sort of files shall be ignored by git.  
`.gitmodules`: git submodule configuration file.  
`include`:Directory containing the header files of the project.  
`IS-02-2 Informierte Suche.pdf`: PDF file regarding informed search algorithms.  
`README.md`: This file.
`src`: Directory containing the source (*.cpp) files of the project.  
`TODO_LIST.txt`: This project's todo-list.  
`UNLICENSE.md`: The license of this project.  
