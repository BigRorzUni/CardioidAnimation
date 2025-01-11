#!/bin/bash

# Set the configuration
if [ "$1" == "debug" ]; then
  CONFIG=debug_rgfw_arm64
else
  CONFIG=${1:-release_rgfw_arm64}
fi

# Build the project
echo "Building project with configuration: $CONFIG"
make config=$CONFIG VERBOSE=1

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Running the project..."
  # Determine the output directory based on the configuration
  if [[ "$CONFIG" == *"debug"* ]]; then
    OUTPUT_DIR="./bin/Debug"
  else
    OUTPUT_DIR="./bin/Release_RGFW"
  fi
  # Check if the executable exists
  if [ -f "$OUTPUT_DIR/CardioidAnimation" ]; then
    # Run the project
    $OUTPUT_DIR/CardioidAnimation
  else
    echo "Error: Executable not found in $OUTPUT_DIR"
    exit 1
  fi
else
  echo "Build failed."
  exit 1
fi