
#include "functions.h"
#define SYSCLOCK 72000000U
#define PERIOD(f)       (1e6 / f)
#define PRESCALER       (SystemCoreClock / 1e6)
#define FREQ            1000
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */
void led_blink_exemple_1(uint32_t tick_delay);
static void TIM2_Init(void);
void stop_TIM2 (void);
void TIM2_IRQHandler(void);
uint32_t tmpreg = 0;
uint8_t tim2_count = 0;
int main (void)
{
        
        //включение портов
       gpiox_push_pull(0xA, 11);
       gpiox_push_pull(0xC, 13);
       pwm_pin_output_14();
       TIM2_Init();                // настройка таймера 2
       TIM2->DIER |= TIM_DIER_UIE; // обновление таймера 2
       TIM2->CR1 |= TIM_CR1_CEN;   // запуск таймера 2
    while (1)
    {       
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
    delay(tick_delay);    
    }
    for (;i>0;i--)
    {
    TIM1->CCR4 = i;
    delay(tick_delay);
    }
    TIM1->CCR4 = 0;
}
static void TIM2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // тактирование таймера
    NVIC_EnableIRQ(TIM2_IRQn);          // глобальные прерывания (без них не работают локальные)
    TIM2->PSC = 3599;                   // делитель
    TIM2->ARR = 2000;                   // зачение до которого считать
}
void stop_TIM2 (void)                   // остановка таймера 2
{
    TIM2->CR1 &= ~(TIM_CR1_CEN);
}   
void TIM2_IRQHandler(void)              //выполнение прерывания при переполнении таймера 2
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~(TIM_SR_UIF);
    switch(tim2_count)
    {
        case 0:  TIM1->CCR4 = 100; 
        break; 
        case 1:  TIM1->CCR4 = 200; 
        break;        
        case 2:  TIM1->CCR4 = 300; 
        break;  
        case 3:  TIM1->CCR4 = 400; 
        break;
        case 4:  TIM1->CCR4 = 500; 
        break; 
        case 5:  TIM1->CCR4 = 600; 
        break;
        case 6:  TIM1->CCR4 = 700; 
        break;
        case 7:  TIM1->CCR4 = 800; 
        break;
        case 8:  TIM1->CCR4 = 900; 
        break;
        case 9:  TIM1->CCR4 = 1000; 
        break;        
    }
    tim2_count++;
    if(tim2_count>9) 
        tim2_count=0;
    }
}