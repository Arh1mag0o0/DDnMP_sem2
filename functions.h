#include <stdio.h>
#include <stdint.h>
#include "functions.c"

/*Экспортируем функцию из main.s написанную на ассемблере, которая выполняет задание.
array_ptr - входной массив
arrray_size - размер входного массива
new_array_ptr - выходной массив
x - искомое число
*/
extern void lab_asm (int32_t* array_ptr, size_t array_size, int32_t* new_array_ptr, int32_t x );

/*функция, которая выполняет задание на языке си
arr[] - входной массив
size - размер входного массива
n - искомое число 
out[] - выходной массив
*/
void ableev_lab_c(int32_t arr[], size_t size, int32_t n, int32_t out[]) {

    // в переменную 'b' будет возвращяться номер эллемента стоящего после искомого числа   
int b;
    b = search_x(arr, size, n);
    write (arr, size, out, b);
}




	

