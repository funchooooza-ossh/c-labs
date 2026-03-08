#include "matrix.c"
#include "input.c"
#include <stdio.h>

int main()
{
    int n = get_positive_int(
        "Введите желаемую размерность квадратной матринцы(int):\n");

    char op = get_operation_char("Введите операцию (+, -, *): ");
    double *matA = (double *)malloc(n * n * sizeof(double));
    double *matB = (double *)malloc(n * n * sizeof(double));

    if (matA == NULL || matB == NULL)
    {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
    }

    printf("Введите элементы матрицы А:\n");
    fillMatrix(n, n, matA);
    printf("Введите элементы матрицы В:\n");
    fillMatrix(n, n, matB);

    printf("\nПолученная матрица A %dx%d:\n", n, n);
    printMatrix(n, n, matA);

    printf("\nПолученная матрица B %dx%d:\n", n, n);
    printMatrix(n, n, matB);

    double *result = (double *)calculate_matrices(n, matA, matB, op);

    printf("\nИтоговая матрица %dx%d:\n", n, n);
    printMatrix(n, n, result);

    free(matA);
    free(matB);
    free(result);

    return 0;
}