#include <stdio.h>
#include <math.h>

// Функция проверки существования треугольника
int is_valid_triangle(double a, double b, double c)
{
    // Проверка: сумма двух сторон должна быть строго больше третьей
    if ((a + b > c) && (a + c > b) && (b + c > a))
    {
        return 1; // Валиден
    }
    return 0; // Не существует
}
// Функция вычисления площади треугольника по формуле Герона
// На вход ожидает периметр и стороны треугольника
double calc_triangle_area(double p, double a, double b, double c)
{
    double half_p = p / 2.0;
    return sqrt(half_p * (half_p - a) * (half_p - b) * (half_p - c));
}