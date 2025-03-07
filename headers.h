#define numberOfBanks 32
#define queueSize 16

#define tburst 8
#define trcd 39
#define tras 76
#define trrdl 12
#define trrds 8
#define trtp 18
#define trp 39
#define tcl 40
#define cwl 38
#define twr 30
#define tccdl 12
#define tccds 8
#define tccdlw 48
#define tccdsw 8
#define tccdlrtw 16
#define tccdsrtw 16
#define tccdlwtr 70
#define tccdswtr 52

struct bank {
	int status, row;
};

struct queue {
	int time, core, opCode, row, col, chanel, bnk, bnkGp, bank;
};