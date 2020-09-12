builddir := build

all: format run

format:
	clang-format -i `find src/*\.{cpp,h} -type f`

cmake:
	mkdir -p $(builddir)
	cd $(builddir) && cmake ..

build: cmake
	cd $(builddir) && make

run: build
	cd $(builddir) && ./vector

clean:
	rm -rf $(builddir)