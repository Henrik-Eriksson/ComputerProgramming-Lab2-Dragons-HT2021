
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "_strings.h"
#include "dragons.h"
#include "database.h"
#include "userinterface.h"

static void swap(Dragon* dragons, int a, int b); //Swap place with two dragon structs
static void editColors(Database* dbPtr, unsigned int index);

void updateDragon(Database* dbPtr, unsigned int index)
{

        dbPtr->dragons[index].isVolant = getVolant();

        dbPtr->dragons[index].fierceness = getFierceness();

        editColors(dbPtr, index);

        puts("Dragon updated.");
 
}

void addDragon(Database* dbPtr)
{

    if (dbPtr->size == dbPtr->capacity)
    {
        if (!increaseCapacity(dbPtr))
        {
            puts("Couldn't allocate memory in order to increase capacity for one more dragon");
            return;
        }
    }

    dbPtr->dragons[dbPtr->size].name = getName();

    dbPtr->dragons[dbPtr->size].id = dbPtr->nextId;

    dbPtr->dragons[dbPtr->size].isVolant = getVolant();

    dbPtr->dragons[dbPtr->size].fierceness = getFierceness();

    dbPtr->dragons[dbPtr->size].numColours = 0;
    editColors(dbPtr, dbPtr->size);

    dbPtr->size++;
    dbPtr->nextId++;

    puts("Dragon added.");
}

void swap(Dragon* dragons, int a, int b)
{
    Dragon temp;
    temp = dragons[a];
    dragons[a] = dragons[b];
    dragons[b] = temp;
}

void deleteDragon(Database* dbPtr, unsigned int index)
{

    for (int i = index; i < dbPtr->size-1; i++)
    {
        swap(dbPtr->dragons, i, i + 1);
    }
    dbPtr->size--;

    puts("Dragon deleted");

}

//Returns the index of the dragon in the array if found, Else if multiple is found tell the user to specify the dragon after the search result is shown
int findDragon(Database* dbPtr, char* query)
{
    int found = 0;
    int i;
    int index;
    for (i = 0; i < dbPtr->size; i++)
    {
        if (dbPtr->dragons[i].id == strtol(query, NULL, 10) || equalStrings(dbPtr->dragons[i].name, query))
        {
            found++;
            index = i;
        }

    }

    if (found > 1)
    {
        int input;
        specificOverview(dbPtr, query);
        while (1)
        {
            puts("Please, Specify which dragon you were looking for");
            printf("Enter ID of dragon: ");
            if (scanf("%d", &input) == 0) fseek(stdin, 0, SEEK_SET); //clear buffer
               
            for (i = 0; i < dbPtr->size; i++)
            {
                if (dbPtr->dragons[i].id == input)
                {
                    return i;
                }

            }
            puts("Invalid id try again");
        }
    }
    else if (found == 1)
    {
        return index;
    }

    return -1;
}

void editColors(Database* dbPtr, unsigned int index)
{
    //Deallocate any prior colours
    for (int i = 0; i < dbPtr->dragons[index].numColours; i++)
    {
        free(dbPtr->dragons[index].colours[i]);
    }
    dbPtr->dragons[index].numColours = 0;


    fseek(stdin, 0, SEEK_SET);//clear buffer
    char colorInput[MAX_COLOURNAME];
    for(int j = 0; j < MAX_COLOURS; j++)
    {
        printf("\nColour %d (of %d) : ", j + 1, MAX_COLOURS);
        fgets(colorInput, MAX_COLOURNAME, stdin);
        if (*(colorInput) == '\n') break;

        dbPtr->dragons[index].colours[j] = (char*)malloc(MAX_COLOURNAME * sizeof(char));
        if (dbPtr->dragons[index].colours[j] == NULL)
        {
            puts("Couldn't allocate memory for one more color");
            break;
        }
        strcpy(dbPtr->dragons[index].colours[j], colorInput);

        if (!isAlphabetic(dbPtr->dragons[index].colours[j]))
        {
            puts("Invalid name of colour, Try again");
            continue;
        }

        toUpperCase(dbPtr->dragons[index].colours[j]);
        dbPtr->dragons[index].numColours = j + 1;
    }
}

