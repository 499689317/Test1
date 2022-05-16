#include <stdlib.h>
#include "LCD1602.h"
#include "Test1.h"
#include "MatrixLed.h"

unsigned char SnakeX[10] = {0};
unsigned char SnakeY[10] = {0};
unsigned char SnakeLen = 0, Direction = 0;
unsigned char FoodX = 0, FoodY = 0;
unsigned char FootX = 0, FootY = 0;
unsigned int Seeder = 0, Score = 0;
unsigned char Inited = 0;

void SnakeFood() {
    srand(Seeder);
    FoodX = rand() % 8;
    FoodY = rand() % 8;
    for (unsigned char i = 0; i < SnakeLen; i++)
    {
        if (FoodX == SnakeX[i] && FoodY == SnakeY[i])
        {
            SnakeFood();
        }
    }
}

void GameInit() {
    MatrixLedInit();
    // 初始化蛇形状
    SnakeX[0] = 0;
    SnakeY[0] = 0;
    SnakeLen = 1;
    // 初始化默认方向
    Direction = 1;
    // 初始化食物
    SnakeFood();
    // 初始化完成
    Inited = 1;
}

// 捕猎
void SnakeHunter() {
    if (FoodX == SnakeX[0] && FoodY == SnakeY[0])
    {
        SnakeFood();
        SnakeX[SnakeLen] = FootX;
        SnakeY[SnakeLen] = FootY;
        SnakeLen++;
        Score += 100;
        LCD1602PrintUnsignedNum(2, 7, Score);
    }
}

// 自动行走
void SnakeMove() {
    unsigned char len = SnakeLen - 1;
    FootX = SnakeX[len];
    FootY = SnakeY[len];
    while (len > 0)
    {
        // 每个节点往后推一位，此时已去掉最后一位
        SnakeX[len] = SnakeX[len - 1];
        SnakeY[len] = SnakeY[len - 1];
        len--;
    }
    // 头按当前方向更新一次坐标
    switch (Direction)
    {
    case 1:// 向上
        SnakeY[0]++;
        break;
    case 2:// 向下
        SnakeY[0]--;
        break;
    case 3:// 向左
        SnakeX[0]--;
        break;
    case 4:// 向右
        SnakeX[0]++;
        break;
    default:
        break;
    }
}

// 游戏检测
unsigned char SnakeScan() {
    if (Inited == 0)
    {
        return 2;
    }
    // 超出矩阵
    if (SnakeX[0] > 7 || SnakeY[0] > 7)
    {
        return 1;
    }
    // 碰到自已
    for (unsigned char i = 4; i < SnakeLen; i++)
    {
        if (SnakeX[0] == SnakeX[i] && SnakeY[0] == SnakeY[i])
        {
            return 1;
        }
    }
    // 正常
    return 0;
}

// 游戏循环
void GameLoop() {
    Seeder++;
    if (Seeder > 47283)
    {
        Seeder = 0;
    }
    
    unsigned char flag = SnakeScan();
    if (flag == 0)
    {
        SnakeMove();
        SnakeHunter();
    }
    if (flag == 1)
    {
        LCD1602PrintString(1, 13, "OVER");
    }
    if (flag == 2)
    {
        LCD1602PrintString(1, 13, "INIT");
    }
}

void GameDirection(unsigned char direction) {
    Direction = direction;
}

// 绘制渲染
void GameDraw() {
    for (unsigned char i = 0; i < SnakeLen; i++)
    {
        MatrixLedZero(SnakeX[i], SnakeY[i]);
        MatrixLedZero(FoodX, FoodY);
    }
}
