#ifndef OUTPUT_C
#define OUTPUT_C

#include <stdio.h>

// func to printf pretty line
void printLine(int cols, int width)
{
    printf("   +");
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < width + 2; j++)
            printf("-");
        printf("+");
    }
    printf("\n");
}

void printInputClosed()
{
    printf("\nПоток ввода закрыт. Завершение программы...\n");
}

void printIntTypeError()
{
    printf("Ошибка! Введите целое число (int): ");
}

void printDoubleTypeError()
{
    printf("Ошибка! Введите число (double): ");
}

#define printTypeError(ptr) _Generic((ptr), \
    int *: printIntTypeError,               \
    double *: printDoubleTypeError)()

#endif