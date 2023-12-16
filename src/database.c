#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dragons.h"
#include "database.h"
#include "userinterface.h"

//static int increaseCapacity(Database* dbPtr);

Database* createDatabase(void)
{

    Database* dbPtr = (Database*)malloc(sizeof(Database));

    if (dbPtr == NULL)
    {
        puts("Couldn't allocate memory for the database");
        exit(0);
    }

    dbPtr->dragons = (Dragon*)malloc(sizeof(Dragon[INITIAL_CAPACITY]));

    if (dbPtr->dragons == NULL)
    {
        puts("Couldn't allocate memory for the database");
        exit(0);
    }

    dbPtr->size = 0;
    dbPtr->nextId = 1;
    dbPtr->capacity = INITIAL_CAPACITY;
    return(dbPtr);
}

void loadDatabase(char* filename, Database* dbPtr)
{
    FILE* fPtr = fopen(filename, "r");
    if (fPtr != NULL)
    {
        unsigned int numDragons;
        fscanf(fPtr, "%d", &numDragons);


        for (int i = 0; i < numDragons; i++)
        {

            if (dbPtr->size == dbPtr->capacity)
            {
                if (!increaseCapacity(dbPtr))
                {
                    puts("Couldn't allocate memory in order to increase capacity for one more dragon");
                    return;
                }
            }

            fscanf(fPtr, "%u", &(dbPtr->dragons[i].id));
            dbPtr->dragons[i].name = (char*)malloc(MAX_DRAGONNAME * sizeof(char));
            if (dbPtr->dragons[i].name == NULL) exit(137);
            fscanf(fPtr, "%s", dbPtr->dragons[i].name);
            fseek(fPtr, 2, SEEK_CUR); 
            fscanf(fPtr, "%c", &(dbPtr->dragons[i].isVolant));
            fscanf(fPtr, "%u", &(dbPtr->dragons[i].fierceness));
            fscanf(fPtr, "%u", &(dbPtr->dragons[i].numColours));

            for (int j = 0; j < dbPtr->dragons[i].numColours; j++)
            {
                dbPtr->dragons[i].colours[j] = (char*)malloc(MAX_COLOURNAME * sizeof(char));
                if (dbPtr->dragons[i].colours[j] == NULL) exit(137);
                fscanf(fPtr, "%s", dbPtr->dragons[i].colours[j]);
                fseek(fPtr, 2, SEEK_CUR);
            }

            dbPtr->size++;

        }
        fscanf(fPtr, "%u", &(dbPtr->nextId));
        puts("Database loaded");
    }
    else //If the file didn't exist, Try to create a new one instead
    {
        fPtr = fopen(filename, "w");
        puts("A new database file was created");
        if (fPtr == NULL)
        {
            puts("Couldn't create the new database file");
            exit(0);
        }
    }

    fclose(fPtr);
}

void saveDatabase(char* filename, Database* dbPtr)
{
    sortDatabase(dbPtr, 1); //Sort back to ASCENDING order by ID
    FILE* fPtr = fopen(filename, "w");
    if (fPtr != NULL)
    {
        fprintf(fPtr, "%u\n", dbPtr->size);
        for (int i = 0; i < dbPtr->size; i++)
        {
            fprintf(fPtr, "%u\n", dbPtr->dragons[i].id);
            fprintf(fPtr, "%s\n", dbPtr->dragons[i].name);
            fprintf(fPtr, "%c\n", dbPtr->dragons[i].isVolant);
            fprintf(fPtr, "%u\n", dbPtr->dragons[i].fierceness);
            fprintf(fPtr, "%u\n", dbPtr->dragons[i].numColours);
            for (int j = 0; j < dbPtr->dragons[i].numColours; j++)
            {
                fprintf(fPtr, "%s\n", dbPtr->dragons[i].colours[j]);
            }
        }
        fprintf(fPtr, "%u", dbPtr->nextId);
    }

}

void destroyDatabase(Database* dbPtr)
{
    for (int i = 0; i < dbPtr->size; i++)
    {
        free(dbPtr->dragons[i].name);
        for (int j = 0; j < dbPtr->dragons[i].numColours; j++)
        {
            free(dbPtr->dragons[i].colours[j]);
        }
    }
    free(dbPtr->dragons);
    free(dbPtr);
}

void sortDatabase(Database* dbPtr, int choice)
{
    int i;
    int j;
    for (i = 0; i < dbPtr->size; ++i)
    {

        for (j = i + 1; j < dbPtr->size; ++j)
        {
            int condition = 0;

            if (choice == 0)
            {

                //If the first letter is the same check the second and third and so on
                for (int k = 0; k < strlen(dbPtr->dragons[j].name) && k < strlen(dbPtr->dragons[i].name); k++)
                {
                    if (dbPtr->dragons[i].name[k] != dbPtr->dragons[j].name[k])
                    {
                        condition = (dbPtr->dragons[i].name[k] > dbPtr->dragons[j].name[k]);
                        break;
                    }
                }


            }
            else if ((choice == 1))
            {
                condition = (dbPtr->dragons[i].id > dbPtr->dragons[j].id);
            }

            if (condition) //If condition make a switch
            {

                Dragon a = dbPtr->dragons[i];
                dbPtr->dragons[i] = dbPtr->dragons[j];
                dbPtr->dragons[j] = a;

            }

        }

    }
    puts("Database sorted");
}

int increaseCapacity(Database* dbPtr)
{

    Dragon* memPtr = (Dragon*)realloc(dbPtr->dragons, (sizeof(dbPtr->dragons[0]) * dbPtr->capacity)*GROWTH_FACTOR);
    if (memPtr == NULL) return 0;
    dbPtr->dragons = memPtr;
    dbPtr->capacity *= GROWTH_FACTOR;
    printf("Increased the database capacity to %d\n", dbPtr->capacity);
    return 1;


}





