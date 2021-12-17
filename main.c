
#include "functions.h"
#define SYSCLOCK 72000000U
#define PERIOD(f)       (1e6 / f)
#define PRESCALER       (SystemCoreClock / 1e6)
#define FREQ            1000
int main (void)
{
        
        //включение портов
       gpiox_push_pull(0xA, 11);
       gpiox_push_pull(0xA, 9);
       gpiox_push_pull(0xA, 10);
       gpiox_push_pull(0xA, 8);
    
    //включение каналов таймера 1 на генерацию ПВМ на выходах
       pwm_pin_output_14();
      // pwm_pin_output_13();
       pwm_pin_output_12();
      // pwm_pin_output_11();
    
    
      TIM2_Init();                // настройка таймера 2
      TIM2->DIER |= TIM_DIER_UIE; // обновление таймера 2
      TIM2->CR1 |= TIM_CR1_CEN;   // запуск таймера 2
        
    while (1)
    {       
    }
}  