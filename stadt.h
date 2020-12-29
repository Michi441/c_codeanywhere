#ifndef STADT_H
#define STADT_H
#include "region.h"

// Michael Lenort, 19947059

typedef struct{
    int stadtId;
    char name[101];
    int einwohner;
    int gebietId;
    int meeresHoehe;
    int distance;
} Stadt;

typedef struct {
    Stadt **stadt;
    int count;
    int allocated;
} StadtList;

typedef struct {
    int stadtStart;
    int stadtEnd;
    int distance;
} Street;
typedef struct
{
    Street **street;
    int count;
    int allocated;
} StreetList;

struct CityStreetArray
{
    int stadtId;
    char name[101];
    int einwohner;
    int gebietId;
    int stadtStart;
    int stadtEnd;
    int distance;
};

StadtList *
newStadtList();
Stadt *newStadt(StadtList *sl);

StreetList *newStreetList();
Street *newStreet(StreetList *streetList);
void readStadtList(StadtList *sl, char *fileName);
void printStadt(Stadt *s);
void GetAllDistancesFromCity(StadtList *sl2,StadtList *sl1, Stadt *s, StreetList *streetList);
int stadtSort(const void *a, const void *b);

void readStreetList(StreetList *streetList, char *fileName);
void TheDestroyer(StadtList *sl, RegionList *rl, char *name, StreetList *streetList);


void printStadtWithId(StadtList *sl, char *name);
void GetPopulationSize(StadtList *sl, char *name);

void SortArray(int *arr, int length);
void sortTrackList(StadtList *sl);
void WriteAfterMathData(StadtList *sl, Stadt *s, Stadt *s2, char *fileName);

void stringSubst(char *s, char old, char _new); 

#endif