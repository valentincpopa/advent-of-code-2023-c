#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Symbol
{
    char value;
    int position[2];

    int adjentNumbersCount;
    char **numbers;

} Symbol;

void getNumberOfLinesAndLength(FILE *file, int *numberOfLines, int *lineLength);
void readLines(FILE *file, int noOfLines, int lineLength, char lines[noOfLines][lineLength]);
int getPartNumbersSum(Symbol **symbols, int noOfSymbols);
int getGearRatios(Symbol **symbols, int noOfSymbols);

const int noOfPossibleNeighbours = 8;
int neighbours[8][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};

int main()
{
    FILE *file;
    file = fopen("./input.txt", "r");

    if (file == NULL)
    {
        return -1;
    }

    int lineLength, noOfLines;

    getNumberOfLinesAndLength(file, &noOfLines, &lineLength);
    rewind(file);

    char lines[noOfLines][lineLength];
    readLines(file, noOfLines, lineLength, lines);

    Symbol **symbols;
    int noOfSymbols = 0;

    for (int i = 0; i < noOfLines; i++)
    {
        for (int j = 0; j < lineLength; j++)
        {
            if (lines[i][j] != '.' && !isdigit(lines[i][j]))
            {
                noOfSymbols++;
                symbols = realloc(symbols, noOfSymbols * sizeof(Symbol *));

                Symbol *symbol = malloc(sizeof(Symbol));
                symbol->numbers = malloc(sizeof(char *));
                symbol->value = lines[i][j];
                symbol->position[0] = i;
                symbol->position[1] = j;

                symbols[noOfSymbols - 1] = symbol;

                int noOfValidNumbers = 0;
                for (int k = 0; k < noOfPossibleNeighbours; k++)
                {
                    int ni = i + neighbours[k][0];
                    int nj = j + neighbours[k][1];

                    if (ni >= 0 && ni < noOfLines && nj >= 0 && nj < lineLength)
                    {
                        if (!isdigit(lines[ni][nj]))
                        {
                            continue;
                        }

                        while (isdigit(lines[ni][nj]))
                        {
                            nj--;
                        }

                        if (noOfValidNumbers > 0 && symbol->numbers[noOfValidNumbers - 1] == &lines[ni][nj + 1])
                        {
                            continue;
                        }

                        noOfValidNumbers++;
                        symbol->numbers = realloc(symbol->numbers, noOfValidNumbers * sizeof(char *));
                        symbol->adjentNumbersCount = noOfValidNumbers;
                        symbol->numbers[noOfValidNumbers - 1] = &lines[ni][nj + 1];
                    }
                }
            }
        }
    }

    int partNumbersSum = getPartNumbersSum(symbols, noOfSymbols);
    printf("%d", partNumbersSum);

    int gearRatios = getGearRatios(symbols, noOfSymbols);
    printf("%d", gearRatios);

    return 0;
}

void getNumberOfLinesAndLength(FILE *file, int *noOfLines, int *lineLength)
{
    int bufferLength = 255;
    char buffer[bufferLength];
    int i = 0;

    while (fgets(buffer, bufferLength, file))
    {
        *lineLength = strlen(buffer);
        i++;
    }

    *noOfLines = i;
}

void readLines(FILE *file, int noOfLines, int lineLength, char lines[noOfLines][lineLength])
{
    int i = 0;
    while (fgets(*(lines + i), lineLength + 2, file))
    {
        i++;
    }
}

int getPartNumbersSum(Symbol **symbols, int noOfSymbols)
{
    int partNumbersSum = 0;
    for (int i = 0; i < noOfSymbols; i++)
    {
        for (int j = 0; j < (*(symbols[i])).adjentNumbersCount; j++)
        {
            partNumbersSum += strtoul((*(symbols[i])).numbers[j], NULL, 10);
        }
    }

    return partNumbersSum;
}

int getGearRatios(Symbol **symbols, int noOfSymbols)
{
    int partNumbersSum = 0;
    for (int i = 0; i < noOfSymbols; i++)
    {
        if ((*(symbols[i])).adjentNumbersCount != 2)
        {
            continue;
        }

        int partNumbersProduct = 1;
        for (int j = 0; j < (*(symbols[i])).adjentNumbersCount; j++)
        {
            partNumbersProduct *= strtoul((*(symbols[i])).numbers[j], NULL, 10);
        }

        partNumbersSum += partNumbersProduct;
    }

    return partNumbersSum;
}