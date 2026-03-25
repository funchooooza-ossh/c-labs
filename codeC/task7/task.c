#include "input.c"
#include "output.c"
#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 4

typedef struct
{
    char name[51];
    char surname[51];
    int birth_year;
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

humen get_humen(const char *prompt)
{
    printf(prompt);

    humen h;
    // 1. Ввод Имени
    char *temp_name = get_string("Введите имя: ", 50);
    strncpy(h.name, temp_name, 50);
    h.name[50] = '\0'; // Гарантируем ноль в конце
    free(temp_name);

    // 2. Ввод Фамилии
    char *temp_surname = get_string("Введите фамилию: ", 50);
    strncpy(h.surname, temp_surname, 50);
    h.surname[50] = '\0';
    free(temp_surname); // Освобождаем память

    // 3. Ввод Года рождения
    while (1)
    {
        int year = get_positive_int("Введите год рождения: ");

        if (is_valid_birth_year(year))
        {
            h.birth_year = year;
            clearBuffer();
            break;
        }
    }

    return h;
}

void print_humen(int index, humen h)
{

    printf("| %-2d | %-15s | %-15s | %-14d |\n", index, h.name, h.surname, h.birth_year);
}
int main()
{
    humen dataset[DATASET_SIZE];
    humen dataset2[DATASET_SIZE];

    for (int i = 0; i < DATASET_SIZE; i++)
    {
        char prompt[100];
        sprintf(prompt, "\nВведите данные человека №%d\n", i + 1);
        dataset[i] = get_humen(prompt);
    }

    printf("-----------------------------------------------------------\n");
    printf("| # | Имя             | Фамилия         | Год рождения    |\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < DATASET_SIZE; i++)
    {
        print_humen(i, dataset[i]);
        printf("\n");
    }

    // копируем данные(хз зачем, можно сделать in-place сортировку)
    for (int i = 0; i < DATASET_SIZE; i++)
    {
        dataset2[i] = dataset[i];
    }

    for (int i = 0; i < DATASET_SIZE - 1; i++)
    {
        for (int j = 0; j < DATASET_SIZE - i - 1; j++)
        {
            // Если год рождения текущего элемента больше следующего — меняем их местами
            if (dataset2[j].birth_year > dataset2[j + 1].birth_year)
            {
                humen temp = dataset2[j];
                dataset2[j] = dataset2[j + 1];
                dataset2[j + 1] = temp;
            }
        }
    }

    printf("-----------------------------------------------------------\n");
    printf("| # | Имя             | Фамилия         | Год рождения    |\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < DATASET_SIZE; i++)
    {
        print_humen(i, dataset2[i]);
        printf("\n");
    }

    return 0;
}
