#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int getAdvanceOffset(char *numberSets);

typedef struct MapItem
{
    long long sourceInterval[2];
    long long destinationInterval[2];
} MapItem;

typedef struct Map
{
    MapItem **mapItems;
    int mapItemsCount;
} Map;

int main()
{
    FILE *file;
    file = fopen("./input.txt", "r");

    if (file == NULL)
    {
        return -1;
    }

    int bufferLength = 255;
    char buffer[bufferLength];

    fgets(buffer, bufferLength, file);
    int advanceOffset = getAdvanceOffset(buffer);

    long long seeds[63];
    int seedCount = 0;
    char *line = buffer;

    while (advanceOffset > -1)
    {
        seeds[seedCount] = strtol(line + advanceOffset, &line, 10);
        advanceOffset = getAdvanceOffset(line);

        seedCount++;
    }

    Map maps[100];
    Map *currentMap = NULL;
    int mapCount = 0;
    int mapItemsCount = 0;

    while (fgets(buffer, bufferLength, file))
    {
        if (strlen(buffer) < 2)
        {
            continue;
        }

        if (strstr(buffer, "map"))
        {
            currentMap = &maps[mapCount];
            currentMap->mapItems = malloc(sizeof(MapItem *));
            mapCount++;

            mapItemsCount = 0;
            continue;
        }

        mapItemsCount++;
        currentMap->mapItemsCount = mapItemsCount;
        currentMap->mapItems = realloc(currentMap->mapItems, mapItemsCount * sizeof(MapItem *));

        line = buffer;
        advanceOffset = 0;

        MapItem *mapItem = malloc(sizeof(MapItem));
        *(currentMap->mapItems + mapItemsCount - 1) = mapItem;

        int type = 0;
        while (advanceOffset > -1)
        {
            type++;

            long long destSrcOffset = strtoll((line + advanceOffset), &line, 10);

            if (type == 1)
            {
                mapItem->destinationInterval[0] = destSrcOffset;
            }
            else if (type == 2)
            {
                mapItem->sourceInterval[0] = destSrcOffset;
            }
            else if (type == 3)
            {
                mapItem->destinationInterval[1] = mapItem->destinationInterval[0] + destSrcOffset - 1;
                mapItem->sourceInterval[1] = mapItem->sourceInterval[0] + destSrcOffset - 1;
            }

            advanceOffset = getAdvanceOffset(line);
        }
    }

    int soil[seedCount];

    for (int i = 0; i < mapCount; i++)
    {
        Map currentMap = maps[i];

        for (int j = 0; j < seedCount; j++)
        {
            for (int k = 0; k < currentMap.mapItemsCount; k++)
            {
                MapItem currentMapItem = **(currentMap.mapItems + k);
                if (seeds[j] >= currentMapItem.sourceInterval[0] && seeds[j] <= currentMapItem.sourceInterval[1])
                {
                    seeds[j] = currentMapItem.destinationInterval[0] - currentMapItem.sourceInterval[0] + seeds[j];
                    break;
                }
            }
        }
    }

    long long min = __LONG_LONG_MAX__;
    for (int i = 0; i < seedCount; i++)
    {
        if (min > seeds[i])
        {
            min = seeds[i];
        }
    }

    printf("%lld", min);

    return 0;
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