#include <STC89xx.h>
#include "Nixie.h"

// 位选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE1, _P2, 0);
// 段选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE2, _P2, 1);
// 寄存器I/O口，位选
SFR(NEXIE_DATA, _P1);
// 段选
SFR(NEXIE_POS, _P3);

// 数码管初始值
unsigned char NEXIE_BUFF[] = {0xC0, 0xC0, 0xC0, 0xC0};
// 编码表
unsigned char NEXIE_CODE[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// 位选表
unsigned char NEXIE_LOCAL[] = {0x04, 0x08, 0x10, 0x20};

// 打印数码管显示
void NexiePrint(unsigned char local, unsigned char data) {
    if (local < 1 || local > 4)
    {
        local = 1;
    }
    if (data > 9)
    {
        data = 0;
    }
    NEXIE_BUFF[--local] = NEXIE_CODE[data];
}

// 选择数码管
void NexieLocal(unsigned char local) {
    NEXIE_POS = NEXIE_LOCAL[local];
    NEXIE_LE2 = 0x01;
    NEXIE_LE2 = 0x00;
}

// 显示数码管
void NexieByte(unsigned char data) {
    NEXIE_DATA = data;
    NEXIE_LE1 = 0x01;
    NEXIE_LE1 = 0x00;
}

// 扫描刷新数据
void NexieScan(unsigned char local, unsigned char data) {
    NEXIE_DATA = 0xFF;
    NexieLocal(local);
    NexieByte(data);
}

// 定时器2ms循环一次
void NexieLoop() {
    static unsigned char index = 0;
    NexieScan(index, NEXIE_BUFF[index]);
    index++;
    if (index > 3)
    {
        index = 0;
    }
}