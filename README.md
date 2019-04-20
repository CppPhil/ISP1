# ISP1
## General description
This repository serves as an implementation of the A* algorithm.  

## Warning
Currently only GNU/Linux operating systems are supported!  

## Prerequisites
* Git
* CMake
* g++-7
* doxygen
* clang-format
* graphviz

To install the prerequisites run:  
`sudo apt-get install git cmake gcc-7 doxygen clang-format graphviz -y`  

## Cloning the repository
Use  
`git clone https://github.com/CppPhil/ISP1.git --recursive`  
to clone the repository.  
The `--recursive` flag is important!  
This will take a few minutes!  

## Building
To build run  
`bash ./build.sh`  
from the project's root directory.  
The `isp1` executable will be placed in the `build` subdirectory.  
Alternatively you can build and run the application at once using  
`bash ./buildAndRun.sh`  
from the project's root directory.  

## Running
The application can be run after it has been built using  
`./build/isp1`  
from the project's root directory.  

## Formatting
To format the source code use  
`bash ./format.sh`  
from the project's root directory.  

## Dependencies
The project's dependencies are managed through git submodules.  
Their files are placed in the `deps` subdirectory.  

### "clang-format" dependency
Contains clang-format stuff, nothing to worry about.  

### "Graph" dependency
Repository: <https://github.com/Terae/Graph/>  
Documentation: <https://terae.github.io/graph/>  
The documentation is subpar, you will have to consult the source files yourself if the documentation proves insufficient / incomplete.  

### "nlohmann_json" dependency
The Graph library depends on this JSON library...  
Repository: <https://github.com/nlohmann/json>  
Documentation: <https://nlohmann.github.io/json/>  

### "philslib" dependency
Repository: <https://github.com/CppPhil/philslib/>  
Documentation: Run `doxygen ./deps/philslib/Doxyfile` from the project's root directory to generate the HTML documentation for this library.  
The documentation can then be viewed using something like `firefox ./doc/html/index.html`  

## Generating the documentation
To generate the documentation run  
`doxygen ./Doxyfile `  
in the project's root directory.  
The `docs` subdirectory will then contain the HTML documentation.  
Using something like `firefox ./docs/html/index.html ` the documentation can be viewed.  

## Overview of the files / directories
`build`: Automatically generated directory containing the build artifacts generated, including the executable.  
`buildAndRun.sh`: Shell script to build and then run the application.  
`build.sh`: Shell script to build the application.  
`CMakeLists.txt`: Configuration file of the CMake build system generator.  
`data`: Directory containing data for the project.  
`deps`: Directory containing the git submodule dependencies.  
`docs`: Directory containing the doxygen generated documentation.  
`format.sh`: Shell script to format the source code of the project.  
`.git`: Directory of the git software configuration management software.  
`.gitignore`: File containing information as to which sort of files shall be ignored by git.  
`.gitmodules`: Git submodule configuration file.  
`include`: Directory containing the header files of the project.  
`IS-02-2 Informierte Suche.pdf`: PDF file regarding informed search algorithms.  
`README.md`: This file.
`src`: Directory containing the source (*.cpp) files of the project.  
`TODO_LIST.txt`: This project's todo-list.  
`UNLICENSE.md`: The license of this project.  

## C++
<https://en.cppreference.com/w/cpp/header> C++ standard library documentation by header files.  
<https://isocpp.org/faq> C++ FAQ  
<https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Die_STL/_Iteratoren> C++ iterators  
<https://isocpp.org/wiki/faq/const-correctness> Const Correctness  
<https://en.cppreference.com/w/cpp/language/ub> Undefined behavior  
<https://en.cppreference.com/w/cpp/preprocessor> C++ preprocessor  
<https://en.cppreference.com/w/cpp/language/templates> C++ templates  
<https://en.cppreference.com/w/cpp/language/cv> C++ type qualifiers (const and volatile)  
<https://en.cppreference.com/w/cpp/container/vector> vector documentation  
<https://en.cppreference.com/w/cpp/types/integer> Fixed width integer types  
<https://en.cppreference.com/w/cpp/utility/pair> pair documentation  
<https://en.cppreference.com/w/cpp/language/typedef> typedef specifier  
<https://en.cppreference.com/w/cpp/language/type_alias> Type alias, alias template  
<https://en.cppreference.com/w/cpp/language/operators> operator overloading  
<https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019> operator<<  
<https://en.cppreference.com/w/cpp/header/algorithm> STL algorithms  
<https://en.cppreference.com/w/cpp/language/lambda> Lambda expressions  
<https://en.cppreference.com/w/cpp/header/string> string header  
<https://isocpp.org/wiki/faq/exceptions> C++ exceptions  
<https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_N%C3%BCtzliches/_Casts> C++ casts  

<https://en.cppreference.com/w/cpp/language/history> History of C++  
<http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines> C++ Core Guidelines  
<http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4713.pdf> C++17 standard working draft  
<https://wandbox.org/> online compiler  
<https://gcc.godbolt.org/> Compiler Explorer - Interactive Online Disassembler  
<http://quick-bench.com/> Online C++ Microbenchmarking  

## Git
<https://gist.github.com/hofmannsven/6814451> Git Cheatsheet  

## CMake
<https://cmake.org/> home page  
<https://cmake.org/documentation/> documentation  

## Bash scripting
<https://devhints.io/bash> Bash scripting cheatsheet  

## Markdown
<https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf> Markdown cheatsheet  

### Recommended markdown editor
To edit this file I use `Remarkable` which can be obtained from <https://remarkableapp.github.io/index.html>  
GitHub uses its own variant of markdown, called `GitHub Flavored Markdown`, see: <https://github.github.com/gfm/>  
Therefore it is imperative to double check if GitHub renders the markdown within this file as you'd expect it.  
