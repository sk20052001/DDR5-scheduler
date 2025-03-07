#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

FILE *inputFile, *outputFile;

int main(int argc, char *argv[3]) {
    if (argc > 3) {
		printf("Enter Currect number of arguments!");
		return 0;
	}	
	if (argc>1) {
		inputFile = fopen(argv[1], "r");
	} else {
		inputFile = fopen("trace.txt", "r");
	}
	if (argc>2) {
		outputFile = fopen(argv[2], "w");
	} else {
		outputFile = fopen("dram.txt","w");
	}

    // fscanf(inputFile, "%d %d %d %llx", &time, &core, &opCode, &address);

    return 0;
}