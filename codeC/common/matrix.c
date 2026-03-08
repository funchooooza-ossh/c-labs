#ifndef MATRIX_C
#define MATRIX_C

#include "input.c"
#include <stdio.h>
#include "output.c"

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

#endif

char get_operation_char(const char *prompt)
{
    char op;
    while (1)
    {
        printf("%s", prompt);
        // Пробел перед %c игнорирует символы новой строки от предыдущих вводов
        if (scanf(" %c", &op) != 1)
        {
            clearBuffer();
            continue;
        }
        if (op == '+' || op == '-' || op == '*')
        {
            return op;
        }
        printf("Ошибка: недопустимая операция '%c'. Используйте +, - или *.\n", op);
        clearBuffer();
    }
}

double *add_double_matrices(int n, double *a, double *b)
{
    double *res = (double *)malloc(n * n * sizeof(double));
    if (!res)
        return NULL;
    for (int i = 0; i < n * n; i++)
    {
        res[i] = a[i] + b[i];
    }
    return res;
}

double *sub_double_matrices(int n, double *a, double *b)
{
    double *res = (double *)malloc(n * n * sizeof(double));
    if (!res)
        return NULL;
    for (int i = 0; i < n * n; i++)
    {
        res[i] = a[i] - b[i];
    }
    return res;
}

double *multiply_double_matrices(int n, double *a, double *b)
{
    double *res = (double *)calloc(n * n, sizeof(double)); // calloc сразу зануляет память
    if (!res)
        return NULL;

    for (int i = 0; i < n; i++)
    { // Строка первой
        for (int j = 0; j < n; j++)
        { // Столбец второй
            for (int k = 0; k < n; k++)
            { // Индекс суммирования
                res[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
    return res;
}

int *add_int_matrices(int n, int *a, int *b)
{
    int *res = (int *)malloc(n * n * sizeof(int));
    if (!res)
        return NULL;
    for (int i = 0; i < n * n; i++)
        res[i] = a[i] + b[i];
    return res;
}

int *sub_int_matrices(int n, int *a, int *b)
{
    int *res = (int *)malloc(n * n * sizeof(int));
    if (!res)
        return NULL;
    for (int i = 0; i < n * n; i++)
        res[i] = a[i] - b[i];
    return res;
}

int *multiply_int_matrices(int n, int *a, int *b)
{
    int *res = (int *)calloc(n * n, sizeof(int));
    if (!res)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                res[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
    return res;
}

void *dispatch_double(int n, double *a, double *b, char op)
{
    if (op == '+')
        return add_double_matrices(n, a, b);
    if (op == '-')
        return sub_double_matrices(n, a, b);
    if (op == '*')
        return multiply_double_matrices(n, a, b);
    return NULL;
}

void *dispatch_int(int n, int *a, int *b, char op)
{
    if (op == '+')
        return add_int_matrices(n, a, b);
    if (op == '-')
        return sub_int_matrices(n, a, b);
    if (op == '*')
        return multiply_int_matrices(n, a, b);
    return NULL;
}

#define calculate_matrices(n, a, b, op) _Generic((a), \
    double *: dispatch_double,                        \
    int *: dispatch_int)(n, a, b, op)
