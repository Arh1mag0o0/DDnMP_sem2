#include <stm32f10x.h>
#include <stdio.h>
#include <stdint.h>
/*Определение прототипов функциий*/
void pwm_pin_output_14 (void);      //настройка TIM1 канала 4 на ПВМ выход
void pwm_pin_output_13 (void);      //настройка TIM1 канала 3 на ПВМ выход
void pwm_pin_output_12 (void);      //настройка TIM1 канала 2 на ПВМ выход
void pwm_pin_output_11 (void);      //настройка TIM1 канала 1 на ПВМ выход
void delay (uint32_t ticks);        //типо задержка по времени, чем больше передаваемое значение тем больше задержка (но чет не работает)  
void gpiox_push_pull(int32_t portx, int32_t piny); //установка на push_pull порта x пина y,  не доделанная (слишком много(однотипного) кода, можно проще реализовать)
void TIM2_Init(void);               //настройка таймера 2
void TIM2_IRQHandler(void);         //выполнение прерывания при переполнении таймера 2
void stop_TIM2 (void);              // остановка таймера 2