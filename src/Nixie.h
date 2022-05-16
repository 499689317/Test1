/**
 * 数码管驱动
 */

#ifndef NIXIE_H
#define NIXIE_H

// 打印数码管显示
extern void NexiePrint(unsigned char local, unsigned char data);
// 定时器2ms循环一次
extern void NexieLoop();

#endif
