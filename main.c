
#include "functions.h"
#define SYSCLOCK 72000000U
#define PERIOD(f)       (1e6 / f)
#define PRESCALER       (SystemCoreClock / 1e6)
#define FREQ            1000
void led_blink_exemple_1(uint32_t tick_delay);
void led_blink_exemple_2(uint32_t tick_delay);

int main (void)
{
    
    //включение портов 
    gpiox_push_pull(0xA, 10);
    gpiox_push_pull(0xA, 8);
    pwm_pin_output_14();
    
    while (1)
    {
      led_blink_exemple_1(10);
      led_blink_exemple_2(10);  
    }
}

void led_blink_exemple_1(uint32_t tick_delay)
{
	/****************************************************************/
	/*Программа моргания светодиодом каждые tick_delay тиков*/
	/****************************************************************/
    int32_t i=1;
    for (;i<999;i++)
    {
    TIM1->CCR4 = i;
        i=i+100;
    }
    for (;i>0;i--)
    {
    TIM1->CCR4 = i;
        i=i-100;
    }
    TIM1->CCR4 = 0;
}

void led_blink_exemple_2(uint32_t tick_delay)
{
	/****************************************************************/
	/*Программа моргания светодиодом каждые tick_delay тиков*/
	/****************************************************************/
    int32_t i=1;
    for (;i<999;i++)
    {
    TIM1->CCR3 = i;
        i=i+100;
    }
    for (;i>0;i--)
    {
    TIM1->CCR3 = i;
        i=i-100;
    }
    TIM1->CCR3 = 0;
}

