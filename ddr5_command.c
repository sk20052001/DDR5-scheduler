#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

FILE* input_file;
int ctrl, time, core, opCode,front = -1, end = 1;
unsigned long cpu = 0, dim = 0;
long long address;

struct bank{
    int row;
    int col;
};

struct bank bank[numberOfBanks];

int main(int argc, char *argv[3]) {
    if(argc>3)
	{
		printf("Enter Currect number of arguments!");
		return 0;
	}	
	if(argc>1)
	{
		input_file=fopen(argv[1], "r");
	}
	else
	{
		input_file=fopen("trace.txt","r");
	}

	// if(argc>2)
	// {
	// 	fw=fopen(argv[2], "w");
	// }
	// else
	// {
	// 	fw=fopen("dram.txt","w");
	// }

    for(int i = 0; i < numberOfBanks; i++) {
        bank[i].row = -1;
        bank[i].col = 0;
    }

    fscanf(input_file, "%d %d %d %llx", &time, &core, &opCode, &address);
	do {
		
	}while(!foef(input_file) || front != -1 || end == 1);

    return 0;
}