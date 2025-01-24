#define numberOfBanks 32
#define queueSize 16

struct bank {
	int status, row;
};

struct queue {
	int time, core, opCode, row, col, channel, bnk, bnkGp, bank;
};