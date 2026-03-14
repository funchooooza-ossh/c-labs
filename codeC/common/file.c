#ifndef FILE_C
#define FILE_C

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *filename, const char *mode)
{
    FILE *f = fopen(filename, mode);

    if (f == NULL)
    {
        // Выводим системную ошибку (например, "No such file or directory")
        perror("Error opening file");
        // Если без файла работа невозможна — убиваем процесс
        exit(EXIT_FAILURE);
    }

    return f;
}

int count_lines(const char *filename)
{
    FILE *f = open_file(filename, "r");
    if (!f)
        return 0;
    int lines = 0;
    char ch;
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }

    fclose(f);
    return lines;
}

#endif
