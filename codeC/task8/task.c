#include <time.h>
#include "file.c"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 256

typedef struct
{
    char name_or_surname[51];
    int birth_year;
    char sex[5];
    double height;
} humen;

int is_valid_birth_year(int year)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    int min_year = 1900;

    if (year >= min_year && year <= current_year)
    {
        return 1;
    }
    printf("\nОшибка! %d не валиден. Диапазон: %d - %d\n", year, min_year, current_year);
    return 0;
}

// Сравнение по году (от меньшего к большему)
int compare_birth_year(const void *a, const void *b)
{
    return ((humen *)a)->birth_year - ((humen *)b)->birth_year;
}

// Сравнение по росту (от большего к меньшему)
int compare_height(const void *a, const void *b)
{
    double diff = ((humen *)b)->height - ((humen *)a)->height;
    return (diff > 0) ? 1 : (diff < 0) ? -1
                                       : 0;
}

// Сравнение по имени (алфавит)
int compare_name(const void *a, const void *b)
{
    return strcmp(((humen *)a)->name_or_surname, ((humen *)b)->name_or_surname);
}

// Сравнение по полу
int compare_sex(const void *a, const void *b)
{
    return strcmp(((humen *)a)->sex, ((humen *)b)->sex);
}

int sort_order[4];   // Массив индексов полей для сортировки
int sort_levels = 0; // Сколько полей выбрал пользователь

int multi_comparator(const void *a, const void *b)
{
    for (int i = 0; i < sort_levels; i++)
    {
        int result = 0;
        switch (sort_order[i])
        {
        case 1:
            result = compare_birth_year(a, b);
            break;
        case 2:
            result = compare_name(a, b);
            break;
        case 3:
            result = compare_sex(a, b);
            break;
        case 4:
            result = compare_height(a, b);
            break;
        }
        // Если значения по текущему полю разные — возвращаем результат.
        // Если одинаковые — переходим к следующему приоритету в цикле.
        if (result != 0)
            return result;
    }
    return 0;
}

humen readline_into_humen_struct(char *line)
{
    humen h = {0};

    int scanned = sscanf(line, "%50s %d %4s %lf",
                         h.name_or_surname,
                         &h.birth_year,
                         h.sex,
                         &h.height);

    if (scanned < 4)
    {
        h.birth_year = -1;
    }
    if (strcmp(h.sex, "М") != 0 && strcmp(h.sex, "Ж") != 0)
    {
        h.birth_year = -1;
    }

    return h;
}

int main()
{
    setlocale(LC_NUMERIC, "C");
    const char *inp_filename = "task8.txt";
    int lines_count = count_lines(inp_filename);
    if (lines_count == 0)
    {
        printf("\nEmpty input file\n");
        return 1;
    }
    printf("\nline count:%d\n", lines_count);

    humen dataset[lines_count];

    FILE *f_read = open_file(inp_filename, "r");
    if (!f_read)
        return 1;

    char buffer[MAX_LINE_LEN];
    int current_struct = 0;

    while (fgets(buffer, MAX_LINE_LEN, f_read) && current_struct < lines_count)
    {
        humen temp = readline_into_humen_struct(buffer);

        if (temp.birth_year != -1 && is_valid_birth_year(temp.birth_year))
        {
            dataset[current_struct] = temp;
            current_struct++;
        }
    }

    fclose(f_read);

    printf("\nВыберите поля для сортировки в порядке приоритета (0 - закончить выбор):\n");
    printf("1 - Год рождения, 2 - Имя, 3 - Пол, 4 - Рост\n");

    int choice;
    while (sort_levels < 4)
    {
        printf("Приоритет %d: ", sort_levels + 1);
        if (scanf("%d", &choice) != 1 || choice == 0)
            break;
        if (choice >= 1 && choice <= 4)
        {
            sort_order[sort_levels++] = choice;
        }
    }

    if (sort_levels == 0)
    {
        printf("\nНичего не выбрано. Сортировка по умолчанию: Имя.\n");
        sort_order[0] = 2;
        sort_levels = 1;
    }

    qsort(dataset, current_struct, sizeof(humen), multi_comparator);

    printf("\n--- Результат сортировки ---\n");
    for (int i = 0; i < current_struct; i++)
    {
        printf("%-15s | %d | %s | %.2f\n",
               dataset[i].name_or_surname,
               dataset[i].birth_year,
               dataset[i].sex,
               dataset[i].height);
    }

    return 0;
}