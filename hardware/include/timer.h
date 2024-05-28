// timer.h
#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

extern hw_timer_t* timer0; // 声明定时器0为外部变量
extern hw_timer_t* timer1; // 声明定时器1为外部变量
extern volatile bool timer0Flag; // 声明定时器0标志为外部变量
extern volatile bool timer1Flag; // 声明定时器1标志为外部变量
void IRAM_ATTR onTimer0(); // 定时器0中断服务例程
void IRAM_ATTR onTimer1(); // 定时器1中断服务例程
void setupTimer0(uint64_t time); // 设置定时器0
void setupTimer1(uint64_t time); // 设置定时器1
void tearDownTimer0(); // 清理定时器0资源
void tearDownTimer1(); // 清理定时器1资源

#endif // TIMER_H
