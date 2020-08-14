#!/bin/bash

sudo apt-get -y install clang-format

if [ ! -d "library/benchmark" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  cd library && ./install.sh
  cd -
fi

cd library/benchmark/build && sudo make install
cd -
