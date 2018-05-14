all: lib obj lib/magic6502.a

obj/%.o: src/%.c
	gcc -O -c $< -Iinclude -o $@

lib/magic6502.a: obj/magic6502.o obj/addressing.o obj/execute.o \
	obj/instr_helpers.o obj/instructions.o obj/interrupts.o
	ar rcs ./lib/magic6502.a obj/magic6502.o obj/addressing.o obj/execute.o \
		obj/instr_helpers.o obj/instructions.o obj/interrupts.o

lib:
	mkdir lib

obj:
	mkdir obj
