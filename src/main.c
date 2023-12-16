#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dragons.h"
#include "database.h"
#include "userinterface.h"

void printWelcomeMessage(void);
void displayMainMenu(void);
int executeCommands(Database* dbPtr);

int main(void)
{

    char filename[MAX_FILENAME];
    Database* dbPtr = createDatabase();

    printWelcomeMessage();
    getDatabaseFilename(filename);
    loadDatabase(filename, dbPtr);
    displayMainMenu();

    executeCommands(dbPtr);
    saveDatabase(filename, dbPtr);
    destroyDatabase(dbPtr);


    return 0;
}

void printWelcomeMessage(void)
{
    puts("This program helps organize information about dragons. You may add and\nremove dragons and their attributes, list the dragons currently in the\ndatabase, and their attributes, look up the attributes of an individual\ndragon, get statistics from the database, or sort the database.\n");
}

void displayMainMenu(void)
{
    puts("------------------------------------------");
    puts("Menu");
    puts("------------------------------------------");
    puts("    0. Display menu.");
    puts("    1. Insert a dragon.");
    puts("    2. Update a dragon.");
    puts("    3. Delete a dragon.");
    puts("    4. List all dragons(brief).");
    puts("    5. List all dragons(detailed).");
    puts("    6. Show details for a specific dragon.");
    puts("    7. List database statistics.");
    puts("    8. Sort database.");
    puts("    - 1. Quit.");
    puts("------------------------------------------");
}

int executeCommands(Database* dbPtr)
{
    int userChoice;
    char query[MAX_DRAGONNAME]; //User search string 
    
    while (1)
    {
        printf("\n?: ");
        scanf("%d", &userChoice);
  
        switch (userChoice)
        {
        case 0:
            displayMainMenu();
            break;
        case 1:
            addDragon(dbPtr);
            break;
        case 2:
            getQuery(query);
            updateDragon(dbPtr, findDragon(dbPtr, query));
            break;
        case 3:
            getQuery(query);
            deleteDragon(dbPtr, findDragon(dbPtr, query));
            break;
        case 4:
            briefOverview(dbPtr);
            break;
        case 5:
            detailedOverview(dbPtr);
            break;
        case 6:
            getQuery(query);
            specificOverview(dbPtr, query);
            break;
        case 7:
            databaseOverview(dbPtr);
            break;
        case 8:
            sortDatabase(dbPtr, getSort());
            break;
        case -1:
            return 0;
            break;
        default:
            puts("Invalid selection. Please try again.");
            break;
        }
    }
    return 1;
}

