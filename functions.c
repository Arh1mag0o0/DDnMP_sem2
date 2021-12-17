
#include "functions.h"
uint16_t led_up = 0;        //для увеличения яркости
uint16_t led_down = 1000;   //для уменьшения яркости

void pwm_pin_output_14 (void)           //настройка TIM1 канала 4 на ПВМ выход                
{
    // Тактирование  GPIOA , TIM1, альтернативных функций порта
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;

	//делитель
	TIM1->PSC = 72;
	//значение перезагрузки
    TIM1->ARR = 1000;
	//коэф. заполнения
	TIM1->CCR4 = 1;
	//настроим на выход канал 4, активный уровень низкий 
	TIM1->CCER |= TIM_CCER_CC4E & ~TIM_CCER_CC4P;;

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
void pwm_pin_output_13 (void)           //настройка TIM1 канала 3 на ПВМ выход      
{
    // Тактирование  GPIOA , TIM1, альтернативных функций порта
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;
	//коэф. заполнения
	TIM1->CCR3 = 1;
    
	//настроим на выход канал 4, активный уровень низкий 
	TIM1->CCER |= TIM_CCER_CC3E & ~TIM_CCER_CC3P;;

	TIM1->BDTR |= TIM_BDTR_MOE;
	//PWM mode 1, прямой ШИМ 4 канал
    TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; 
	//считаем вверх
	TIM1->CR1 &= ~TIM_CR1_DIR;
	//выравнивание по фронту, Fast PWM
	TIM1->CR1 &= ~TIM_CR1_CMS;
	//включаем счётчик
	TIM1->CR1 |= TIM_CR1_CEN;  

}
void pwm_pin_output_12 (void)           //настройка TIM1 канала 2 на ПВМ выход
{
    // Тактирование  GPIOA , TIM1, альтернативных функций порта
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;

	//делитель
	TIM1->PSC = 72;
	//значение перезагрузки
    TIM1->ARR = 1000;
	//коэф. заполнения
	TIM1->CCR2 = 1;
    
	//настроим на выход канал 4, активный уровень низкий 
	TIM1->CCER |= TIM_CCER_CC2E & ~TIM_CCER_CC2P;

	TIM1->BDTR |= TIM_BDTR_MOE;
	//PWM mode 1, прямой ШИМ 4 канал
    TIM1->CCMR1 = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; 
	//считаем вверх
	TIM1->CR1 &= ~TIM_CR1_DIR;
	//выравнивание по фронту, Fast PWM
	TIM1->CR1 &= ~TIM_CR1_CMS;
	//включаем счётчик
	TIM1->CR1 |= TIM_CR1_CEN;  

}
void pwm_pin_output_11 (void)           //настройка TIM1 канала 1 на ПВМ выход
{
    // Тактирование  GPIOA , TIM1, альтернативных функций порта
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;

	//делитель
	TIM1->PSC = 72;
	
    //значение перезагрузки
    TIM1->ARR = 1000;
	
    //коэф. заполнения
	TIM1->CCR2 = 1;
    
	//настроим на выход канал 4, активный уровень низкий 
	TIM1->CCER |= TIM_CCER_CC1E & ~TIM_CCER_CC1P;
	TIM1->BDTR |= TIM_BDTR_MOE;
	
    //PWM mode 1, прямой ШИМ 4 канал
    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; 
	
    //считаем вверх
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
    //выравнивание по фронту, Fast PWM
	TIM1->CR1 &= ~TIM_CR1_CMS;
	
    //включаем счётчик
	TIM1->CR1 |= TIM_CR1_CEN;  

}

void gpiox_push_pull(int32_t portx, int32_t piny)       //установка на push_pull порта x пина y,  не доделанная (слишком много(однотипного) кода, можно проще реализовать)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN; //включение тактирования
    if (portx == 0xA) // для портов А, выставляет выбранный пин(1-15) на push_pull
    {
    if (piny == 0){
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL |= GPIO_CRL_CNF0_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE0;
	GPIOA->CRL	|= GPIO_CRL_MODE0_1; } 
    else
        if (piny == 1){
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_CNF1_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE1;
	GPIOA->CRL	|= GPIO_CRL_MODE1_1; } 
    else
        if (piny == 2){
    GPIOA->CRL &= ~GPIO_CRL_CNF2;
	GPIOA->CRL |= GPIO_CRL_CNF2_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE2;
	GPIOA->CRL	|= GPIO_CRL_MODE2_1; } 
    else
        if (piny == 3){
    GPIOA->CRL &= ~GPIO_CRL_CNF3;
	GPIOA->CRL |= GPIO_CRL_CNF3_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE3;
	GPIOA->CRL	|= GPIO_CRL_MODE3_1; } 
    else
        if (piny == 4){
    GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL |= GPIO_CRL_CNF4_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE4;
	GPIOA->CRL	|= GPIO_CRL_MODE4_1; } 
    else
        if (piny == 5){
    GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE5;
	GPIOA->CRL	|= GPIO_CRL_MODE5_1; } 
    else
        if (piny == 6){
    GPIOA->CRL &= ~GPIO_CRL_CNF6;
	GPIOA->CRL |= GPIO_CRL_CNF6_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE6;
	GPIOA->CRL	|= GPIO_CRL_MODE6_1; } 
    else
        if (piny == 7){
    GPIOA->CRL &= ~GPIO_CRL_CNF7;
	GPIOA->CRL |= GPIO_CRL_CNF7_1;

	GPIOA->CRL	&= ~GPIO_CRL_MODE7;
	GPIOA->CRL	|= GPIO_CRL_MODE7_1; }       
    else
        if (piny == 8){
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE8;
	GPIOA->CRH	|= GPIO_CRH_MODE8_1; }
     else
        if (piny == 9){
    GPIOA->CRH &= ~GPIO_CRH_CNF9;
	GPIOA->CRH |= GPIO_CRH_CNF9_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE9;
	GPIOA->CRH	|= GPIO_CRH_MODE9_1; }
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
        if (piny == 12){
    GPIOA->CRH &= ~GPIO_CRH_CNF12;
	GPIOA->CRH |= GPIO_CRH_CNF12_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE12;
	GPIOA->CRH	|= GPIO_CRH_MODE12_1; }
    else
        if (piny == 13){
    GPIOA->CRH &= ~GPIO_CRH_CNF13;
	GPIOA->CRH |= GPIO_CRH_CNF13_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE13;
	GPIOA->CRH	|= GPIO_CRH_MODE13_1; }
    else
        if (piny == 14){
    GPIOA->CRH &= ~GPIO_CRH_CNF14;
	GPIOA->CRH |= GPIO_CRH_CNF14_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE14;
	GPIOA->CRH	|= GPIO_CRH_MODE14_1; }
    else
        if (piny == 15){
    GPIOA->CRH &= ~GPIO_CRH_CNF15;
	GPIOA->CRH |= GPIO_CRH_CNF15_1;

	GPIOA->CRH	&= ~GPIO_CRH_MODE15;
	GPIOA->CRH	|= GPIO_CRH_MODE15_1; }
    }    
    else 
        if (portx == 0xB) // для портов B, выставляет выбранный пин(1-15) на push_pull
    {
    if (piny == 0){
    GPIOB->CRL &= ~GPIO_CRL_CNF0;
	GPIOB->CRL |= GPIO_CRL_CNF0_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE0;
	GPIOB->CRL	|= GPIO_CRL_MODE0_1; } 
    else
        if (piny == 1){
    GPIOB->CRL &= ~GPIO_CRL_CNF1;
	GPIOB->CRL |= GPIO_CRL_CNF1_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE1;
	GPIOB->CRL	|= GPIO_CRL_MODE1_1; } 
    else
        if (piny == 2){
    GPIOB->CRL &= ~GPIO_CRL_CNF2;
	GPIOB->CRL |= GPIO_CRL_CNF2_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE2;
	GPIOB->CRL	|= GPIO_CRL_MODE2_1; } 
    else
        if (piny == 3){
    GPIOB->CRL &= ~GPIO_CRL_CNF3;
	GPIOB->CRL |= GPIO_CRL_CNF3_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE3;
	GPIOB->CRL	|= GPIO_CRL_MODE3_1; } 
    else
        if (piny == 4){
    GPIOB->CRL &= ~GPIO_CRL_CNF4;
	GPIOB->CRL |= GPIO_CRL_CNF4_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE4;
	GPIOB->CRL	|= GPIO_CRL_MODE4_1; } 
    else
        if (piny == 5){
    GPIOB->CRL &= ~GPIO_CRL_CNF5;
	GPIOB->CRL |= GPIO_CRL_CNF5_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE5;
	GPIOB->CRL	|= GPIO_CRL_MODE5_1; } 
    else
        if (piny == 6){
    GPIOB->CRL &= ~GPIO_CRL_CNF6;
	GPIOB->CRL |= GPIO_CRL_CNF6_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE6;
	GPIOB->CRL	|= GPIO_CRL_MODE6_1; } 
    else
        if (piny == 7){
    GPIOB->CRL &= ~GPIO_CRL_CNF7;
	GPIOB->CRL |= GPIO_CRL_CNF7_1;

	GPIOB->CRL	&= ~GPIO_CRL_MODE7;
	GPIOB->CRL	|= GPIO_CRL_MODE7_1; }       
    else
        if (piny == 8){
    GPIOB->CRH &= ~GPIO_CRH_CNF8;
	GPIOB->CRH |= GPIO_CRH_CNF8_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE8;
	GPIOB->CRH	|= GPIO_CRH_MODE8_1; }
     else
        if (piny == 9){
    GPIOB->CRH &= ~GPIO_CRH_CNF9;
	GPIOB->CRH |= GPIO_CRH_CNF9_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE9;
	GPIOB->CRH	|= GPIO_CRH_MODE9_1; }
    else
        if (piny == 10){
    GPIOB->CRH &= ~GPIO_CRH_CNF10;
	GPIOB->CRH |= GPIO_CRH_CNF10_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE10;
	GPIOB->CRH	|= GPIO_CRH_MODE10_1; }
    else
        if (piny == 11){
    GPIOB->CRH &= ~GPIO_CRH_CNF11;
	GPIOB->CRH |= GPIO_CRH_CNF11_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE11;
	GPIOB->CRH	|= GPIO_CRH_MODE11_1; }
    else
        if (piny == 12){
    GPIOB->CRH &= ~GPIO_CRH_CNF12;
	GPIOB->CRH |= GPIO_CRH_CNF12_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE12;
	GPIOB->CRH	|= GPIO_CRH_MODE12_1; }
    else
        if (piny == 13){
    GPIOB->CRH &= ~GPIO_CRH_CNF13;
	GPIOB->CRH |= GPIO_CRH_CNF13_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE13;
	GPIOB->CRH	|= GPIO_CRH_MODE13_1; }
    else
        if (piny == 14){
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE14;
	GPIOB->CRH	|= GPIO_CRH_MODE14_1; }
    else
        if (piny == 15){
    GPIOB->CRH &= ~GPIO_CRH_CNF15;
	GPIOB->CRH |= GPIO_CRH_CNF15_1;

	GPIOB->CRH	&= ~GPIO_CRH_MODE15;
	GPIOB->CRH	|= GPIO_CRH_MODE15_1; }     
    }      
}
void TIM2_Init(void)                    //настройка таймера 2
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // тактирование таймера
    NVIC_EnableIRQ(TIM2_IRQn);          // глобальные прерывания (без них не работают локальные)
    TIM2->PSC = 3599;                   // делитель
    TIM2->ARR = 2000;                   // зачение до которого считать
}

void TIM2_IRQHandler(void)              //выполнение прерывания при переполнении таймера 2
{
    if (TIM2->SR & TIM_SR_UIF)          //если произошло обновление таймера
    {
        TIM2->SR &= ~(TIM_SR_UIF);      //сброс бита обновления
        while (led_up<1000)             //плавное загарание
            {
                TIM1->CCR4 = led_up;
                TIM1->CCR2 = led_up; 
                led_up = led_up+20; 
                break;
            }         
        if (led_up>995)
            {
                while (led_down>25)             //плавное затухание
                {
                    TIM1->CCR4 = led_down;
                    TIM1->CCR2 = led_down; 
                    led_down = led_down-20; 
                    break;
                }         
            }
        if (led_up>995 & led_down<25)   //сброс счетчиков загорания и затухания псоле первого цикла
            {
                led_up = 0;
                led_down = 1000;
            }    
            
    }
}

void stop_TIM2 (void)                   // остановка таймера 2
{
    TIM2->CR1 &= ~(TIM_CR1_CEN);
} 