#!/bin/bash

### This script build the project and then runs the generated executable

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

if [ "$#" -ne 1 ]; then
    echo "Illegal number of command line arguments. Enter Debug or Release as the first command line argument."
    exit 1
fi

if [ "$1" == "Debug" ] || [ "$1" == "Release" ]; then
    # Run the build script
    bash $DIR/build.sh $1

    # Run the executable
    $BUILD_DIR/isp1

    # Change working directory to the directory containing this bash script.
    cd $DIR

    # Exit this bash script
    exit 0
fi

# Exit with error
echo "The first command line argument was neither Debug nor Release."
exit 1