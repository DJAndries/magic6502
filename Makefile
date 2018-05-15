all: lib obj bin lib/libmagic6502.so bin/test

bin/test: bin/test_prog.bin bin/libmagic6502.so obj/main.o
	gcc -lm -o bin/test obj/main.o -L./lib -l:libmagic6502.so

bin/test_prog.bin:
	cp test/test_prog.bin bin/test_prog.bin

bin/libmagic6502.so: lib/libmagic6502.so
	cp lib/libmagic6502.so bin/libmagic6502.so

obj/%.o: test/%.c
	gcc -Wall -O -c $< -Iinclude -o $@

obj/%.o: src/%.c
	gcc -Wall -O -fpic -c $< -Iinclude -o $@

lib/libmagic6502.so: obj/magic6502.o obj/addressing.o obj/execute.o \
	obj/instr_helpers.o obj/instructions.o obj/interrupts.o
	gcc -fvisibility=hidden -shared -o ./lib/libmagic6502.so obj/magic6502.o obj/addressing.o obj/execute.o \
		obj/instr_helpers.o obj/instructions.o obj/interrupts.o

lib:
	mkdir lib

obj:
	mkdir obj

bin:
	mkdir bin

clean:
	rm -f obj/* lib/* bin/*
