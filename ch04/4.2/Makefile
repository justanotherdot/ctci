.PHONY: run
run: build
	./q

all:
	run

build: q.c
	clang -lm -g -Wall -Werror -Wpedantic q.c ../common/tree.o -o q
