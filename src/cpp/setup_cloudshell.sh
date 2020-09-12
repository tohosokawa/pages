#!/bin/bash

sudo apt-get -y install clang-format

cd library
if [ ! -d "benchmark" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  ./install.sh
fi
cd -

cd library/benchmark/build && sudo make install
cd -
cd library/benchmark/googletest/build && sudo make install
cd -