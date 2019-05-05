all: main
main: asm_parser.o assembler.c
	clang -Wall -g asm_parser.o assembler.c -o assembler
asm_parser.o: asm_parser.c
	clang -g -c asm_parser.c
clean:
	rm -rf *.o
clobber: clean
	rm -rf assembler