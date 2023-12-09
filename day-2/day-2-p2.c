#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getAdvanceOffset(char *);
void computeMinimumCubes(char *, int *, char *, int, int);

const int gameIdIndex = 5;

char *greenString = "green";
int greenStringLength = 5;

char *blueString = "blue";
int blueStringLength = 4;

char *redString = "red";
int redStringLength = 3;

int valueOffset = 2;

int main()
{
    FILE *file;
    file = fopen("./input.txt", "r");
    int bufferLength = 255;
    char buffer[bufferLength];

    char *subsets;

    int total = 0;

    if (file == NULL)
    {
        return -1;
    }

    while (fgets(buffer, bufferLength, file))
    {
        int rgbColors[3] = {0, 0, 0};
        long gameId = strtol((buffer + gameIdIndex), &subsets, 10);

        int advanceOffset = getAdvanceOffset(subsets);

        while (advanceOffset > -1)
        {
            long noOfCubes = strtol((subsets + advanceOffset), &subsets, 10);
            computeMinimumCubes(redString, &rgbColors[0], subsets, advanceOffset, noOfCubes);
            computeMinimumCubes(greenString, &rgbColors[1], subsets, advanceOffset, noOfCubes);
            computeMinimumCubes(blueString, &rgbColors[2], subsets, advanceOffset, noOfCubes);

            advanceOffset = getAdvanceOffset(subsets);
        }

        total += rgbColors[0] * rgbColors[1] * rgbColors[2];
    }

    fclose(file);
    printf("%d\n", total);

    return 0;
}

int getAdvanceOffset(char *subsets)
{
    int advanceOffset = 0;
    while (1)
    {
        advanceOffset++;

        if (*(subsets + advanceOffset) == '\n')
        {
            return -1;
        }

        if (isdigit(*(subsets + advanceOffset)))
        {
            return advanceOffset;
        }
    }
}

void computeMinimumCubes(char *coloredBlock, int *currentColoredBlockCount, char *subsets, int advanceOffset, int noOfCubes)
{
    char *cubeType = strstr((subsets), coloredBlock);

    if (cubeType == (subsets + 1) && noOfCubes > *currentColoredBlockCount)
    {
        *currentColoredBlockCount = noOfCubes;
    }
}