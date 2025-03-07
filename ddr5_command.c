#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

struct bank bank[numberOfBanks];
struct queue queue[queueSize];

FILE *inputFile, *outputFile;
int incrementFlag, time, core, opCode, front = -1, rear = -1, end = 1;
unsigned long int cpu = 0, dim = 0;
unsigned long long int address;

void enqueue() {
	if (front == -1) {
		front = 0;
	}
	rear = (rear + 1) % queueSize;
	queue[rear].time = time;
	queue[rear].core = core;
	queue[rear].opCode = opCode;
	queue[rear].row = (address >> 18) & ((1 << 16) - 1);
	queue[rear].col = (((address >> 12) & (0x3F)) << 4) | ((address >> 2) & (0xF));
	queue[rear].bnk = (address >> 10) & (0x3);
	queue[rear].bnkGp = (address & ((0x7) << 7)) >> 7;
	queue[rear].chanel = (address & (1 << 6)) >> 6;
	queue[rear].bank= (queue[rear].bnkGp * 4) + queue[rear].bnk;
}

void deq()
{
	if(front == rear)
	{		
		rear = front = - 1;
	}

	else 
	{
		front = (front + 1) % numberOfBanks;
	}	
}


void delay(int clockCycles) {
	for (int i = 0; i < clockCycles; i++) {
		if (front != ((rear + 1) % queueSize)) {
			if (time <= cpu) {
				if (!feof(inputFile)) {
					enqueue();
					if (fscanf(inputFile, "%d %d %d %llx", &time, &core, &opCode, &address) == EOF) {
						end = 0;
					}
				} else if (end) {
					enqueue();
					end = 0;
				}
			}
		}
		cpu++;
		dim = cpu / 2;
	}
}

int isFull() {
	if ((front == rear + 1) || (front == 0 && rear == numberOfBanks - 1)) return 1;
	return 0;
}
  
int empty() {
	return front==-1;
}

void dimm(struct queue queue) {
	if (bank[queue.bnk].status==0) {
		fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "ACT0", 3, queue.bnkGp, 3, queue.bank, 3, queue.row);		
		delay(2);
		fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "ACT1", 3, queue.bnkGp, 3, queue.bank, 3, queue.row);
		bank[queue.bnk].status=1;
		bank[queue.bnk].row=queue.row;
		delay(2*trcd);
		if(queue.opCode!=1) {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(tcl+tburst));
			deq();
			incrementFlag=1;
			return;
		} else {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(cwl+tburst+twr));
			deq();
			incrementFlag=1;
			return;
		}
	} else if (bank[queue.bnk].status == 1 && bank[queue.bnk].row != queue.row) {
		fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d\n", 10, cpu, 3, queue.chanel, 6, "PRE", 3, queue.bnkGp, 3, queue.bank);
		delay(2*trp);
		fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "ACT0", 3, queue.bnkGp, 3, queue.bank, 3, queue.row);		
		delay(2);
		fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "ACT1", 3, queue.bnkGp, 3, queue.bank, 3, queue.row);
		bank[queue.bnk].status=1;
		bank[queue.bnk].row=queue.row;
		delay(2*trcd);
		if(queue.opCode!=1) {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(tcl+tburst));
		} else {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(cwl+tburst+twr));
		}
		deq();
		incrementFlag=1;
		return;
	} else {
		if(queue.opCode!=1) {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "RD1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(tcl+tburst));
			
		} else {
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR0", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2);
			fprintf(outputFile, "%-*lu%-*d%-*s%-*d%-*d%-*x\n", 10, cpu, 3, queue.chanel, 6, "WR1", 3, queue.bnkGp, 3, queue.bank, 3, queue.col);
			delay(2*(cwl+tburst+twr));
		}
		deq();
		incrementFlag=1;
		return;
	}	
}

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

	if(argc>2)
	{
		outputFile=fopen(argv[2], "w");
	}
	else
	{
		outputFile=fopen("dram.txt","w");
	}

    for (int i = 0; i < numberOfBanks; i++) {
        bank[i].row = -1;
        bank[i].status = 0;
    }

    fscanf(inputFile, "%d %d %d %llx", &time, &core, &opCode, &address);
	do {
		incrementFlag = 0;
		if (cpu % 2 == 0) {
			if (front != -1) {
				dimm(queue[front]);
			}
		}
		if (front != ((rear + 1) % queueSize)) {
			if (time <= cpu) {
				if (!feof(inputFile)) {
					enqueue();
					if (fscanf(inputFile, "%d %d %d %llx", &time, &core, &opCode, &address) == EOF) {
						end = 0;
					}
				} else if (end) {
					enqueue();
					end = 0;
				}
			}
		}
		if (incrementFlag == 0) {
			cpu++;
		}
		dim = cpu / 2;
	} while (!feof(inputFile) || front != -1 || end == 1);

    return 0;
}