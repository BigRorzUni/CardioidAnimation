#!/bin/bash

# Set the configuration
if [ "$1" == "debug" ]; then
  CONFIG=debug_x64
else
  CONFIG=${1:-release_rgfw_arm64}
fi
# Build the project
echo "Building project with configuration: $CONFIG"
make config=$CONFIG

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Running the project..."
  # Determine the output directory based on the configuration
  if [[ "$CONFIG" == *"debug"* ]]; then
    OUTPUT_DIR="./bin/Debug"
  else
    OUTPUT_DIR="./bin/Release_RGFW"
  fi
  # Run the project
  $OUTPUT_DIR/CardioidAnimation
else
  echo "Build failed."
fi