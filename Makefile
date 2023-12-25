main: main.c
	gcc main.c -o chip8

.PHONY: clean
clean:
	rm *.o chip8
