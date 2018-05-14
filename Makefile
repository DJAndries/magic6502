all: lib obj obj/test bin lib/libmagic6502.a bin/test

bin/test: lib/libmagic6502.a obj/test/main.o
	gcc -lm -o bin/test obj/test/main.o -L./lib -lmagic6502

obj/test/%.o: test/%.c
	gcc -Wall -O -c $< -Iinclude -o $@

obj/%.o: src/%.c
	gcc -Wall -O -c $< -Iinclude -o $@

lib/libmagic6502.a: obj/magic6502.o obj/addressing.o obj/execute.o \
	obj/instr_helpers.o obj/instructions.o obj/interrupts.o
	ar rcs ./lib/libmagic6502.a obj/magic6502.o obj/addressing.o obj/execute.o \
		obj/instr_helpers.o obj/instructions.o obj/interrupts.o

lib:
	mkdir lib

obj:
	mkdir obj

obj/test: obj
	mkdir obj/test

bin:
	mkdir bin

clean:
	rm -f obj/* lib/* bin/*
