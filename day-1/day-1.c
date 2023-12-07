#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char getFirstDigit(char *);
char getLastDigit(char *);
char getDigitFromWord(char *);

char *threeLetterDigits[3][2] = {{"one", "1"}, {"two", "2"}, {"six", "6"}};
char *fourLetterDigits[3][2] = {{"four", "4"}, {"five", "5"}, {"nine", "9"}};
char *fiveLetterDigits[3][2] = {{"three", "3"}, {"seven", "7"}, {"eight", "8"}};

int main()
{
    FILE *file;
    file = fopen("./input.txt", "r");
    int bufferLength = 255;
    char buffer[bufferLength];

    int total = 0;

    if (file == NULL)
    {
        return -1;
    }

    while (fgets(buffer, bufferLength, file))
    {
        char firstAndLastDigits[2];
        firstAndLastDigits[0] = getFirstDigit(buffer);
        firstAndLastDigits[1] = getLastDigit(buffer);

        total += atoi(firstAndLastDigits);
    }

    fclose(file);
    printf("%d\n", total);

    return 0;
}

char getFirstDigit(char *line)
{
    int offset = 0;

    while (offset < strlen(line))
    {
        // part 1
        if (isdigit(*(line + offset)))
        {
            return line[offset];
        }

        // part 2
        char digitFromWord = getDigitFromWord(line + offset);
        if (digitFromWord != '\0')
        {
            return digitFromWord;
        }

        offset++;
    }
}

char getLastDigit(char *line)
{
    int offset = strlen(line) - 2;

    while (offset >= 0)
    {
        // part 1
        if (isdigit(*(line + offset)))
        {
            return line[offset];
        }

        // part 2
        char digitFromWord = getDigitFromWord(line + offset);
        if (digitFromWord != '\0')
        {
            return digitFromWord;
        }

        offset--;
    }
}

char getDigitFromWord(char *subword)
{
    if (strlen(subword) >= 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(subword, *(threeLetterDigits + i)[0], 3) == 0)
            {
                return *(*(threeLetterDigits + i))[1];
            }
        }
    }

    if (strlen(subword) >= 4)
    {
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(subword, *(fourLetterDigits + i)[0], 4) == 0)
            {
                return *(*(fourLetterDigits + i))[1];
            }
        }
    }

    if (strlen(subword) >= 5)
    {
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(subword, *(fiveLetterDigits + i)[0], 5) == 0)
            {
                // char *t1 = *(*(fiveLetterDigits + i) + 1);
                // char *t2 = **(fiveLetterDigits + i);
                // char *t3 = **(&fiveLetterDigits[0] + i);
                // char *t4 = *(fiveLetterDigits[i] + 1);
                // char *t5 = (*(fiveLetterDigits + i))[1];

                // return **(*(fiveLetterDigits + i) + 1);
                // return *fiveLetterDigits[i][1];
                return *(*(fiveLetterDigits + i))[1];
            }
        }
    }

    return '\0';
}