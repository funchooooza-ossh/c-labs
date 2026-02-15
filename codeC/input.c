#include <stdio.h>
#include <stdlib.h>
#include <output.c>
#include <limits.h>
#include <math.h>
#include <string.h>

// clean input buffer
void clearBuffer()
{
    int c;
    // Цикл остановится и на новой строке, и на конце файла
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// string input checker
char *get_string(const char *prompt, int size)
{
    int capacity = (size > 0) ? (size + 1) : 16; // Начальная емкость
    int length = 0;
    char *buffer = (char *)malloc(capacity * sizeof(char));

    if (!buffer)
    {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
    }

    printf("%s", prompt);

    while (1)
    {
        int c = getchar();

        // 1. Обработка EOF (Ctrl+D)
        if (c == EOF)
        {
            if (length == 0)
            {
                // Если поток закрылся сразу - выходим как в get_int
                free(buffer);
                printInputClosed();
                exit(1);
            }
            // Если текст был, а потом EOF - завершаем строку
            break;
        }

        // 2. Обработка конца строки (Enter)
        if (c == '\n')
        {
            break;
        }

        // 3. Логика наполнения буфера
        if (size == -1)
        {
            // ДИНАМИЧЕСКИЙ РЕЖИМ (без ограничений)
            if (length + 1 >= capacity)
            {
                capacity *= 2;
                char *new_buffer = (char *)realloc(buffer, capacity);
                if (!new_buffer)
                {
                    free(buffer);
                    exit(1);
                }
                buffer = new_buffer;
            }
            buffer[length++] = (char)c;
        }
        else
        {
            // РЕЖИМ С ОГРАНИЧЕНИЕМ
            if (length < size)
            {
                buffer[length++] = (char)c;
            }
        }
    }

    // Завершаем строку нуль-терминатором
    buffer[length] = '\0';

    // Оптимизация: "подрезаем" лишнюю память перед возвратом
    char *final_buffer = (char *)realloc(buffer, length + 1);
    return final_buffer ? final_buffer : buffer;
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

        if (status == EOF)
        {
            printInputClosed();
            exit(1);
        }

        if (status == 1)
        {
            // Проверка на "бесконечность" (если ввели слишком огромное число)
            if (isfinite(value))
            {
                return value;
            }
            else
            {
                printf("Ошибка! Число слишком велико для обработки.\n");
                printf("Попробуйте снова: ");
                clearBuffer();
                continue;
            }
        }

        printTypeError(&value);
        clearBuffer();
    }
}

// int input checker
int get_int(const char *prompt)
{
    long long buffer; // Используем long long, чтобы поймать переполнение int
    int status;

    printf("%s", prompt);
    while (1)
    {
        // Читаем как long long (%lld)
        status = scanf("%lld", &buffer);

        if (status == EOF)
        {
            printInputClosed();
            exit(1);
        }

        if (status == 1)
        {
            // Проверяем, входит ли число в диапазон обычного int
            if (buffer >= INT_MIN && buffer <= INT_MAX)
            {
                // Успех: число влезает в int
                return (int)buffer;
            }
            else
            {
                // Ошибка: число слишком большое или маленькое
                printf("Ошибка! Число вне допустимого диапазона (%d ... %d)\n", INT_MIN, INT_MAX);
                printf("Попробуйте снова: ");
                clearBuffer();
                continue;
            }
        }

        // Если status == 0 (введены буквы)
        // Передаем указатель на int-переменную, чтобы сработал макрос _Generic
        int dummy;
        printTypeError(&dummy);
        clearBuffer();
    }
}