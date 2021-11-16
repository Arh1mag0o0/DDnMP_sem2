
#include "main.h"
#include "functions.h"
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


int main(void)
{
	
	/****************************************************************/
	/*Инициализация порта A пина 5 на выход для моргания светодиодом*/
	/****************************************************************/
	
	/* Установка регистра CRL битов MODE5[1:0] на максимальную частоту 50 МHz */
	/* 
	Макроподстановки
	
	GPIO_CRL_MODE5_0 =       0b0000 0000 0001 0000 0000 0000 0000 0000
	GPIO_CRL_MODE5_1 =       0b0000 0000 0010 0000 0000 0000 0000 0000
	GPIO_CRL_CNF5_0 =        0b0000 0000 0100 0000 0000 0000 0000 0000
	GPIO_CRL_CNF5_1 =        0b0000 0000 1000 0000 0000 0000 0000 0000
	RCC_APB2ENR_IOPAEN_Msk = 0b0000 0000 0100 0000 0000 0000 0000 0100
	*/
		/*Включение тактирования для порта А*/
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN_Msk;
	
    GPIOA->CRL = (GPIOA->CRL) 
    | ( GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1) 
    | ( GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1) 
    | ( GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1) 
    | ( GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1)
    | ( GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1)
    | ( GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1)
    | ( GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1)
    | ( GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1);

	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
    GPIOA->CRL = (GPIOA->CRL) 
    & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF0_1))
    & ( ~( GPIO_CRL_CNF1_0 | GPIO_CRL_CNF1_1))
    & ( ~( GPIO_CRL_CNF2_0 | GPIO_CRL_CNF2_1))
    & ( ~( GPIO_CRL_CNF3_0 | GPIO_CRL_CNF3_1))
    & ( ~( GPIO_CRL_CNF4_0 | GPIO_CRL_CNF4_1))
    & ( ~( GPIO_CRL_CNF5_0 | GPIO_CRL_CNF5_1))
    & ( ~( GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1))
    & ( ~( GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1));
    
		RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPCEN_Msk;
        GPIOC->CRL = (GPIOC->CRL) 
    | ( GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1) 
    | ( GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1) 
    | ( GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1) 
    | ( GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1)
    | ( GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1)
    | ( GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1)
    | ( GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1)
    | ( GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1);

	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
    GPIOC->CRL = (GPIOC->CRL) 
    & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF0_1))
    & ( ~( GPIO_CRL_CNF1_0 | GPIO_CRL_CNF1_1))
    & ( ~( GPIO_CRL_CNF2_0 | GPIO_CRL_CNF2_1))
    & ( ~( GPIO_CRL_CNF3_0 | GPIO_CRL_CNF3_1))
    & ( ~( GPIO_CRL_CNF4_0 | GPIO_CRL_CNF4_1))
    & ( ~( GPIO_CRL_CNF5_0 | GPIO_CRL_CNF5_1))
    & ( ~( GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1))
    & ( ~( GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1));
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

//внешняя кнопка подключенная к пину 10
    GPIOC->CRH = (GPIOC->CRH) & ( ~( GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1));
	/* Установка регистра CRL битов CNF13[1:0] на тип входа pull-up */
	GPIOC->CRH = ((GPIOC->CRH) | ( GPIO_CRH_CNF11_0 | GPIO_CRH_MODE11_1));
	GPIOC->ODR = ((GPIOC->ODR) | ( GPIO_PIN_11)); 
   
	/*Инициализация прерываний для примера №3*/
	init_IT_for_exemple_3();
	
  while (1)
  {
		/******EXEMPLE_1*******/
	led_blink_exemple_1(800000);
		/******EXEMPLE_1*******/
		//button_led_exemple_2();
		/******EXEMPLE_1*******/
       // init_IT_for_exemple_3();
  }
}
