#include <stdio.h>
#include <stdint.h>


//Экспортируем функцию из main.s написанную на ассемблере.
extern void array_write_asm (int32_t* array_ptr, size_t array_size, int32_t* new_array_ptr );


/*
Common function
*/
void ableev_lab (int32_t arr, size_t size,int32_t n,int out[]);

/*
int b - номер элемента после которого записывать
int arr[] 
int out[] 
*/
uint8_t fun (int32_t arr[], size_t size, int32_t n);

/*
int b - номер элемента после которого записывать
int arr[] 
int out[] 
*/
void write(int b , int arr[], int out[]);

	

//подпрограмма search_22 поиска числа 22, возвращаяет номер первого эллемента входного массива стоящего после 22
int search_22 (int arr[]){
//в 'a' храниться очередной эллемент входного массива
    int a = arr[0];     
//обявляем цикл, который будет находить число 22, путем сравнения каждого эллемента массива с числом 22
            int i = 1;
			for (;i<10 ; i++){
                if (a == 22) 
                    break;    
                    
                else    {
                    a = arr[i];
                    }
    }
    return (i);  
   }   
//подпрограмма write выполняет запись эллементов массива стоящих после 22	
//Принимает номер эллемента входного массива стоящего после 22 (b), входной массив (arr), выходной массив (out)   
void write(int b , int arr[], int out[]) {
/*     
В 'f' будем хранить номера элементов выходного массива, 
используем цикл пока эллемент входного массива не 10(т.е. не превышает номер последнего элемента (9)),
записывать его в выходной массив
*/ 
    int f = 0;
    while (b < 10){	
        out[f] = arr[b];
        f = f + 1;
				b = b + 1;
    }
}