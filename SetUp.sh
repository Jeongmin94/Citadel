#!/bin/bash

echo "build project..."

if [ $1 == "UnitTest" ]; then
  PROJECT_DIR="UnitTest"
else
  PROJECT_DIR="Citadel"
fi

if [ -d "build" ]; then
  echo "build directory is already exist"
else
  echo "create build directory"
  mkdir build
fi

cd build
cmake ..
make

cd ./bin
echo "----execute ${PROJECT_DIR}----"
./${PROJECT_DIR}