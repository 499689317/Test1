#include <mcs51/lint.h>
#include <stdlib.h>
#include "LCD1602.h"
#include "Timer0.h"
#include "MatrixKey.h"
#include "MatrixLed.h"
#include "Test1.h"

void main()
{
    LCD1602Init();
    Timer0Init();
    GameInit();
    LCD1602PrintString(1, 1, "snake ");
    LCD1602PrintString(2, 1, "score ");
    LCD1602PrintUnsignedNum(2, 7, 0);
    while (1)
    {
        GameDraw();
        unsigned char key = MatrixKeyScanUp();
        if (key)
        {
            unsigned char dir = 0;
            if (key == 11)
            {
                dir = 1;
                LCD1602PrintString(1, 7, "up   ");
            }
            else if (key == 14)
            {
                dir = 3;
                LCD1602PrintString(1, 7, "left ");
            }
            else if (key == 15)
            {
                dir = 2;
                LCD1602PrintString(1, 7, "down ");
            }
            else if (key == 16)
            {
                dir = 4;
                LCD1602PrintString(1, 7, "right");
            }
            GameDirection(dir);
        }
    }
}

void Timer0Inter() __interrupt(1) {
    Timer0Loop();
    static unsigned int gameIndex = 0, keyIndex = 0;
    if (gameIndex == 700)
    {
        gameIndex = 0;
        GameLoop();
    }
    gameIndex++;
    if (keyIndex == 120)
    {
        keyIndex = 0;
        MatrixKeyLoop();
    }
    keyIndex++;
}