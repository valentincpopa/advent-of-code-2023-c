#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int getAdvanceOffset(char *numberSets);

int main()
{
    FILE *file;
    file = fopen("./input.txt", "r");
    int bufferLength = 255;
    char buffer[bufferLength];

    int *scratchCardsCount = calloc(512, sizeof(int));
    char *numberSets;

    if (file == NULL)
    {
        return -1;
    }

    long gameId;
    double cardsWon = 0;
    double total = 0;

    while (fgets(buffer, bufferLength, file))
    {
        int advanceOffset = getAdvanceOffset(buffer);
        gameId = strtol((buffer + advanceOffset), &numberSets, 10);

        int *winningNumbers = calloc(100, sizeof(int));
        int *numbersInHand = calloc(100, sizeof(int));

        char *numberSet = strtok((numberSets), "|");
        int winningNumberCount = 0;
        int setId = 0;

        while (numberSet != NULL)
        {
            setId++;
            int advanceOffset = getAdvanceOffset(numberSet);

            while (advanceOffset > -1)
            {
                if (setId == 1)
                {
                    long winningNumber = strtol((numberSet + advanceOffset), &numberSet, 10);
                    winningNumbers[winningNumberCount] = winningNumber;
                    winningNumberCount++;
                }
                else
                {
                    long numberInHand = strtol((numberSet + advanceOffset), &numberSet, 10);
                    numbersInHand[numberInHand]++;
                }
                advanceOffset = getAdvanceOffset(numberSet);
            }

            numberSet = strtok(NULL, "|");
        }

        for (int i = 0; i < winningNumberCount; i++)
        {
            if (numbersInHand[winningNumbers[i]] == 1)
            {
                cardsWon++;
            }
        }

        if (cardsWon > 0)
        {
            for (int i = 0; i <= scratchCardsCount[gameId]; i++)
            {
                for (int j = 1; j <= cardsWon; j++)
                {
                    scratchCardsCount[gameId + j]++;
                }
            }
        }
    }

    for (int i = 1; i <= gameId; i++)
    {
        total += scratchCardsCount[i] + 1;
    }

    printf("%1.f", total);
}

int getAdvanceOffset(char *numberSets)
{
    int advanceOffset = 0;
    while (1)
    {
        advanceOffset++;

        if (*(numberSets + advanceOffset) == '\000')
        {
            return -1;
        }

        if (isdigit(*(numberSets + advanceOffset)))
        {
            return advanceOffset;
        }
    }
}