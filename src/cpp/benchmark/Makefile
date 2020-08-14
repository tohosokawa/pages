builddir := build

all: format run

format:
	clang-format -i `find src/*\.{cpp,h} -type f`

build:
	mkdir -p $(builddir)
	cd $(builddir) && cmake ..
	cd $(builddir) && make

run: build
	cd $(builddir) && ./container

clean:
	rm -rf $(builddir)