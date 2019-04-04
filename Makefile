all : asm_parser.c assembler.c
	clang -Wall -g -o asm_parser.h asm_parser.c assembler.c -o assembler