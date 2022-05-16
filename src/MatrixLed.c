#include <STC89xx.h>
#include "MatrixLed.h"

// 寄存器1数据输入口
SBIT(MATRIX_DS1, _P0, 0);
// 寄存器1 storage控制器，将串口数据寄存器送到并口输出寄存器，上升沿有效
SBIT(MATRIX_STCP1, _P0, 1);
// 寄存器1 shift控制器，将数据从DS输入口移位进入移动寄存器，上升沿有效
SBIT(MATRIX_SHCP1, _P0, 2);
// 寄存器2同理
SBIT(MATRIX_DS2, _P0, 3);
SBIT(MATRIX_STCP2, _P0, 4);
SBIT(MATRIX_SHCP2, _P0, 5);

unsigned char MATRIX_X[] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
unsigned char MATRIX_Y[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void MatrixLedDelay() {
    unsigned int n = 4587 * 7;
    while (n > 0)
    {
        n--;
    }
}

void _74HC595WriteBety(unsigned char type, unsigned char data) {
    // 每次移动8位数据到寄存器中
	for(unsigned char i = 0; i < 8; i++)
	{
        if (0x00 == type)
        {
            MATRIX_DS1 = data & (0x80 >> i);
            MATRIX_SHCP1 = 1;
            MATRIX_SHCP1 = 0;
        }
        else if (0x01 == type)
        {
            MATRIX_DS2 = data & (0x80 >> i);
            MATRIX_SHCP2 = 1;
            MATRIX_SHCP2 = 0;
        }
	}
    // 每次将8位数据寄存到输出寄存器
    if (0x00 == type)
    {
        MATRIX_STCP1 = 1;
        MATRIX_STCP1 = 0;
    }
    else if (0x01 == type)
    {
        MATRIX_STCP2 = 1;
        MATRIX_STCP2 = 0;
    }
}
// 初始化控制器，将控制器置低电平
void MatrixLedInit() {
    MATRIX_STCP1 = 0;
    MATRIX_SHCP1 = 0;
    MATRIX_STCP2 = 0;
    MATRIX_SHCP2 = 0;
    // 初始化屏幕
    _74HC595WriteBety(0x00, 0x01);
    _74HC595WriteBety(0x01, 0x00);
    unsigned char col = 0x01;
    for (unsigned char i = 0; i < 8; i++)
    {
        MatrixLedDelay();
        col <<= 1;
        _74HC595WriteBety(0x00, col);
    }
    MatrixLedDelay();
    _74HC595WriteBety(0x00, 0x00);

    MatrixLedDelay();
    _74HC595WriteBety(0x00, 0xFF);
    unsigned char row = 0x01;
    for (unsigned char j = 0; j < 8; j++)
    {
        MatrixLedDelay();
        row <<= 1;
        _74HC595WriteBety(0x01, row);
    }
    MatrixLedDelay();
    _74HC595WriteBety(0x01, 0xFF);
}

void MatrixLedZero(unsigned char x, unsigned char y) {
    _74HC595WriteBety(0x00, 0x00);
    _74HC595WriteBety(0x01, 0x00);
    if (x > 7)
    {
        x = 7;
    }
    _74HC595WriteBety(0x01, MATRIX_X[x]);
    // MatrixLedDelay();
    if (y > 7)
    {
        y = 7;
    }
    _74HC595WriteBety(0x00, MATRIX_Y[y]);
}