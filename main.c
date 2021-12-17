#include "functions.h"
#define SYSCLOCK 72000000U
int main (void)
{        
        //включение портов для светодиодов
    gpiox_push_pull(0xA, 11);       //порт А пин 11(PWM1/4)
    gpiox_push_pull(0xA, 9);        //порт А пин 9(PWM1/2)
    gpiox_push_pull(0xA, 10);       //порт А пин 10(PWM1/3)
    gpiox_push_pull(0xA, 8);        //порт А пин 8(PWM1/1)
    
    //включение каналов таймера 1 на генерацию ПВМ на выходах
    pwm_pin_output_14();            //канал 1/4
   // pwm_pin_output_13();          //канал 1/3
    pwm_pin_output_12();            //канал 1/2
   // pwm_pin_output_11();          //канал 1/1
    
      TIM2_Init();                  // настройка таймера 2
      TIM2->DIER |= TIM_DIER_UIE;   // обновление таймера 2
      TIM2->CR1 |= TIM_CR1_CEN;     // запуск таймера 2   
    while (1)
    {       
    }
}  