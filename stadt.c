#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stadt.h"
#include "region.h"
// Michael Lenort, 19947059

StadtList *newStadtList()
{
    StadtList *sl = (StadtList *)malloc(sizeof(StadtList));
    sl->count = 0;
    sl->allocated = 10;
    sl->stadt = (Stadt **)calloc(sl->allocated, sizeof(Stadt *));
    return sl;
}

StreetList *newStreetList()
{

    StreetList *streetList = (StreetList *)malloc(sizeof(StreetList));
    streetList->count = 0;
    streetList->allocated = 10;
    streetList->street = (Street **)calloc(streetList->allocated, sizeof(Street *));
    return streetList;
}

Street *newStreet(StreetList *streetList)
{
    if (streetList->count >= streetList->allocated)
    {
        streetList->allocated *= 2;
        streetList->street = (Street **)realloc(streetList->street, streetList->allocated * sizeof(StreetList *));
    }

    Street *street = (Street *)malloc(sizeof(Street));
    streetList->street[streetList->count++] = street;
    return street;
}
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
// Same as above.
Stadt *newStadt(StadtList *sl)
{
    if (sl->count >= sl->allocated)
    {
        sl->allocated *= 2;
        sl->stadt = (Stadt **)realloc(sl->stadt, sl->allocated * sizeof(Stadt *));
    }
    Stadt *s = (Stadt *)malloc(sizeof(Stadt));
    sl->stadt[sl->count++] = s;
    return s;
}
void readStreetList(StreetList *streetList, char *fileName)
{

    int x = 0;

    FILE *file = fopen(fileName, "r");
    // If there isn't a file, we can't read anything. Return error.
    if (file == NULL)
    {
        perror(fileName);
        exit(1);
    }

    // Integer used for the iteration.
    // while r != EOF
    do
    {

        if (x != EOF)
        {
            Street *street = newStreet(streetList);

            x = fscanf(file, "%d %d %d",
                       &street->stadtStart, &street->stadtEnd, &street->distance);
            //printf("%d %d %d \n", street->stadtStart, street->stadtEnd, street->distance);
        }
    } while (x != EOF);

    fclose(file);
}

// Reads the file stadt.dat and adds the data to our StadtList struct.
void readStadtList(StadtList *sl, char *fileName)
{

    FILE *file = fopen(fileName, "r");
    // If there isn't a file, we can't read anything. Return error.
    if (file == NULL)
    {
        perror(fileName);
        exit(1);
    }

    // Integer used for the iteration.
    int r, id;

    // while r != EOF
    do
    {
        r = fscanf(file, "%d", &id);

        if (r != EOF)
        {
            Stadt *s = newStadt(sl);
            s->stadtId = id;
            r = fscanf(file, "%100s %d %d %d",
                       s->name, &s->gebietId, &s->einwohner, &s->meeresHoehe);
            //printStadt(s);
        }

    } while (r != EOF);
    fclose(file);
}

// Finds a city in a given CityList with an string.
Stadt *findStadt(StadtList *sl, char *city)
{
    int i;

    // Needs to be declared because we want to return
    // a new city.
    Stadt *s = NULL;

    // For the length of our cityList, start an for loop.
    for (i = 0; i < sl->count; i++)
        // if inside our cityList the id of a city is equal
        // to the id that were injected as an argument
        if (strcmp(sl->stadt[i]->name, city) == 0)
        {
            // Set the Stadt *s (which points to NULL)
            // to the stadt that has the same id.
            s = sl->stadt[i];
        }
    // Return the new City with all data (name, gebietId etc.)
    return s;
}

// Is used for qsort to sort the neighbor cities by its closest distance
// to the city that will be destroyed.
int stadtSort(const void *a, const void *b)
{
    Stadt *ba = *(Stadt **)a;
    Stadt *bb = *(Stadt **)b;
    if (ba->distance > bb->distance)
        return +1;
    else if (ba->distance < bb->distance)
        return -1;
    else
        return 0;
}
// Destroys a city and evacuates the population.
void TheDestroyer(StadtList *sl, RegionList *rl, char *cityName, StreetList *streetList)
{
    int count = 0;

    // First, lets find the City we want to destroy by using the
    // findStadt function (add sl cityList and the id from the city.)
    Stadt *s = findStadt(sl, cityName);
    if (s == NULL)
    {
        printf("%s \n \n", "Sorry, but this City doesn't exist!");
        printf("%s \n \n", "No city was destroyed that day!");

        return;
    }

    // // Used to generate a second cityList that holds only neighbor
    // // cities from the city that should be destroyed.
    // // I think its good to seperate them as i don't want to
    // // mess around with the original cityList.
    // StadtList *sl2 = newStadtList();

    // Region *r = findRegion(rl, s->einwohner);
    // printf("%s %s %d\n", "Region of the City: ", r->name, r->regionId);
    // Region *bundesLand = findRegion(rl, r->overRegion);
    // printf("%s %s %d\n", "State of the Citys Region: ", bundesLand->name, bundesLand->regionId);
    // Region *Land = findRegion(rl, bundesLand->overRegion);
    // printf("%s %s %d\n \n", "Country of the City:", Land->name, Land->regionId);
    // printf("%s\n", "Neighbor Cities:");

    // get all regions
    // for (int i = 0; i < rl->count; i++)
    // {
    //     if (rl->region[i]->overRegion == bundesLand->regionId)
    //     {
    //         //printf("%s", rl->region[i]->name);
    //         for (int z = 0; z < sl->count; z++)
    //         {
    //             if (sl->stadt[z]->einwohner == rl->region[i]->regionId)
    //             {
    //                 count++;
    //                 printf("%s %d %s %s %d\n", "ID: ", sl->stadt[z]->stadtId, sl->stadt[z]->name, " Population Size: ", sl->stadt[z]->gebietId);
    //                 sl2->stadt[sl2->count++] = sl->stadt[z];
    //             }
    //         }
    //     }
    // }

    printf("%s %d \n", "Counter is...", count);
    printf("%s \n \n", "trying to find the closest city. Standby.");
    printf("%s %s \n", "city is...", cityName);
    int numbers = 0;
    for (int z = 0; z < sl->count; z++)
    {
        for (int y = 0; y < streetList->count; y++)
        {
            if ((streetList->street[y]->stadtStart == s->stadtId && streetList->street[y]->stadtEnd == sl->stadt[z]->stadtId) || (streetList->street[y]->stadtEnd == s->stadtId && streetList->street[y]->stadtStart == sl->stadt[z]->stadtId))
            {
                sl->stadt[z]->distance = streetList->street[y]->distance;
                numbers++;
                //printf("%d %s\n", sl->stadt[z]->distance, sl->stadt[z]->name);
            }
        }
    }

    //GetAllDistancesFromCity(sl2, sl, s, streetList);
    qsort(sl->stadt, sl->count, sizeof(Stadt *), &stadtSort);

    //int diff = 0;
    int sum = 0;

    for (int h = numbers; h > 0; h--)
    {
        sum = sum + sl->stadt[sl->count - h]->gebietId;
    }

    for (int o = numbers; o > 0 && sum != 0; o--)
    {

        long num1 = sl->stadt[sl->count - o]->gebietId;
        long num2 = s->gebietId;
        int diff = num2 * num1 / sum;
        //printf("%Ld \n", num2 * num1 / sum);
        sl->stadt[sl->count - o]->gebietId = sl->stadt[sl->count - o]->gebietId + diff;
        diff = 0;
        printf("%s %d %d \n", sl->stadt[sl->count - o]->name, sl->stadt[sl->count - o]->gebietId, sl->stadt[sl->count - o]->distance);
    }

    WriteAfterMathData(sl, s, s, "stadtneu.dat");

    //printf("%s %d\n", "number is", numbers);

    // for (int t = 0; t < sl->count; t++)
    // {
    //     printf("%s %d %d \n", sl->stadt[t]->name, sl->stadt[t]->gebietId, sl->stadt[t]->distance);
    // }
    //printf("%s %d\n", s->name, s->gebietId);
}

void GetAllDistancesFromCity(StadtList *sl2, StadtList *sl, Stadt *s, StreetList *streetList)
{

    printf("%s %s %s %d \n\n", "City to Destroy:", s->name, "Population Size:", s->gebietId);

    StadtList *sl3 = newStadtList();
    StreetList *selectedRoads = newStreetList();
    for (int i = 0; i < streetList->count; i++)
    {
        if (streetList->street[i]->stadtStart == s->stadtId)
        {

            for (int g = 0; g < sl2->count; g++)
            {

                if (sl2->stadt[g]->stadtId == streetList->street[i]->stadtEnd)
                {

                    sl3->stadt[sl3->count++] = sl2->stadt[g];
                }
            }

            printf("%s %d  %s %d %s %d \n", "Start ID:", streetList->street[i]->stadtStart, "End ID:", streetList->street[i]->stadtEnd, "Distance:", streetList->street[i]->distance);
            selectedRoads->street[selectedRoads->count++] = streetList->street[i];
            //Stadt *so = findStadt(sl, streetList->street[i]->stadtEnd);
        }

        // If the streetEnd is equal to the stadtId
        // we have a stadtStart that points to our city
        if (streetList->street[i]->stadtEnd == s->stadtId)
        {
            for (int g = 0; g < sl2->count; g++)
            {

                if (sl2->stadt[g]->stadtId == streetList->street[i]->stadtStart)
                {

                    printf("%s", sl2->stadt[g]->name);
                    sl3->stadt[sl3->count++] = sl2->stadt[g];
                    //sl3->stadt[g]->distance = streetList->street[i]->distance;
                    break;
                }
            }

            printf("%s %d  %s %d %s %d \n", "Start ID:", streetList->street[i]->stadtStart, "End ID:", streetList->street[i]->stadtEnd, "Distance:", streetList->street[i]->distance);
            selectedRoads->street[selectedRoads->count++] = streetList->street[i];
        }
    }

    //Sort from short to long distances.
    for (int u = 0; u < selectedRoads->count; u++)
    {

        printf("%d %s", selectedRoads->street[u]->distance, "!!!!");
        // int livePop = 0;

        // if (selectedRoads->street[u]->stadtStart == s->stadtId)
        // {

        //     for (int v = 0; v < sl2->count; v++)
        //     {
        //         if (sl2->stadt[v]->stadtId == selectedRoads->street[u]->stadtEnd)
        //         {
        //             //printf("%s", "FALSEEEE");

        //             if (s->gebietId < (sl2->stadt[v]->gebietId))
        //             {
        //                 if (s->gebietId > 0)
        //                 {
        //                     livePop = s->gebietId;

        //                     s->gebietId = s->gebietId - sl2->stadt[v]->gebietId;
        //                     sl2->stadt[v]->gebietId = sl2->stadt[v]->gebietId + livePop;
        //                     //printf("%s %d\n", "no, bigger", sl2->stadt[v]->gebietId);

        //                     WriteAfterMathData(sl2, s, sl2->stadt[v], "stadtneu.dat");
        //                 }
        //             }
        //             // else
        //             // {
        //             //     // livePop = s->gebietId;

        //             //     // s->gebietId = s->gebietId - sl2->stadt[v]->gebietId;
        //             //     // sl2->stadt[v]->gebietId = sl2->stadt[v]->gebietId + livePop;
        //             //     // printf("%s %d\n", "nope, bigger", sl2->stadt[v]->gebietId);

        //             //     // WriteAfterMathData(sl2, s, sl2->stadt[v], "stadtneu.dat");
        //             // }
        //             //printf("%s %s %d \n\n", sl2->stadt[v]->name, "population:", sl2->stadt[v]->gebietId);
        //         }
        //     }
        // }
        // if (selectedRoads->street[u]->stadtEnd == s->stadtId)
        // {
        //     for (int v = 0; v < sl2->count; v++)
        //     {

        //         if (sl2->stadt[v]->stadtId == selectedRoads->street[u]->stadtStart)
        //         {

        //             if (s->gebietId < sl2->stadt[v]->gebietId)
        //             {
        //                 if (s->gebietId > 0)
        //                 {

        //                     livePop = s->gebietId;

        //                     s->gebietId = s->gebietId - sl2->stadt[v]->gebietId;

        //                     sl2->stadt[v]->gebietId = sl2->stadt[v]->gebietId + livePop;
        //                     //printf("%s %d\n", "nope, bigger2", sl2->stadt[v]->gebietId);

        //                     WriteAfterMathData(sl2, s, sl2->stadt[v], "stadtneu.dat");
        //                 }

        // else
        // {
        //     livePop = s->gebietId;

        //     s->gebietId = s->gebietId - sl2->stadt[v]->gebietId;

        //     sl2->stadt[v]->gebietId = sl2->stadt[v]->gebietId + livePop;
        //     printf("%s %d\n", "nope, bigger2", sl2->stadt[v]->gebietId);

        //     WriteAfterMathData(sl2, s, sl2->stadt[v], "stadtneu.dat");

        //printf("%s %s %d %d \n\n", sl2->stadt[v]->name, "population:", sl2->stadt[v]->gebietId, popOtherCity);

        printf("%s %d %s %d \n", "City:", selectedRoads->street[u]->stadtStart, "Distance: ", selectedRoads->street[u]->distance);
    }
}

void WriteAfterMathData(StadtList *sl3, Stadt *s, Stadt *s2, char *fileName)
{
    FILE *file = fopen("stadtneu.dat", "w");
    fprintf(file, "ID | Stadt | Population \n");
    for (int i = 1; i < sl3->count; i++)
    {
        if (sl3->stadt[i]->stadtId != s->stadtId || sl3->stadt[i]->gebietId != 0)
        {
            fprintf(file, "%d %s %d \n", sl3->stadt[i]->stadtId, sl3->stadt[i]->name, sl3->stadt[i]->gebietId);
        }
    }

    fclose(file);
}

void printStadt(Stadt *s)
{
    printf("%d %101s %d %d %d \n", s->stadtId, s->name, s->einwohner, s->gebietId, s->meeresHoehe);
}

void printStadtWithId(StadtList *sl, char *name)
{
    Stadt *s = findStadt(sl, name);
    printStadt(s);
}

void GetPopulationSize(StadtList *sl, char *name)
{
    Stadt *s = findStadt(sl, name);
    printf("%100s, %d", "The population size is :", s->gebietId);
}

void stringSubst(char *s, char old, char new)
{
    while (*s)
    {
        if (*s == old)
            *s = new;
        s++;
    }
}