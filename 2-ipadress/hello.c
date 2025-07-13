#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void foo1();
void foo2();
void foo3();
void fooHomeWork();

int main() {
/*  foo1();
  foo2();
  foo3();*/
  fooHomeWork();

//  printf("Hello world");
}

uint8_t ui8 = 0xFF;
uint16_t ui16 = 0xEEEE;
uint32_t ui32 = 0xDDDDDDDD;

int8_t i8 = 0x7F;
int16_t i16 = 0x7EEE;
int32_t i32 = 0x7DDDDDDD;

// 1. Хранение целочисленных типов в памяти
// Привычная нам форма - big-endian
//  (он же прямой порядок байтов или сетевой порядок байтов)
// В архитектурах x86 и производных, RISC-V, а также болшьшинстве ARM
// используется little-endian (обратный порядок байтов)
// Шестнадцатиричное число 12 34 56 78 хранится в памяти x86: 78 56 34 12
void foo1() {
  ui8 = 0x12;
  ui16 = 0x3456;
  ui32 = 0x789ABCDE;
}

// 2. Преобразование целочисленных типов
// uint8_t  -> uint16_t
// 0x12     -> 0x0012
//
// uint16_t -> uint8_t
// 0x1234   -> 0x34
void foo2() {
  // Увеличиваем размерность
  ui16 = (uint16_t)ui8;
  printf("Преобразуем uint8_t %#x в uint16_t. Результат: %#x\n", ui8, ui16);

  // Уменьшаем размерность (теряем старшую часть)
  ui16 = 0x1234;
  ui8 = (uint8_t)ui16;
  printf("Преобразуем uint16_t %#x в uint8_t. Результат: %#x\n", ui16, ui8);
  ui32 = 0x12345678;
  ui16 = (uint16_t)ui32;
  printf("Преобразуем uint32_t %#x в uint16_t. Результат: %#x\n", ui32, ui16);
  /****************************************************************************/
  // Преобразование знакового-безнакового
  // Старший бит определяет знак
  // двоичное однобайтное 1xxx xxxx - отрицательное, 0xxx xxxx - положительное
  // 0x80 (16) - 1000 0000 (2)
  // Аналогично для двубайтных и выше
  // 0x8000 (16) - 1000 0000 0000 0000 (2)
  // 0x80000000 (16) - 1000 0000 0000 0000 0000 0000 0000 0000 (2)

  // Увеличиваем размерность
  i16 = (int16_t)i8; // 0x7F
  printf("Преобразуем int8_t %#x в int16_t. Результат: %#x\n", i8, i16);
  // Уменьшаем размерность (теряем старшую часть, включающую информацию о знаке)
  i16 = 0x7EEE;
  i8 = (int8_t)i16;
  // Примечание: В этой строке для вывода я дополнительно преобразую int8_t
  // в однобайтное число. int8_t - это, фактически, char, а он функцией printf
  // либо выводится как символ, либо преобразуется к четырехбайтному int
  printf("Преобразуем int16_t %#x в int8_t. Результат: %#x\n", i16, (uint8_t)i8);
  // Преобразуем знаковое в безнаковое
  i16 = 0x7EEE;
  ui16 = (uint16_t)i16;
  printf("Преобразуем int16_t %#x в uint16_t. Результат: %#x\n", i16, ui16);
  // и обратно
  i16 = (int16_t)ui16;
  printf("Преобразуем uint16_t %#x в int16_t. Результат: %#x\n", ui16, i16);
}

// 3. Массивы
void foo3() {
  uint8_t undefBeh[5];
  for (size_t n = 0; n < sizeof undefBeh; n++)
    undefBeh[n] = n + 100;
  uint8_t arr1[5] = { 0, 1, 2, 3, 4 };
  // Такое присвоение допускается только на этапе инициализации
  // если сейчас мы напишем
  // arr1 = { 0, 1, 2, 3, 4 };
  // это не сработает
  size_t l1 = sizeof arr1;
  // Если размер не задан, то определяется количеством элементов,
  // заданных при инициализации
  uint8_t arr1_[] = { 0, 1, 2, 3, 4 };
  size_t l2 = sizeof arr1_;
  // Если задано элементов меньше, чем размер, остаток инициализируется нулями
  uint8_t arr2[5] = { 0, 1, 2, };
  uint8_t arr3[5] = {};

  // Адреса
  // Создаем массив и инициализируем нулями
  uint32_t arr4[5] = {};
  // Задаем один элемент
  arr4[2] = 0x12345678;

  // Это адреса начала массива
  uint32_t* arr4_addr = arr4;
  uint32_t* arr4_addr0 = &arr4[0]; // & - получение адреса значения

  // Это адреса элемента 2
  uint32_t* arr4_addr2_ = &arr4[2];
  uint32_t* arr4_addr2 = arr4 + 2;

  // Учимся "стрелять в ногу"
  /*************************************/
  // Что за адрес окажется в what_is_it?
  uint32_t* what_is_it = &arr4_addr2[-2];
  /*************************************/
  uint8_t* shot = (uint8_t*)arr4_addr2 + 2;
  uint32_t* shot2 = (uint32_t*)shot;
  uint32_t shot2_val = *shot2; // * - получение значения по адресу

  printf("Hello world");
}

// Домашнее задание
bool convertAddr(const char* ipAddr, uint8_t out[4]);

void fooHomeWork() {
  // Таблица ASCII
  // https://upload.wikimedia.org/wikipedia/commons/1/1b/ASCII-Table-wide.svg

  // Задан массив симоволов (строка)
  char ipAddr[] = "192.168.10.18";
  // char ipAddr[] = "192.168.XXX.100";
  // char ipAddr[] = "Scientia potentia est";

  // Проверить правильность введеной последовательности и
  // преобразовать в массив байтов, где каждый байт - октет (элемент) адреса
  // return false - преобразование не удалось
  uint8_t out[4];
  bool res = convertAddr(ipAddr, out);
  if (res)
    printf("%i.%i.%i.%i\n", out[0], out[1], out[2], out[3]);
}

bool convertAddr(const char* ipAddr, uint8_t out[4]) {
    size_t length = strlen(ipAddr); 
    uint8_t bytes[length];
    for (size_t i = 0; i < length; i++) {
        bytes[i] = (uint8_t)ipAddr[i]; // Явное приведение к uint8_t
    }
    int pos=0;
    int dots=0;
    int octNum=0;
    char octet[100]="";
    for (size_t i = 0; i <= length; i++) {
      char symbol = (char)bytes[i];

      if  (bytes[i]==0x30 &&  i==0)
      {
        printf("%s","IP адрес не может начинаться с нуля");
        return false;
      }
      if  (bytes[i]==0x30)
      {
        if  (bytes[i+1]!=46)
        {
          printf("%s","Октет не может начинаться с нуля");
          return false;
        }
      }
      
      if  (bytes[i]==46 &&  pos==0)
      {
        printf("%s","Октет не может начинаться с точки");
        return false;
      }
      

      if  (bytes[i]==46 || i==length)
      {        
        //*out = octet;
        pos=0;
        int i=atoi(octet);
        if(i>256)
        {
          printf("%s", "октет не может быть больше 255");
          return false;
        }
           printf("%i\n",i);
        out[octNum] = (uint8_t)i;
        octNum++;
        continue;
      }
      else
      {
        
        octet[pos]=(char)bytes[i];
        pos++;
        octet[pos]='\0';
      }   
      if  (bytes[i]!=46)
      {
        if  (bytes[i]<48 || bytes[i]>57)
        {
          printf("%s","Такого символа в адресе быть не может");
          return false;
        }

      }

          
    }
  printf("%s - %s", ipAddr, "IP адрес валиден\n");
  return true;
}
