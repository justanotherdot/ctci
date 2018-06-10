.PHONY: run
run: build
	./q

all:
	run

build: q.c tree
	clang -lm -g -Wall -Werror -Wpedantic q.c ../common/tree.o -o q

tree:
	cd ../common && make && cd -
