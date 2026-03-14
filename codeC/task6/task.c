#include "file.c"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256

int main()
{
    const char *first_filename = "task6.1.txt";
    const char *final_filename = "task6.2.txt";

    // Действие1 -- Пишем dataset в файлик
    FILE *f_write = open_file(first_filename, "w");
    if (!f_write)
        return 1;

    // намеренно используем сырой char массив с "" терминатором на конце.
    // вообще мы могли бы работать с данным масивом через sizeof, т.к он объявлен здесь же
    // но данный подход дает возможность проитерировать данный массив где угодно
    char dataset[][MAX_LINE_LEN] = {
        "Иванов Петр Сергеевич 1975",
        "Сидоров Николай Андреевич 1981",
        "Воробьянинов Ипполит Матвеевич 1978",
        "Тестов Тест Тестович 2542",
        "",
    };

    for (int i = 0; dataset[i][0] != '\0'; i++)
    {
        fputs(dataset[i], f_write);

        if (dataset[i][strlen(dataset[i]) - 1] != '\n')
        {
            fputc('\n', f_write);
        }
    }

    fclose(f_write);
    // Конец действия 1

    // Действие 2 -- читаем содержимое файла в новый dataset
    // Получаем количество строк
    int lines_count = count_lines(first_filename);
    if (lines_count == 0)
        return 1;

    // dataset по кол-ву строк + 1 для "\0"
    char **dataset2 = malloc((lines_count + 1) * sizeof(char *));

    // открываем под чтение
    FILE *f_read = open_file(first_filename, "r");
    if (!f_read)
        return 1;

    // выделяем буффер
    char buffer[MAX_LINE_LEN];
    int i = 0;

    // собираем строки из файла в буффер
    while (fgets(buffer, MAX_LINE_LEN, f_read) && i < lines_count)
    {
        // заменяем \n на нуль терминатор
        buffer[strcspn(buffer, "\n")] = '\0';

        // выделяем память и копируем значение в dataset
        dataset2[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(dataset2[i], buffer);
        i++;
    }

    // добавляем в конец нуль терминатор для удобной итерации
    dataset2[i] = malloc(1 * sizeof(char));
    dataset2[i][0] = '\0';

    fclose(f_read);
    // Конец действия 2

    // Действие 3
    FILE *f_final = open_file(final_filename, "w");

    for (int i = 0; dataset2[i][0] != '\0'; i++)
    {
        char fn[MAX_LINE_LEN], sn[MAX_LINE_LEN], p[MAX_LINE_LEN];
        int year;

        if (sscanf(dataset2[i], "%s %s %s %d", fn, sn, p, &year) == 4)
        {
            if (year > 1980)
            {
                fputs(dataset2[i], f_final);

                if (dataset2[i][strlen(dataset2[i]) - 1] != '\n')
                {
                    fputc('\n', f_final);
                }
            }
        }
    }
    fclose(f_final);
    // Конец действия

    // Уборка
    for (int j = 0; j <= lines_count; j++)
    {
        free(dataset2[j]);
    }
    free(dataset2);
}