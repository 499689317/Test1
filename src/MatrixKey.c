#include <STC89xx.h>
#include "MatrixKey.h"

SFR(MATRIX_PORT, _P2);
SBIT(MATRIX_K1, _P2, 0);
SBIT(MATRIX_K2, _P2, 1);
SBIT(MATRIX_K3, _P2, 2);
SBIT(MATRIX_K4, _P2, 3);
SBIT(MATRIX_K5, _P2, 4);
SBIT(MATRIX_K6, _P2, 5);
SBIT(MATRIX_K7, _P2, 6);
SBIT(MATRIX_K8, _P2, 7);

unsigned char MATRIX_KEY = 0;

void MatrixKeyDelay() {
    unsigned short n = 4587;
    while (n > 0)
    {
        n--;
    }
}
// 检测按建松开状态
unsigned char MatrixKeyDelayUp() {
    unsigned char key=0;
	MATRIX_PORT = 0xFF;
	MATRIX_K8 = 0;
	if(MATRIX_K4 == 0){ MatrixKeyDelay(); while(MATRIX_K4 == 0); MatrixKeyDelay(); key = 1; }
	if(MATRIX_K3 == 0){ MatrixKeyDelay(); while(MATRIX_K3 == 0); MatrixKeyDelay(); key = 2; }
	if(MATRIX_K2 == 0){ MatrixKeyDelay(); while(MATRIX_K2 == 0); MatrixKeyDelay(); key = 3; }
	if(MATRIX_K1 == 0){ MatrixKeyDelay(); while(MATRIX_K1 == 0); MatrixKeyDelay(); key = 4; }
	MATRIX_PORT = 0xFF;
	MATRIX_K7 = 0;
	if(MATRIX_K4 == 0){ MatrixKeyDelay(); while(MATRIX_K4 == 0); MatrixKeyDelay(); key = 5; }
	if(MATRIX_K3 == 0){ MatrixKeyDelay(); while(MATRIX_K3 == 0); MatrixKeyDelay(); key = 6; }
	if(MATRIX_K2 == 0){ MatrixKeyDelay(); while(MATRIX_K2 == 0); MatrixKeyDelay(); key = 7; }
	if(MATRIX_K1 == 0){ MatrixKeyDelay(); while(MATRIX_K1 == 0); MatrixKeyDelay(); key = 8; }
	MATRIX_PORT = 0xFF;
	MATRIX_K6 = 0;
	if(MATRIX_K4 == 0){ MatrixKeyDelay(); while(MATRIX_K4 == 0); MatrixKeyDelay(); key = 9; }
	if(MATRIX_K3 == 0){ MatrixKeyDelay(); while(MATRIX_K3 == 0); MatrixKeyDelay(); key = 10; }
	if(MATRIX_K2 == 0){ MatrixKeyDelay(); while(MATRIX_K2 == 0); MatrixKeyDelay(); key = 11; }
	if(MATRIX_K1 == 0){ MatrixKeyDelay(); while(MATRIX_K1 == 0); MatrixKeyDelay(); key = 12; }
	MATRIX_PORT = 0xFF;
	MATRIX_K5 = 0;
	if(MATRIX_K4 == 0){ MatrixKeyDelay(); while(MATRIX_K4 == 0); MatrixKeyDelay(); key = 13; }
	if(MATRIX_K3 == 0){ MatrixKeyDelay(); while(MATRIX_K3 == 0); MatrixKeyDelay(); key = 14; }
	if(MATRIX_K2 == 0){ MatrixKeyDelay(); while(MATRIX_K2 == 0); MatrixKeyDelay(); key = 15; }
	if(MATRIX_K1 == 0){ MatrixKeyDelay(); while(MATRIX_K1 == 0); MatrixKeyDelay(); key = 16; }
	return key;
}

// 扫描按建松开状态
unsigned char MatrixKeyScanUp() {
	unsigned char key = 0;
	key = MATRIX_KEY;
	MATRIX_KEY = 0;
	return key;
}
void MatrixKeyCheck(unsigned char now, unsigned char last) {
	if (now == 0 && last == 1) { MATRIX_KEY = 1; }
	if (now == 0 && last == 2) { MATRIX_KEY = 2; }
	if (now == 0 && last == 3) { MATRIX_KEY = 3; }
	if (now == 0 && last == 4) { MATRIX_KEY = 4; }
	if (now == 0 && last == 5) { MATRIX_KEY = 5; }
	if (now == 0 && last == 6) { MATRIX_KEY = 6; }
	if (now == 0 && last == 7) { MATRIX_KEY = 7; }
	if (now == 0 && last == 8) { MATRIX_KEY = 8; }
	if (now == 0 && last == 9) { MATRIX_KEY = 9; }
	if (now == 0 && last == 10) { MATRIX_KEY = 10; }
	if (now == 0 && last == 11) { MATRIX_KEY = 11; }
	if (now == 0 && last == 12) { MATRIX_KEY = 12; }
	if (now == 0 && last == 13) { MATRIX_KEY = 13; }
	if (now == 0 && last == 14) { MATRIX_KEY = 14; }
	if (now == 0 && last == 15) { MATRIX_KEY = 15; }
	if (now == 0 && last == 16) { MATRIX_KEY = 16; }
}
unsigned char MatrixKeyScan() {
	unsigned char key = 0;
	MATRIX_PORT = 0xFF;
	MATRIX_K8 = 0;
	if(MATRIX_K4 == 0){ key = 1; }
	if(MATRIX_K3 == 0){ key = 2; }
	if(MATRIX_K2 == 0){ key = 3; }
	if(MATRIX_K1 == 0){ key = 4; }
	MATRIX_PORT = 0xFF;
	MATRIX_K7 = 0;
	if(MATRIX_K4 == 0){ key = 5; }
	if(MATRIX_K3 == 0){ key = 6; }
	if(MATRIX_K2 == 0){ key = 7; }
	if(MATRIX_K1 == 0){ key = 8; }
	MATRIX_PORT = 0xFF;
	MATRIX_K6 = 0;
	if(MATRIX_K4 == 0){ key = 9; }
	if(MATRIX_K3 == 0){ key = 10; }
	if(MATRIX_K2 == 0){ key = 11; }
	if(MATRIX_K1 == 0){ key = 12; }
	MATRIX_PORT = 0xFF;
	MATRIX_K5 = 0;
	if(MATRIX_K4 == 0){ key = 13; }
	if(MATRIX_K3 == 0){ key = 14; }
	if(MATRIX_K2 == 0){ key = 15; }
	if(MATRIX_K1 == 0){ key = 16; }
	return key;
}
void MatrixKeyLoop() {
	static unsigned char s1 = 0, s2 = 0;
	s2 = s1;
	s1 = MatrixKeyScan();
	MatrixKeyCheck(s1, s2);
}
