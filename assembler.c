/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : tjf & you                                                 *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {
    
	char* filename = NULL ;					// name of ASM file
	char  program [ROWS][COLS]; 			// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)
    int i;
    
    if (argc != 2) {
      printf("error1: usage: ./assembler <assembly_file.asm>\n");
      return 0;
    }
    
    //clean up memory
    for (i = 0; i < ROWS; i++) {
        memset(program[i], '\0', COLS);
        memset(program_bin_str[i], '\0', 17);
    }
    memset(program_bin, '\0', ROWS);
	
    filename = argv[1];
    if (read_asm_file(filename, program) == 2) {
        printf("error2: read_asm_file() failed.\n");
        return 0;
    }
    
    //reaching here means we can parse instructions out of program
    
    for (int i = 0; i < ROWS; i++) {
        if (program[i][0] == '\0') {
			continue;
		}
		parse_instruction(program[i], program_bin_str[i]);
		program_bin[i] = str_to_bin(program_bin_str[i]);
//  		printf("%s\n", program_bin_str[i]);
//         printf("0x%X\n", program_bin[i]);
//         printf("\n");
    }

	if (write_obj_file(filename, program_bin) == 7) {
        printf("error7: write_obj_file() failed.\n");
    }
    return 0;
}
