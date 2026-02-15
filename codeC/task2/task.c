#include <stdio.h>
#include <matrix.c>

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