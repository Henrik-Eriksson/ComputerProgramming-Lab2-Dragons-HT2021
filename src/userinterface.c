#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "_strings.h"
#include "dragons.h"
#include "database.h"
#include "userinterface.h"

//Display infromation about a specific dragon
static void displayDragon(Database* dbPtr, unsigned int index);
static void displayHeader();

void briefOverview(Database* dbPtr)
{
    puts("--------------------------------------------------------------------------------");
    puts("ID Name");
    puts("--------------------------------------------------------------------------------");

    for (int i = 0; i < dbPtr->size; i++)
    {
        printf("%-1d %s\n", dbPtr->dragons[i].id, dbPtr->dragons[i].name);
    }

}

void detailedOverview(Database* dbPtr)
{
    displayHeader();

    for (int i = 0; i < dbPtr->size; i++)
    {
        displayDragon(dbPtr, i);
    }

}

void specificOverview(Database* dbPtr, char* query)
{
    displayHeader();

    for (int i = 0; i < dbPtr->size; i++)
    {
        if (dbPtr->dragons[i].id == strtol(query, NULL, 10) || equalStrings(dbPtr->dragons[i].name, query))
        {
            displayDragon(dbPtr, i);

        }

    }

}

void databaseOverview(Database* dbPtr)
{
    puts("---------------------------------------------------");
    puts("Size MinFierceness MaxFierceness #Volant #NonVolant");
    puts("---------------------------------------------------");

    unsigned int minFierceness = 100;
    unsigned int maxFierceness = 0;
    unsigned int volant = 0;
    unsigned int nonVolant = 0;

    for (int i = 0; i < dbPtr->size; i++)
    {
        if (minFierceness > dbPtr->dragons[i].fierceness)
        {
            minFierceness = dbPtr->dragons[i].fierceness;
        }

        if (maxFierceness < dbPtr->dragons[i].fierceness)
        {
            maxFierceness = dbPtr->dragons[i].fierceness;
        }

        if (dbPtr->dragons[i].isVolant == 'Y')
        {
            volant++;
        }
        else
        {
            nonVolant++;
        }

    }

    printf("%d\t %d\t\t %d\t  %d \t    %d", dbPtr->size, minFierceness, maxFierceness, volant, nonVolant);

}

void displayHeader()
{
    puts("--------------------------------------------------------------------------------");
    puts("ID Name\t    Volant Fierceness #Colours Colors");
    puts("--------------------------------------------------------------------------------");
}

void displayDragon(Database* dbPtr, unsigned int index)
{
    printf("%-2d %-10s \t %-2c %-13u %-5u", dbPtr->dragons[index].id, dbPtr->dragons[index].name, dbPtr->dragons[index].isVolant, dbPtr->dragons[index].fierceness, dbPtr->dragons[index].numColours);
    for (int j = 0; j < dbPtr->dragons[index].numColours; j++)
    {
        printf("%-1s ", dbPtr->dragons[index].colours[j]);
    }
    printf("\n");
}

void getDatabaseFilename(char* filename)
{
 
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("Database file name (max %d characters): ", MAX_FILENAME);
        scanf("%s", filename);
        if (strlen(filename) <= MAX_FILENAME)
        {
            for (int i = 0; i < strlen(filename); i++)
            {
                if (filename[i] == '.')
                {
                    if ((i + 3) < strlen(filename))
                    {
                        if (filename[i + 1] == 't' && filename[i + 2] == 'x' && filename[i + 3] == 't') return;
                    }
                 
                }
                
            }
            puts("Invalid format, Make sure to end the filename with \".txt\"");
        }
        else
        {
            puts("Filename too long, Try again.");
        }   
        
    }
  

}

void getQuery(char* query)
{
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("Enter id or name of dragon: ");
        scanf("%s", query);
        if (strlen(query) <= MAX_DRAGONNAME)
        {
            return;
        }
        printf("Too long search query, Max: %d characters long\n", MAX_DRAGONNAME);
    }
}

char* getName()
{
    char* name = (char*)malloc(MAX_DRAGONNAME * sizeof(char));
    if (name == NULL) {
        puts("Couldn't allocate memory for the name");
        exit(-1);
    }
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("Enter the dragons name: ");
        scanf("%s", name);
        if (isAlphabetic(name))
        {
            toUpperCase(name);
            return name;
        }
        puts("Invalid name, Try again");
    }
}

char getVolant()
{
    char volant;
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("\nEnter volant(Y,N) : ");
        volant = getchar();
        if (volant == 89 || volant == 121 || volant == 78 || volant == 110)
        {
            if (volant == 121 || volant == 110) volant -= 32; //To uppercase if lowercase
            return volant;
        }
        printf("\nInvalid volant, Try again");
    }
}

int getFierceness()
{
    int fierceness;
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("\nEnter fierceness(1 - 10) : ");
        scanf("%u", &fierceness);
        if (fierceness >= 1 && fierceness <= 10) return fierceness;
        puts("Invalid fierceness, Try again");   
    }
}

int getSort(void)
{
    int choice;
    while (1)
    {
        fseek(stdin, 0, SEEK_END);//clear buffer
        printf("Enter sort ASCENDING by name(0) or id(1) : ");
        scanf("%u", &choice);
        if (choice == 1 || choice == 0) return choice;
        puts("Invalid input, Try again");
    }
}
