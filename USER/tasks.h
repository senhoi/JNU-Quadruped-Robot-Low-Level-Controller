#ifndef _TASKS_H
#define _TASKS_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
//#include "timer.h"
#include "motor.h"
#include "SCA_API.h"
#include "led.h"
#include "lcd.h"
#include "can.h"

void init_task(void);
void init_task_hardware(void);
void init_task_controller(void);
void init_task_innfos(void);
void ctrl_task(void);
void loop_task(void);

#endif
