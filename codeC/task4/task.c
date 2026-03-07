#include "input.c"
#include "triangle.c"
#include <stdio.h>

int main()
{
    double a, b, c;
    while (1)
    {
        a = get_positive_double("Введите размер первой стороны(double):\n");
        b = get_positive_double("Введите размер второй стороны(double):\n");
        c = get_positive_double("Введите размер третьей стороны(double):\n");

        if (is_valid_triangle(a, b, c) == 1)
        {
            break;
        }
        else
        {
            printf("Треугольник со сторонами: %.2lf, %.2lf, %.2lf не может существовать\n", a, b, c);
        }
    }
    double p = a + b + c;
    double area = calc_triangle_area(p, a, b, c);

    printf("Периметр треугольника(%.2lf, %.2lf, %.2lf): %.2lf\n", a, b, c, p);
    printf("Площадь треугольника(%.2lf, %.2lf, %.2lf): %.2lf\n", a, b, c, area);

    return 0;
}