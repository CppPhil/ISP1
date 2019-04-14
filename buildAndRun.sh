#!/bin/bash

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Build directory
readonly BUILD_DIR=$DIR/build

# Run the build script
bash $DIR/build.sh

# Run the executable
$BUILD_DIR/isp1

# Change working directory to the directory containing this bash script.
cd $DIR

# Exit this bash script
exit 0

