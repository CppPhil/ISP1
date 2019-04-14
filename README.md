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
