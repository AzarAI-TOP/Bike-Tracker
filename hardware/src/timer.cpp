// timer.cpp
#include "timer.h"

hw_timer_t* timer0 = NULL; // 定义定时器0变量
hw_timer_t* timer1 = NULL; // 定义定时器1变量
volatile bool timer0Flag = false; // 定义定时器0标志变量并初始化为false
volatile bool timer1Flag = false; // 定义定时器1标志变量并初始化为false

void IRAM_ATTR onTimer0() {
    timer0Flag = true;
}

void IRAM_ATTR onTimer1() {
    timer1Flag = true;
}

void setupTimer0(uint64_t time) {
    // 初始化定时器0，设置中断等
    timer0 = timerBegin(0, 80, true); // 使用定时器0，分频80，上升沿触发
    timerAttachInterrupt(timer0, &onTimer0, true); // 绑定中断服务例程
    timerAlarmWrite(timer0, time, true); // 设置定时器周期为60秒（60,000,000us）
    timerAlarmEnable(timer0); // 启动定时器
}

void setupTimer1(uint64_t time) {
    // 初始化定时器1，设置中断等
    timer1 = timerBegin(1, 80, true); // 使用定时器1，分频80，上升沿触发
    timerAttachInterrupt(timer1, &onTimer1, true); // 绑定中断服务例程
    timerAlarmWrite(timer1, time, true); // 设置定时器周期为1秒（1,000,000us）
    timerAlarmEnable(timer1); // 启动定时器
}

void tearDownTimer0() {
    // 清理定时器0资源
    timerAlarmDisable(timer0);
    timerDetachInterrupt(timer0);
    timerEnd(timer0);
}

void tearDownTimer1() {
    // 清理定时器1资源
    timerAlarmDisable(timer1);
    timerDetachInterrupt(timer1);
    timerEnd(timer1);
}
