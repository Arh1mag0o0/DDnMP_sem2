#include <stdio.h>
#include <stdint.h>
#include "functions.h"


/* Задание:
сформировать 4 массива, найти в них число x. 
Все числа, стоящие после этого числа, переписать в другой массив.
*/

// инициализируем первичные массивы с числами для решения задания 
int32_t array_original_1 [] = {-1,2,-3,2546,20,50};
int32_t array_original_2 [] = {-1,2,-3,4,-5,6,7,22,9,-10,102,1025,1210,55,84,54,75,20,65};
int32_t array_original_3 [] = {-1,2,-3,4,-5,6,7,22,9,-10};
int32_t array_original_4 [] = {-1,2,-3,4,-5,6,7,22,9,-10};

// Объявляем выходные массивы для решения задания 
int32_t array_a1[sizeof(array_original_1)/sizeof(int32_t) ];
int32_t array_a2[sizeof(array_original_2)/sizeof(int32_t) ];
int32_t array_a3[sizeof(array_original_3)/sizeof(int32_t) ];
int32_t array_a4[sizeof(array_original_4)/sizeof(int32_t) ];

int32_t arrayc1[sizeof(array_original_1)/sizeof(int32_t) ];
int32_t arrayc2[sizeof(array_original_2)/sizeof(int32_t) ];
int32_t arrayc3[sizeof(array_original_3)/sizeof(int32_t) ];
int32_t arrayc4[sizeof(array_original_4)/sizeof(int32_t) ];
// Основная программа
int main ()
{    
    // объявляем элемент, который будем искать в массиве, для каждого массива можно выбирать любое число
int32_t x = 20;

    // вызываем функцию, которая выполняет задание на ассемблере
    lab_asm(array_original_1,
sizeof(array_original_1)/sizeof(int32_t), array_a1, x);
    
    // поменяем искомый эллемент
    x = 75;
    lab_asm(array_original_2,
sizeof(array_original_2)/sizeof(int32_t), array_a2, x);
    
    x = 22;
    lab_asm(array_original_3,
sizeof(array_original_3)/sizeof(int32_t), array_a3, x);
    
    lab_asm(array_original_4,
sizeof(array_original_4)/sizeof(int32_t), array_a4, x);
  
    x = -3;
    // вызываем функцию, которая выполняет задание на Си
    ableev_lab_c(array_original_1, sizeof(array_original_1)/sizeof(int32_t), x, arrayc1);
    
    x = 75;
    ableev_lab_c(array_original_2, sizeof(array_original_2)/sizeof(int32_t), x, arrayc2);
    
    ableev_lab_c(array_original_3, sizeof(array_original_3)/sizeof(int32_t), x, arrayc3);
    
    x = 2;
    ableev_lab_c(array_original_4, sizeof(array_original_4)/sizeof(int32_t), x, arrayc4);
    
return 0;
}
