#ifndef __Task2_H
#define __Task2_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define TASK2_CNT1					 1200
#define TASK2_CNT2					 1200
#define TASK2_DEFAULT_SPEED1 70
#define TASK2_DEFAULT_SPEED2 35	

void Task2_Init(int speed1,int speed2);
void Task2_Loop(void);
int check_get(void);
#ifdef __cplusplus
}
#endif
#endif
