builddir := build
OBJ := heap_main
SRC := src/heap_main.cpp

all: format run

format:
	clang-format -i `find src/*\.{cpp,h} -type f`

cmake:
	mkdir -p $(builddir)

build: cmake
	cd $(builddir) && g++ -o ./${OBJ} -std=c++11 ../${SRC}

run: build
	cd $(builddir) && ./${OBJ} 19 1050

clean:
	rm -rf $(builddir)