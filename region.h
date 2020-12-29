#ifndef REGION_H
#define REGION_H
//#include "stadt.h"
// Michael Lenort, 19947059

typedef struct
{
    int regionId;
    char name[101];
    int overRegion;
    char _typ[1]; 
} Region;

typedef struct
{
    Region **region;
    int count;
    int allocated;
} RegionList;


RegionList *newRegionList();

Region *newRegion(RegionList *rl);
Region *findRegion(RegionList *rl, int id);
void readRegionList(RegionList *rl, char *fileName);

//void SortCitiesToRegion(RegionList *rl, StadtList *sl);
void printR(RegionList *rl, int id);

#endif