#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

    int rgbColors[3];

    while (fgets(buffer, bufferLength, file))
    {
        long gameId = strtol((buffer + gameIdIndex), &subsets, 10);

        bool isValidGame = true;

        char *bag = strtok((subsets), ";");

        while (bag != NULL)
        {
            int advanceOffset = getAdvanceOffset(bag);

            rgbColors[0] = 12;
            rgbColors[1] = 13;
            rgbColors[2] = 14;

            while (advanceOffset > -1)
            {
                long noOfCubes = strtol((bag + advanceOffset), &bag, 10);
                computeMinimumCubes(redString, &rgbColors[0], bag, advanceOffset, noOfCubes);
                computeMinimumCubes(greenString, &rgbColors[1], bag, advanceOffset, noOfCubes);
                computeMinimumCubes(blueString, &rgbColors[2], bag, advanceOffset, noOfCubes);

                advanceOffset = getAdvanceOffset(bag);
            }

            if (rgbColors[0] < 0 || rgbColors[1] < 0 || rgbColors[2] < 0)
            {
                isValidGame = false;
                break;
            }

            bag = strtok(NULL, ";");
        }

        if (isValidGame)
        {
            total += gameId;
        }
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

        if (*(subsets + advanceOffset) == '\000')
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

    if (cubeType == (subsets + 1))
    {
        *currentColoredBlockCount = *currentColoredBlockCount - noOfCubes;
    }
}