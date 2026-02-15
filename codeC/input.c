#include <stdio.h>
#include <stdlib.h>

// clean input buffer
void clearBuffer()
{
    int c;
    // Цикл остановится и на новой строке, и на конце файла
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// double input checker
double get_double(const char *prompt)
{
    double value;
    int status;

    printf("%s", prompt);
    while (1)
    {
        status = scanf("%lf", &value);

        if (status == 1)
        {
            // Успешный ввод
            return value;
        }

        if (status == EOF)
        {
            // Пользователь нажал Ctrl+D (закрыл поток)
            printf("\nПоток ввода закрыт. Завершение программы...\n");
            exit(1); // Или return -1, но exit надежнее
        }

        // Если status == 0 (введены буквы)
        printf("Ошибка! Введите число: ");
        clearBuffer();
    }
}

// int input checker
int get_int(const char *prompt)
{
    int value;
    int status;

    printf("%s", prompt);
    while (1)
    {
        status = scanf("%d", &value);

        if (status == 1)
        {
            // Успешный ввод
            return value;
        }

        if (status == EOF)
        {
            // Пользователь нажал Ctrl+D (закрыл поток)
            printf("\nПоток ввода закрыт. Завершение программы...\n");
            exit(1); // Или return -1, но exit надежнее
        }

        // Если status == 0 (введены буквы)
        printf("Ошибка! Введите целое число: ");
        clearBuffer();
    }
}