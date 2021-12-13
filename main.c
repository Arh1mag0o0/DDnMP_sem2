
#include <stm32f10x.h>

#define PERIOD(f)       (1e6 / f)
#define PRESCALER       (SystemCoreClock / 1e6)
#define FREQ            1000

void RCC_DeInit (void)
{
    RCC->CR |= RCC_CR_HSION;
    while (RCC_CR_HSIRDY == RESET ){}
    RCC->CR |= (RCC_CR_HSITRIM == 0x80U);
    RCC->CFGR = 0;
    while (RCC_CFGR_SWS != RESET){}
    RCC->CR |= ~RCC_CR_PLLON;
    while (RCC_CR_PLLRDY != RESET) {}
    RCC->CR |= ~RCC_CR_HSEON | ~RCC_CR_CSSON;
    while (RCC_CR_HSERDY != RESET){}
    RCC->CR |= ~RCC_CR_HSEBYP;
    RCC->CSR |= RCC_CSR_RMVF;
}
void led_pwm_init(void) {
    uint32_t tmpcr1, tmpcr2, tmpccer, tmpccmr2;

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //включение тактирования таймера TIM2 
    
    // сбрасиваем значения битов 
    TIM2->CR1 &= ~TIM_CR1_DIR; // Бит 4 (DIR) задает направление счета: прямой или реверсивный (0 или 1).
    TIM2->CR1 &= ~TIM_CR1_CMS; //Биты 6-5  (CMS) определяют режим для двунаправленного счета (01-11) или разрешают счет только в одном направлении (00).
    TIM2->CR1 &= ~TIM_CR1_CKD; //Биты 9-8 (CKD) задают значение делителя частоты для внутренних нужд таймера.
    
    TIM2->ARR = 65535;  // Регистр перезагрузки, после того как досчитает до числа.
    TIM2->PSC = 0;      // Регистр предделителя.
    
    TIM2->EGR |= TIM_EGR_UG; // бит 0 (UG) – генерация перезагрузки. Производится записью в него 1. Сбрасывается аппаратно. 
    TIM2->CR1 &= ~TIM_CR1_ARPE; // Бит 7 (ARPE) определяет режим записи в регистр перезагрузки: буферизирован или нет. 
    TIM2->SMCR &= ~TIM_SMCR_SMS; // 3 бита (SMS). Для того чтобы задать тактирование таймера от шины APB, надо записать в них нули.  
    TIM2->SMCR &= ~TIM_SMCR_ECE; //включение тактирования
    
    TIM2->CCMR2 |= TIM_CCMR2_OC4CE | TIM_CCMR2_OC3CE; //включение предделителя на каналы 3 и 4.
    TIM2->CCER &= (~TIM_CCER_CC4E & ~TIM_CCER_CC3E); // Отключили каналы для безболезненной настройки.
    
    TIM2->CCMR2 &= ~TIM_CCMR2_CC4S & ~TIM_CCMR2_CC3S; //Очистим в каналах биты, отвечающие за захват/сравнение
    TIM2->CCMR2 = (TIM2->CCMR2) | (TIM_CCMR2_OC4M | TIM_CCMR2_OC3M) 
    | (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1) | (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1); // включение выходов каналов.
    TIM2->CCER &= ~TIM_CCER_CC4P & ~TIM_CCER_CC3P & ~TIM_CCER_CC1P & ~TIM_CCER_CC2P; // полярность каналов
    TIM2->CCER &= ~TIM_CCER_CC4E & ~TIM_CCER_CC3E & ~TIM_CCER_CC1E & ~TIM_CCER_CC2E; // активация ножек каналов
   
   // обнулил регистры сравнения, коэффициент запонения стал равен 0
    TIM2->CCR1 = 10000;
    TIM2->CCR3 = 0;
    TIM2->CCR4 = 0;
    
    TIM2->CCMR2 &= ~TIM_CCMR2_OC4FE & ~TIM_CCMR2_OC3FE; //отключили режим Fast сравнения
    TIM2->CR2 &= ~TIM_CR2_MMS; //отключение мастер-режим таймера
    TIM2->SMCR &= ~TIM_SMCR_MSM; // отключение режима Master/Slave
    
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    GPIOA->CRL = (GPIOA->CRL) 
    | ( GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1) 
    | ( GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1) 
    | ( GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1)
    | ( GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1);
    AFIO_EVCR_PORT_PA;

	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
    GPIOA->CRL = (GPIOA->CRL) 
    & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF0_1))
    & ( ~( GPIO_CRL_CNF1_0 | GPIO_CRL_CNF1_1))
    & ( ~( GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1))
    & ( ~( GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1));
       GPIOB->CRL = (GPIOB->CRL) 
    | ( GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1) 
    | ( GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1) 
    | ( GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1)
    | ( GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1);
    AFIO_EVCR_PORT_PB;

	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
    GPIOB->CRL = (GPIOB->CRL) 
    & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF0_1))
    & ( ~( GPIO_CRL_CNF1_0 | GPIO_CRL_CNF1_1))
    & ( ~( GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1))
    & ( ~( GPIO_CRH_CNF11_0 | GPIO_CRH_CNF11_1));
    
         GPIOC->CRL = (GPIOC->CRL) 
    | ( GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1) 
    | ( GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1) 
    | ( GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1)
    | ( GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1);
    AFIO_EVCR_PORT_PC;

	/* Установка регистра CRL битов CNF5[1:0] на тип выхода push-pull */
    GPIOC->CRL = (GPIOC->CRL) 
    & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF0_1))
    & ( ~( GPIO_CRL_CNF1_0 | GPIO_CRL_CNF1_1))
    & ( ~( GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1))
    & ( ~( GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1));
    
}

int main(void) {
    RCC_DeInit;
    led_pwm_init();
    TIM2->CCER |= TIM_CCER_CC4E | TIM_CCER_CC3E; // включение каналов
    TIM2->CR1 |= TIM_CR1_CEN; //запуск таймера
    
    while(1) {
        for (uint32_t i = 0; i < 262144; i++) 
        {
            if(i<65536)  
                TIM2->CCR3 = i;
            else if ((i>65535)&&(i<131072)) 
                TIM2->CCR3 = 131071-i;
            else if((i>131071)&&(i<196608)) 
                TIM2->CCR4 = i-131072;
            else if ((i>196607)&&(i<262144))  
                TIM2->CCR4 = 262143-i;
        }
    }
}