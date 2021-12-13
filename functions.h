#include <stm32f10x.h>
#include <stdio.h>
#include <stdint.h>
/*Определение прототипов функциий*/
void pwm_pin_output_14 (void);
void tim_pwm (void);
void delay (uint32_t ticks);
void init_IT_for_exemple_3(void);
void gpiox_push_pull(int32_t portx, int32_t piny);
