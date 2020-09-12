FROM gitpod/workspace-full

USER gitpod

# Install custom tools, runtime, etc. using apt-get
# For example, the command below would install "bastet" - a command line tetris clone:
#
# RUN sudo apt-get -q update && \
#     sudo apt-get install -yq bastet && \
#     sudo rm -rf /var/lib/apt/lists/*
#
# More information: https://www.gitpod.io/docs/config-docker/

#####################################
# Check out the library.
RUN git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
RUN git clone https://github.com/google/googletest.git benchmark/googletest

# install benchmark
RUN mkdir -p benchmark/build
RUN cd benchmark/build && cmake -DCMAKE_BUILD_TYPE=Release ../
RUN cd benchmark/build && make -j8
RUN cd benchmark/build && make install
# install gtest
RUN mkdir -p benchmark/googletest/build
RUN cd benchmark/googletest/build && cmake -DCMAKE_BUILD_TYPE=Release ../
RUN cd benchmark/googletest/build && make -j8
RUN cd benchmark/googletest/build && make install
# clean
RUN rm -rf benchmark
#####################################

