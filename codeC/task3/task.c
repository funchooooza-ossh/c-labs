#include <string.h>
#include <stdio.h>
#include <input.c>
#include <ctype.h>

char *to_upper_specific(const char *input, const char *targets)
{
    if (input == NULL || targets == NULL)
        return NULL;

    // 1. Выделяем память под новую строку такой же длины (+1 для \0)
    int len = strlen(input);
    char *result = (char *)malloc((len + 1) * sizeof(char));

    if (!result)
    {
        fprintf(stderr, "Ошибка памяти!\n");
        exit(1);
    }

    // 2. Проходим по каждому символу исходной строки
    for (int i = 0; i < len; i++)
    {
        // Проверяем, есть ли текущий символ input[i] в строке targets
        if (strchr(targets, input[i]) != NULL)
        {
            // Если нашли — переводим в верхний регистр
            result[i] = (char)toupper((unsigned char)input[i]);
        }
        else
        {
            // Если нет — копируем как есть
            result[i] = input[i];
        }
    }

    // 3. Завершаем строку
    result[len] = '\0';

    return result;
}
int main()
{
    const char *upperCaseMatch = "ab";

    const char *input = get_string("string=", 80);

    char *result = to_upper_specific(input, upperCaseMatch);

    printf("\n RESULT IS %s\n", result);
    return 1;
}