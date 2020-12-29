#include <stdio.h>
#include <stdlib.h>
#include "region.h"
// Michael Lenort, 19947059

RegionList *newRegionList()
{
    //printf("executed newRegionlist");
    RegionList *rl = (RegionList *)malloc(sizeof(RegionList));
    rl->count = 0;
    rl->allocated = 11;
    rl->region = (Region **)calloc(rl->allocated, sizeof(Region *));
    return rl;
}

// Same as above.
Region *newRegion(RegionList *rl)
{
    if (rl->count >= rl->allocated)
    {
        rl->allocated *= 2;
        rl->region = (Region **)realloc(rl->region, rl->allocated * sizeof(Region *));
    }
    Region *r = (Region *)malloc(sizeof(Region));
    rl->region[rl->count++] = r;
    return r;
}

// Reads the file stadt.dat and adds the data to our StadtList struct.
void readRegionList(RegionList *rl, char *fileName)
{
    // Integer used for the iteration.
    int r = 0;

    FILE *file = fopen(fileName, "r");
    // If there isn't a file, we can't read anything. Return error.
    if (file == NULL)
    {
        perror(fileName);
        exit(1);
    }

    // while r != EOF
    while (r != EOF)
    {

        Region *re = newRegion(rl);
        r = fscanf(file, "%d %100s %d %1s",
                   &re->regionId, re->name, &re->overRegion, re->_typ);
    }

    fclose(file);
}

Region *findRegion(RegionList *rl, int id)
{
    int i;
    Region *r = NULL;

    for (i = 0; i < rl->count; i++)
        if (rl->region[i]->regionId == id)
        {
            r = rl->region[i];
        }
    return r;
}

void printR(RegionList *rl, int id)
{

    Region *r = findRegion(rl, id);

    printf("%101s \n", r->name);
}
