#include <stdio.h>
#include <math.h>

void calculateRoots(double a, double b, double c)
{
    double D = b * b - 4 * a * c;
    printf("\n--- Результат ---\n");
    printf("Дискриминант D = %.2lf\n", D);

    if (D > 0)
    {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        printf("Два вещественных корня:\nx1 = %.2lf\nx2 = %.2lf\n", x1, x2);
    }
    else if (D == 0)
    {
        double x = -b / (2 * a);
        printf("Один вещественный корень:\nx = %.2lf\n", x);
    }
    else
    {
        double realPart = -b / (2 * a);
        double imagPart = sqrt(-D) / (2 * a);
        printf("Корни комплексные (мнимые):\n");
        printf("x1 = %.2lf + %.2lfi\n", realPart, imagPart);
        printf("x2 = %.2lf - %.2lfi\n", realPart, imagPart);
    }
}

int main()
{
    double a, b, c;

    printf("Введите коэффициенты квадратного уравнения (a, b, c):\n");
    printf("a = ");
    if (scanf("%lf", &a) != 1)
        return 1;
    printf("b = ");
    if (scanf("%lf", &b) != 1)
        return 1;
    printf("c = ");
    if (scanf("%lf", &c) != 1)
        return 1;

    if (a == 0)
    {
        printf("Ошибка: при a=0 уравнение не является квадратным.\n");
    }
    else
    {
        calculateRoots(a, b, c);
    }

    return 0;
}