#include <STC89xx.h>
#include "Timer0.h"

// TCON控制位，选择使用哪个定时器，TF0, TR0为T0定时器控制位
SBIT(TIMER0_TF, _TCON, 5);// TF硬件置1，表示计数溢出，需要软件置0
SBIT(TIMER0_TR, _TCON, 4);// 置1，表示开启定时器
// TMOD寄存器，选择定时器模式，不可位寻址
SFR(TIMER0_TMOD, _TMOD);
// T0计数器
SFR(TIMER0_TH, _TH0);
SFR(TIMER0_TL, _TL0);
// 开启总中断控制位
SBIT(TIMER0_EA, _IE, 7);
// T0中断控制位，置1为开启中断
SBIT(TIMER0_ET, _IE, 1);

// 计算定时器溢出率
// 晶振频率为11.0592MHz，1秒钟11059200个时钟周期，12时钟周期 = 1机器周期
#define TIMER0_FOSC 11059200
// 计算1ms可以运行的机器周期
#define TIMER0_1MS 65525 - (TIMER0_FOSC / 1000 / 12)

void Timer0Init() {
    // 选择模式1计数
    TIMER0_TMOD = 0x01;
    // 初始化计数器，计数器从TIMER0_1MS开始计数，溢出时刚好1ms
    TIMER0_TL = TIMER0_1MS;
    TIMER0_TH = TIMER0_1MS >> 8;
    // 开始定时计数, TF置0，TR置1
    TIMER0_TF = 0x00;
    TIMER0_TR = 0x01;
    // 开启T0中断
    TIMER0_EA = 0x01;
    TIMER0_ET = 0x01;
}

// 循环定时器计数
void Timer0Loop() {
    TIMER0_TL = TIMER0_1MS;
    TIMER0_TH = TIMER0_1MS >> 8;
    // 软件置0
    TIMER0_TF = 0x00;
}