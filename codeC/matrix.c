#include <input.c>
#include <stdio.h>
#include <output.c>

void print_double(int r, int c, double *m)
// func to printf pretty double matrix
{
    printLine(c, 8);
    for (int i = 0; i < r; i++)
    {
        printf("   | ");
        for (int j = 0; j < c; j++)
        {
            printf("%8.2f | ", m[i * c + j]);
        }
        printf("\n");
        printLine(c, 8);
    }
}

void print_int(int r, int c, int *m)
// func to printf pretty int matrix
{
    printLine(c, 5);
    for (int i = 0; i < r; i++)
    {
        printf("   | ");
        for (int j = 0; j < c; j++)
        {
            printf("%5d | ", m[i * c + j]);
        }
        printf("\n");
        printLine(c, 5);
    }
}
// generic func to print int/double matrix
#define printMatrix(r, c, m) _Generic((m), \
    double *: print_double,                \
    int *: print_int)(r, c, (void *)m)

// fill double matrix func
void fill_double(int r, int c, double *m)
{
    char prompt[50]; // Буфер для текста приглашения
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            // Формируем строку вида "Matrix[0][1] (double) = "
            sprintf(prompt, "Matrix[%d][%d] (double) = ", i, j);
            m[i * c + j] = get_double(prompt);
        }
    }
}

// fill int matrix func
void fill_int(int r, int c, int *m)
{
    char prompt[50];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            sprintf(prompt, "Matrix[%d][%d] (int) = ", i, j);
            m[i * c + j] = get_int(prompt);
        }
    }
}
// generic func to fill int/double matrix
#define fillMatrix(r, c, m) _Generic((m), \
    double *: fill_double,                \
    int *: fill_int)(r, c, (void *)m)
