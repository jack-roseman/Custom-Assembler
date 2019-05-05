/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : tjf & jack roseman                                        *
 * description : This program will parse a .ASM file                       *
 *                  						                               * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int read_asm_file(char* filename, char program[ROWS][COLS]) {
	char line[COLS];
	int i = 0;
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return 2;
	}
	while (fgets(line, COLS, file) != NULL) {
		if (line[0] == '\n') {
			i++;
			continue;
		}
		memcpy(program[i], line, strlen(line)); 
		i++;
	}
	
	return 0;
}
int parse_instruction(char* instr, char* instr_bin_str) {
	char* token;
	char instruction[strlen(instr)];
    const char space_delim[2] = " ";
	memcpy(instruction, instr, strlen(instr));
	token = strtok(instruction, space_delim);
	if (strncmp(token, "ADD", 4) == 0) {
		if (parse_add(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if (strncmp(token, "SUB", 4) == 0) {
		if (parse_sub(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if (strncmp(token, "MUL", 4) == 0) {
		if (parse_mul(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if (strncmp(token, "DIV", 4) == 0) {
		if (parse_div(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if (strncmp(token, "AND", 4) == 0) {
		if (parse_and(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if (strncmp(token, "OR", 3) == 0) {
		if (parse_or(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} else if(strncmp(token, "XOR", 4) == 0) {
		if (parse_xor(instr, instr_bin_str) == 4) {
			printf("error3: parse_instruction() failed.\n");
			return 3;
		}
	} 
	return 0;
}

int parse_reg(char reg_num, char* instr_bin_str) {
	int i;
	i = strlen(instr_bin_str);        //where the number in instr_bin_str will be put
	switch (reg_num) {
		case '0':
			instr_bin_str[i]   = '0';
			instr_bin_str[i+1] = '0';
			instr_bin_str[i+2] = '0';
			break;
		case '1':
			instr_bin_str[i]   = '0';
			instr_bin_str[i+1] = '0';
			instr_bin_str[i+2] = '1';
			break;
		case '2':
			instr_bin_str[i]   = '0';
			instr_bin_str[i+1] = '1';
			instr_bin_str[i+2] = '0';
			break;
		case '3':
			instr_bin_str[i]   = '0';
			instr_bin_str[i+1] = '1';
			instr_bin_str[i+2] = '1';
			break;
		case '4':
			instr_bin_str[i]   = '1';
			instr_bin_str[i+1] = '0';
			instr_bin_str[i+2] = '0';
			break;
		case '5':
			instr_bin_str[i]   = '1';
			instr_bin_str[i+1] = '0';
			instr_bin_str[i+2] = '1';
			break;
		case '6':
			instr_bin_str[i]   = '1';
			instr_bin_str[i+1] = '1';
			instr_bin_str[i+2] = '0';
			break;
		case '7':
			instr_bin_str[i]   = '1';
			instr_bin_str[i+1] = '1';
			instr_bin_str[i+2] = '1';
            break;
		default:
			printf("error5: parse_reg() failed.\n");
			return 5;
	}
	return 0;
}

int parse_add(char* instr, char* instr_bin_str ){
	char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");                  //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0001", 5); //opcode
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_add() failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_add() failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"000");  //sub-opcode
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_add() failed.\n");
		return 4;
	}
	return 0;
}

int parse_sub(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0001", 5);  //opcode
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_sub() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_sub() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"010"); //sub-opcode
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_sub() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

int parse_mul(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0001", 5); //opcode
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_mul() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_mul() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)), "001"); //sub-opcode
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_mul() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

int parse_div(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0001", 5); //opcode
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_div() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_div() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"011"); //sub-opcode
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_div() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

int parse_and(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0101", 5);
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_and() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_and() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"000");
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_and() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

int parse_or(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0101", 5); //opcode
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_or() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_or() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"010"); //sub-opcode
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_or() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

int parse_xor(char* instr, char* instr_bin_str ) {
    char registers[3];
	char* token; 
    char r;
	int i = 0;
	token = strtok(instr, " ");          //skip command
    instr = instr + strlen(token) + 1;           //go to next token
    token = strtok(NULL, ", ");
	while (token != NULL) {
        sscanf(token, "R%c", &r);
		registers[i] = '\0' + r;
		if (i == 2) {
			token = strtok(NULL, "");
		} else{
			token = strtok(NULL, ", ");
		}
		i++;
	}
    memcpy(instr_bin_str, "0101", 5);
	if (parse_reg(registers[0], instr_bin_str) == 5) {
		printf("error4: parse_xor() failed because parse_reg failed.\n");
		return 4;
	}
	if (parse_reg(registers[1], instr_bin_str) == 5) {
		printf("error4: parse_xor() failed because parse_reg failed.\n");
		return 4;
	}
	strcpy(instr_bin_str + (sizeof(char) * strlen(instr_bin_str)),"011");
	if (parse_reg(registers[2], instr_bin_str) == 5) {
		printf("error4: parse_xor() failed because parse_reg failed.\n");
		return 4;
	}
	return 0;
}

unsigned short int str_to_bin (char* instr_bin_str) {
    int i;
    int bin_num = 0;
    for(i = 0; i < strlen(instr_bin_str); i++) {
        if (instr_bin_str[i] == '1') {
            bin_num = bin_num + power(2, 15 - i);
        }
    }
	return bin_num;
}

int power(int base, int exponent){
    int s = 1;
    while(exponent != 0) {
        s = s*base;
        exponent--;
    }
	return s;
}

int write_obj_file(char* filename, unsigned short int program_bin[ROWS]) {
    FILE* file;
    int i;
    unsigned short int prog_len = 0;
    unsigned short int n = 0;
    unsigned short int header[1];
    unsigned short int addr[1];
    //change file extension to ".obj"
    filename[strlen(filename) - 3] = 'o';
    filename[strlen(filename) - 2] = 'b';
    filename[strlen(filename) - 1] = 'j';
    filename[strlen(filename)] = '\0';
    file = fopen(filename, "wb");
    if (file == NULL) {
        return 7;
    }
    *header = 0xDECA;
    *addr = 0x0000;
    if (fwrite(header, sizeof(unsigned short int), 1, file) != 1) {
        return 7;
    }
    if (fwrite(addr, sizeof(unsigned short int), 1, file) != 1) {
        return 7;
    }
    while (program_bin[prog_len] != 0) {
        prog_len++;
    }
    //fix endianness
    n = (((prog_len >> 8) & 0x00ff) | ((prog_len << 8) & 0xff00));
    for(i = 0; i < prog_len; i++){
        program_bin[i] = (((program_bin[i] >> 8) & 0x00ff) | ((program_bin[i] << 8) & 0xff00));
    }
    if (fwrite(&n, sizeof(unsigned short int), 1, file) != 1) {
        return 7;
    }
    if (fwrite(program_bin, sizeof(unsigned short int), prog_len, file) != prog_len) {
        return 7;
    }
    fclose(file);
	return 0;
}