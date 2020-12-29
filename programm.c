// Michael Lenort, 19947059

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stadt.h"
#include "region.h"
int main(int argc, char *argv[])
{
    //int count = 1;

    if (argc < 3)
    {

        printf("Error, arguments invalid or wrong.\n");
    }

    StadtList *sl = newStadtList();
    Stadt *newStadt(StadtList * sl);

    RegionList *rl = newRegionList();
    Region *newRegion(RegionList * rl);
    StreetList *streetList = newStreetList();
    Street *newStreet(StreetList * streetList);
    readStadtList(sl, argv[1]);

    readRegionList(rl, argv[2]);

    readStreetList(streetList, argv[3]);
    char *name = argv[4];

    //printf("%s", "Which city do you want to destroy? Type in the City Name: ");
    //scanf("%s", &name);
    //printf("%s", name);
    if (name != NULL)
        TheDestroyer(sl, rl, name, streetList);
}
