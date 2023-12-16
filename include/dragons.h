// File: dragons.h 
// Author(s): Henrik Eriksson, Johan Sollenius
// Description: 
// This file contains the public interface for the dragons module. 
// A dragon is simply a struct distincted with an identifier number and the struct
// contains information regarding the name and different types of attributes of the dragon. [dragons.c]
// The file holds functions on how the dragons is added,deleted,updated and found in the database (see database.h).

#ifndef DRAGONS_H
#define DRAGONS_H
#define MAX_COLOURS 5
#define MAX_DRAGONNAME 20
#define MAX_COLOURNAME 10

typedef struct Database Database;

typedef struct Dragon {
    unsigned int id; //A unique identifier
    char* name;
    char isVolant;
    unsigned int fierceness;
    unsigned int numColours;
    char* colours[MAX_COLOURS];
} Dragon;


//This function takes a pointer to a database and a pointer to a string as its input parameter,
// Returns the dragons index position in the database based on the search query for the id number or the name of the dragon, 
// If multiple dragons are found when searching for the name
// print a list of those dragons that match the search, And prompt the user to specify the id of the specific dragon.
// If no dragon is found, return -1 
// Parameters 
// dbPtr: A pointer to the database, query: A pointer to the search query for which is used to find the specific dragon. 
// Returns 
// If found, The index position of the dragon in the database, Else, -1
int findDragon(Database* dbPtr, char* query);

//This function takes a pointer to a database and a integer as its input parameter
// Updates a dragons based on the second parameter wich is the index position of the dragon struct in the database
// Prompts user to enter attributes such as fierceness,volant and colors
// Validates input and updates attributes accordingly
// Parameters 
// dbPtr: A pointer to the database, index: The index position of the dragon struct in the database dragons array. 
void updateDragon(Database* dbPtr, unsigned int index);

// This function takes a pointer to a database as its only input parameter
// Adds a dragon to the database and prompting the user for attributes
// If the capacity is full, Increases the capacity
void addDragon(Database* dbPtr);

// This function takes a pointer to a database and a integer as its input parameter
// Deletes a dragons based on the second parameter wich is the index position of the dragon struct in the database
// The function deletes a dragon by ”filling” the ”hole” created, by shifting all dragon records
// succeeding the deleted dragon record one step ”left”, to cover the ”hole”.
void deleteDragon(Database* dbPtr, unsigned int index);
#endif // !DRAGONS_H