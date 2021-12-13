
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

uint32_t pin_state = 0;

void pwm_pin_output_14 (void)
{
  // Тактирование  GPIOA , TIM1, альтернативных функций порта
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;

	//делитель
	TIM1->PSC = 72;
	//значение перезагрузки
        TIM1->ARR = 1000;
	//коэф. заполнения
	TIM1->CCR4 = 100;

	//настроим на выход канал 4, активный уровень низкий 
	TIM1->CCER |= TIM_CCER_CC4E & ~TIM_CCER_CC4P;

	TIM1->BDTR |= TIM_BDTR_MOE;
	//PWM mode 1, прямой ШИМ 4 канал
    TIM1->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; 

	//считаем вверх
	TIM1->CR1 &= ~TIM_CR1_DIR;
	//выравнивание по фронту, Fast PWM
	TIM1->CR1 &= ~TIM_CR1_CMS;
	//включаем счётчик
	TIM1->CR1 |= TIM_CR1_CEN;  

}


void tim_pwm (void) //попытка настроить таймер на генерацию шим
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //включение тактирования таймера TIM2 
    
    //настройска CR1, SMCR, EGR, CR2< CCER, CCMR1, CCMR2
    TIM2->CR1 &= (~TIM_CR1_CKD & ~TIM_CR1_DIR & ~TIM_CR1_ARPE & ~TIM_CR1_CMS);
    TIM2->SMCR &= ((~TIM_SMCR_ECE & ~TIM_SMCR_SMS & ~TIM_SMCR_MSM)| TIM_SMCR_ETP);
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->CR2 &= ~TIM_CR2_MMS;
    TIM2->CCER &= (~TIM_CCER_CC1E & ~TIM_CCER_CC2E & ~TIM_CCER_CC3E & ~TIM_CCER_CC4E);
    TIM2->CCMR1 &= (~TIM_CCMR1_CC1S & ~TIM_CCMR1_CC2S & ~TIM_CCMR1_OC1FE & ~TIM_CCMR1_OC2FE) | TIM_CCMR1_OC1CE | TIM_CCMR1_OC2CE | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    TIM2->CCMR2 &= (~TIM_CCMR2_CC3S & ~TIM_CCMR2_CC4S & ~TIM_CCMR2_OC3FE & ~TIM_CCMR2_OC4FE) | TIM_CCMR2_OC3CE | TIM_CCMR2_OC4CE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC3M_2;
    TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
    TIM2->ARR = 65535;
    TIM2->PSC = 1;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL |= GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRH_CNF15_0 | GPIO_CRL_MODE0_0  | GPIO_CRL_MODE1_0 | GPIO_CRH_MODE15_0 | GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRH_CNF15_1 | GPIO_CRL_MODE0_1  | GPIO_CRL_MODE1_1 | GPIO_CRH_MODE15_1;
    TIM2->BDTR |= TIM_BDTR_MOE;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void gpiox_push_pull(int32_t portx, int32_t piny)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
    if (portx == 0xA)
    {
    if (piny == 0)
        GPIOA->CRL &= (~GPIO_CRL_CNF0 & ~GPIO_CRL_MODE0) | (GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_1);
    else
        if (piny == 1)
            GPIOA->CRL &= (~GPIO_CRL_CNF1 & ~GPIO_CRL_MODE1) | (GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_1);
    else
        if (piny == 2)
            GPIOA->CRL &= (~GPIO_CRL_CNF2 & ~GPIO_CRL_MODE2) | (GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_1);
    else
        if (piny == 3)
            GPIOA->CRL &= (~GPIO_CRL_CNF3 & ~GPIO_CRL_MODE3) | (GPIO_CRL_CNF3_1 | GPIO_CRL_MODE3_1);
    else
        if (piny == 4)
            GPIOA->CRL &= (~GPIO_CRL_CNF4 & ~GPIO_CRL_MODE4) | (GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4_1);
    else
        if (piny == 5)
            GPIOA->CRL &= (~GPIO_CRL_CNF5 & ~GPIO_CRL_MODE5) | (GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_1);
    else
        if (piny == 6)
            GPIOA->CRL &= (~GPIO_CRL_CNF6 & ~GPIO_CRL_MODE6) | (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1);
    else
        if (piny == 7)
            GPIOA->CRL &= (~GPIO_CRL_CNF7 & ~GPIO_CRL_MODE7) | (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1);        
    else
        if (piny == 8){
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE8;
	GPIOA->CRH	|= GPIO_CRH_MODE8_1; }
     else
        if (piny == 9)
            GPIOA->CRH &= (~GPIO_CRH_CNF9 & ~GPIO_CRH_MODE9) | (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1); 
    else
        if (piny == 10){
    GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE10;
	GPIOA->CRH	|= GPIO_CRH_MODE10_1; }
    else
        if (piny == 11){
    GPIOA->CRH &= ~GPIO_CRH_CNF11;
	GPIOA->CRH |= GPIO_CRH_CNF11_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE11;
	GPIOA->CRH	|= GPIO_CRH_MODE11_1; }
    else
        if (piny == 12)
            GPIOA->CRH &= (~GPIO_CRH_CNF12 & ~GPIO_CRH_MODE12) | (GPIO_CRH_CNF12_1 | GPIO_CRH_MODE12_1); 
    else
        if (piny == 13)
            GPIOA->CRH &= (~GPIO_CRH_CNF13 & ~GPIO_CRH_MODE13) | (GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_1); 
    else
        if (piny == 14)
            GPIOA->CRH &= (~GPIO_CRH_CNF14 & ~GPIO_CRH_MODE14) | (GPIO_CRH_CNF14_1 | GPIO_CRH_MODE14_1); 
    else
        if (piny == 15)
            GPIOA->CRH &= (~GPIO_CRH_CNF15 & ~GPIO_CRH_MODE15) | (GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15_1);      
    }    
    else 
        if (portx == 0xB)
    {
    if (piny == 0)
        GPIOB->CRL &= (~GPIO_CRL_CNF0 & ~GPIO_CRL_MODE0) | (GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_1);
    else
        if (piny == 1)
            GPIOB->CRL &= (~GPIO_CRL_CNF1 & ~GPIO_CRL_MODE1) | (GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_1);
    else
        if (piny == 2)
            GPIOB->CRL &= (~GPIO_CRL_CNF2 & ~GPIO_CRL_MODE2) | (GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_1);
    else
        if (piny == 3)
            GPIOB->CRL &= (~GPIO_CRL_CNF3 & ~GPIO_CRL_MODE3) | (GPIO_CRL_CNF3_1 | GPIO_CRL_MODE3_1);
    else
        if (piny == 4)
            GPIOB->CRL &= (~GPIO_CRL_CNF4 & ~GPIO_CRL_MODE4) | (GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4_1);
    else
        if (piny == 5)
            GPIOB->CRL &= (~GPIO_CRL_CNF5 & ~GPIO_CRL_MODE5) | (GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_1);
    else
        if (piny == 6)
            GPIOB->CRL &= (~GPIO_CRL_CNF6 & ~GPIO_CRL_MODE6) | (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1);
    else
        if (piny == 7)
            GPIOB->CRL &= (~GPIO_CRL_CNF7 & ~GPIO_CRL_MODE7) | (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1);        
    else
        if (piny == 8)
            GPIOB->CRH &= (~GPIO_CRH_CNF8 & ~GPIO_CRH_MODE8) | (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1);          
     else
        if (piny == 9)
            GPIOB->CRH &= (~GPIO_CRH_CNF9 & ~GPIO_CRH_MODE9) | (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1); 
    else
        if (piny == 10)
            GPIOB->CRH &= (~GPIO_CRH_CNF10 & ~GPIO_CRH_MODE10) | (GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10_1); 
    else
        if (piny == 11)
            GPIOB->CRH &= (~GPIO_CRH_CNF11 & ~GPIO_CRH_MODE11) | (GPIO_CRH_CNF11_1 | GPIO_CRH_MODE11_1); 
    else
        if (piny == 12)
            GPIOB->CRH &= (~GPIO_CRH_CNF12 & ~GPIO_CRH_MODE12) | (GPIO_CRH_CNF12_1 | GPIO_CRH_MODE12_1); 
    else
        if (piny == 13)
            GPIOB->CRH &= (~GPIO_CRH_CNF13 & ~GPIO_CRH_MODE13) | (GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_1); 
    else
        if (piny == 14)
            GPIOB->CRH &= (~GPIO_CRH_CNF14 & ~GPIO_CRH_MODE14) | (GPIO_CRH_CNF14_1 | GPIO_CRH_MODE14_1); 
    else
        if (piny == 15)
            GPIOB->CRH &= (~GPIO_CRH_CNF15 & ~GPIO_CRH_MODE15) | (GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15_1);      
    }      
}

void delay (uint32_t ticks)
{
	for (uint32_t i = 0; i < ticks; i++)
	{
	}
}


