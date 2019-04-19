#!/bin/bash

### This script builds the project

# The C compiler to use
readonly C_COMPILER="gcc-7"

# The C++ compiler to use
readonly CXX_COMPILER="g++-7"

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

if [ "$#" -ne 1 ]; then
    echo "Illegal number of command line arguments. Enter Debug or Release as the first command line argument."
    exit 1
fi

if [ "$1" == "Debug" ] || [ "$1" == "Release" ]; then
    # Delete build directory
    rm -rf $BUILD_DIR

    # Create build directory
    mkdir $BUILD_DIR

    # Change working directory to the build directory
    cd $BUILD_DIR

    # Generate native build scripts
    CC=$C_COMPILER CXX=$CXX_COMPILER cmake -DCMAKE_BUILD_TYPE=$1 -G "Unix Makefiles" $DIR

    # Build
    cmake --build $BUILD_DIR -- -j2 VERBOSE=1

    # Change working directory to the directory containing this bash script.
    cd $DIR

    # Exit this bash script
    exit 0
fi

# Exit with error
echo "The first command line argument was neither Debug nor Release."
exit 1
