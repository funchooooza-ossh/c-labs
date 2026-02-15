#include <stdio.h>
#include <math.h>
#include <input.c>

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

    printf("Введите коэффициенты квадратного уравнения (a, b, c):\n");
    double a = get_double("a = ");
    double b = get_double("b = ");
    double c = get_double("c = ");

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