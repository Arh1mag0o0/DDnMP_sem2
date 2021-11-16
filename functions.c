#include <stdio.h>
#include <stdint.h>
#include "main.h"

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

uint32_t pin_state = 0;

void led_blink_exemple_1(uint32_t tick_delay)
{
	/****************************************************************/
	/*Программа моргания светодиодом каждые tick_delay тиков*/
	/****************************************************************/

		// Установить 1 на порт GPIOA пин 5
        GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_All;
        GPIOC->BSRR = GPIOC->BSRR | GPIO_PIN_All;
		delay (tick_delay);
		// Сбросить состояние в 0 на порте GPIOA пин 
        GPIOA->BRR = GPIOA->BRR | GPIO_PIN_All;
        GPIOC->BRR = GPIOC->BRR | GPIO_PIN_All;
		delay (tick_delay); 
}

void button_led_exemple_2(void)
{
    
    
    
    
		/****************************************************************/
	/*Выключение сетодиода при нажатии кнопки*/
	/****************************************************************/
		// Считать состояние порта GPIOC пина 13

        pin_state = GPIOC->IDR & GPIO_PIN_11;
		if ( pin_state == 0 )
		{
			// Установить 1 на порт GPIOA пин 5
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_0;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_1;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_2;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_3;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_4;
			GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_5;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_6;
            GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_7;
			pin_state = 0;
		}
		else
		{
			// Сбросить состояние в 0 на порте GPIOA пин 
			GPIOA->BRR = GPIOA->BRR | GPIO_PIN_0;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_1;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_2;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_3;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_4;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_5;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_6;
            GPIOA->BRR = GPIOA->BRR | GPIO_PIN_7;
		}
}

void delay (uint32_t ticks)
{
	for (uint32_t i = 0; i < ticks; i++)
	{
	}
}


/*Обработчик прерывания по линии EXTI15_10*/
void EXTI15_10_IRQHandler (void)
{
		EXTI->PR |= GPIO_PIN_13;
        EXTI->PR |= GPIO_PIN_10;
		if (pin_state == 0)
		{
			pin_state = 1;
		}
		else
		{
			pin_state = 0;
		}
}


void HardFault_Handler (void)
{
	while(1)
	{}
}

void change_led_state_IT_exemple_3(void)
{
		/****************************************************************/
		/*Обработка нажатия кнопки с помощью прерывания и включение светодиода*/
		/****************************************************************/
		if ( pin_state == 0 )
		{
			// Установить 1 на порт GPIOA пин 5
			GPIOA->BSRR = GPIOA->BRR | GPIO_PIN_5;
		}
		else
		{
			// Сбросить состояние в 0 на порте GPIOA пин 
			GPIOA->BRR = GPIOA->BSRR | GPIO_PIN_5;
		}
}

void init_IT_for_exemple_3(void)
{
	/****************************************************************/
	/*Включение прерываний от пина 13*/
	/****************************************************************/
	//Включение тактирования на блок альтернативных функций
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_AFIOEN;
	//Разрешить прерывание 13 пина порта С
	AFIO->EXTICR[3] = 0x0020;
	//Разрешить прерывание 13 линии
	EXTI->IMR|=(EXTI_IMR_MR13);
	EXTI->EMR|=(EXTI_EMR_MR13);
	
	//Прерывание 13 линии по спадающему фронту фронту
	EXTI->RTSR|=(EXTI_RTSR_TR13);
	
	/* Разрешение прерываний */
	NVIC->ISER[(((uint32_t)EXTI15_10_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)EXTI15_10_IRQn) & 0x1FUL));
}

void tik (void)
{

}
