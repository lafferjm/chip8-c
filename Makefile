main: main.c chip8
	gcc main.c chip8.o -o chip8

chip8: cpu.h chip8.h
	gcc chip8.c -c

.PHONY: clean
clean:
	rm *.o chip8
