
#include "main.h"
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


/*Определение прототипов функциий*/
void led_blink_exemple_1(uint32_t tick_delay);
void button_led_exemple_2(void);

void change_led_state_IT_exemple_3(void);
void init_IT_for_exemple_3(void);

void delay (uint32_t ticks);

uint32_t pin_state = 0;
	
int main(void)
{
	
	/****************************************************************/
	/*Инициализация порта A пина 5 на выход для моргания светодиодом*/
	/****************************************************************/
	
	/* Установка регистра CRL битов MODE5[1:0] на максимальную частоту 50 МHz */
	/* 
	Макроподстановки
	
	GPIO_CRL_MODE5_0 = 0b0000 0000 0001 0000 0000 0000 0000 0000
	GPIO_CRL_MODE5_1 = 0b0000 0000 0010 0000 0000 0000 0000 0000
	
	GPIO_CRL_CNF5_0 = 0b0000 0000 0100 0000 0000 0000 0000 0000
	GPIO_CRL_CNF5_1 = 0b0000 0000 1000 0000 0000 0000 0000 0000
	
	RCC_APB2ENR_IOPAEN_Msk = 0b0000 0000 0100 0000 0000 0000 0000 0100
	*/
		/*Включение тактирования для порта А*/
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN_Msk;
	
	
	GPIOA->CRL = (GPIOA->CRL) | ( GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1);
	
	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
	GPIOA->CRL = (GPIOA->CRL) & ( ~( GPIO_CRL_CNF5_0 | GPIO_CRL_CNF5_1));
	
	/****************************************************************/
	/*Инициализация порта С пина 13 на вход для детектирования нажатия кнопки*/
	/****************************************************************/
	
	/* Установка регистра CRL битов MODE13[1:0] на максимальную частоту 50 МHz */
	/* 
	Макроподстановки
	
	GPIO_CRH_MODE13_0 = 0b0000 0000 0001 0000 0000 0000 0000 0000
	GPIO_CRH_MODE13_1 = 0b0000 0000 0010 0000 0000 0000 0000 0000
	
	GPIO_CRH_CNF13_0 = 0b0000 0000 0100 0000 0000 0000 0000 0000
	GPIO_CRH_CNF13_1 = 0b0000 0000 1000 0000 0000 0000 0000 0000
	*/
	
	/*Включение тактирования для портаC*/
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPCEN_Msk;
	
	GPIOC->CRH = (GPIOC->CRH) & ( ~( GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1));
	/* Установка регистра CRL битов CNF13[1:0] на тип входа pull-up */
	GPIOC->CRH = ((GPIOC->CRH) | ( GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13_1));
	GPIOC->ODR = ((GPIOC->ODR) | ( GPIO_PIN_13));
	
	
	/*Инициализация прерываний для примера №3*/
	init_IT_for_exemple_3();
	
  while (1)
  {
		/******EXEMPLE_1*******/
	//led_blink_exemple_1(100000);
		/******EXEMPLE_1*******/
	//	button_led_exemple_2();
		/******EXEMPLE_1*******/
		change_led_state_IT_exemple_3();
  }
}


void led_pwm_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
​
    // PA3 as output, alternative, push-pull
    GPIOA->CRL &= ~GPIO_CRL_CNF3;
    GPIOA->CRL |= GPIO_CRL_CNF3_1;
    GPIOA->CRL &= ~GPIO_CRL_MODE3;
    GPIOA->CRL |= GPIO_CRL_MODE3_1;
​
    // TIM2, timer 2, channel 4
    TIM2->CR1 &= ~TIM_CR1_DIR;         // upcounting
    TIM2->CR1 &= ~TIM_CR1_CMS;         // edge-align mode
    TIM2->PSC = PRESCALER;             // 64
    TIM2->ARR = PERIOD(FREQ) - 1;      // 1 kHz
    TIM2->CCR4 = PERIOD(FREQ) / 2 - 1; // 50% by default
    TIM2->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P; // 4 channel, low level
    TIM2->BDTR |= TIM_BDTR_MOE;        // use as output
    TIM2->CCMR2 &= ~TIM_CCMR2_CC4S;    // output
    TIM2->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; // PWM1 mode
    TIM2->CR1 |= TIM_CR1_CEN;          // enable timer
}
void led_blink_exemple_1(uint32_t tick_delay)
{
	/****************************************************************/
	/*Программа моргания светодиодом каждые tick_delay тиков*/
	/****************************************************************/

		// Установить 1 на порт GPIOA пин 5
		GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_5;
		delay (tick_delay);
		// Сбросить состояние в 0 на порте GPIOA пин 
		GPIOA->BRR = GPIOA->BRR | GPIO_PIN_5;
		delay (tick_delay); 
}

void button_led_exemple_2(void)
{
		/****************************************************************/
	/*Включение сетодиода при нажатии кнопки*/
	/****************************************************************/
		// Считать состояние порта GPIOC пина 13

		pin_state = GPIOC->IDR & GPIO_PIN_13;
		
		if ( pin_state == 0 )
		{
			// Установить 1 на порт GPIOA пин 5
			GPIOA->BSRR = GPIOA->BSRR | GPIO_PIN_5;
			pin_state = 0;
		}
		else
		{
			// Сбросить состояние в 0 на порте GPIOA пин 
			GPIOA->BRR = GPIOA->BRR | GPIO_PIN_5;
		}
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
