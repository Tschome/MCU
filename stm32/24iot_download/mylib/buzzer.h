#ifndef __BUZZER_H
#define __BUZZER_H
/*
BEEP	PC7
�ߵ�ƽ	��
�͵�ƽ	����
*/
#include "stm32f10x_conf.h"

extern void buzzer_init(void);

extern void buzzer_on(void);

extern void buzzer_off(void);

#endif



