#include <stdio.h>

void printLine(int cols, int width)
// func to printf pretty line
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

// clean input buffer
void clearBuffer()
{
    while (getchar() != '\n')
        ;
}

// fill double matrix func
void fill_double(int r, int c, double *m)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("Matrix[%d][%d] (double) = ", i, j);
            // m[i * c + j] — это ручная эмуляция двумерного массива
            while (scanf("%lf", &m[i * c + j]) != 1)
            {
                printf("Ошибка! Введите число: ");
                clearBuffer();
            }
        }
    }
}

// fill int matrix func
void fill_int(int r, int c, int *m)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("Matrix[%d][%d] (int) = ", i, j);
            while (scanf("%d", &m[i * c + j]) != 1)
            {
                printf("Ошибка! Введите целое число: ");
                clearBuffer();
            }
        }
    }
}
// generic func to fill int/double matrix
#define fillMatrix(r, c, m) _Generic((m), \
    double *: fill_double,                \
    int *: fill_int)(r, c, (void *)m)

int main()
{
    // 1. Double matrix
    double matA[3][3];
    fillMatrix(3, 3, &matA[0][0]);
    printf("\nПолученная матрица 3x3:\n");
    printMatrix(3, 3, &matA[0][0]);

    double mainSum = 0, sideSum = 0;
    for (int i = 0; i < 3; i++)
    {
        mainSum += matA[i][i];
        sideSum += matA[i][3 - 1 - i];
    }
    printf("Суммы: главная = %.2f, побочная = %.2f\n\n", mainSum, sideSum);

    // 2. Int matrix
    int matB[2][2], resB[2][2];
    fillMatrix(2, 2, &matB[0][0]);
    printf("\nПолученная матрица 2x2:\n");
    printMatrix(2, 2, &matB[0][0]);

    // Квадрат матрицы
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            resB[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                resB[i][j] += matB[i][k] * matB[k][j];
            }
        }
    }

    printf("\nРЕЗУЛЬТАТ ВОЗВЕДЕНИЯ МАТРИЦЫ В КВАДРАТ:\n");
    printMatrix(2, 2, &resB[0][0]);

    return 0;
}