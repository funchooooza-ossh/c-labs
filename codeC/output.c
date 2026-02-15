#include <stdio.h>

void printLine(int cols, int width)
// func to printf pretty line
{
    printf("   +");
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < width + 2; j++)
            printf("-");
        printf("+");
    }
    printf("\n");
}
