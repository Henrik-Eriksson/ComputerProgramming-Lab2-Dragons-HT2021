// File: database.h 
// Author(s): Henrik Eriksson, Johan Sollenius
// Description: 
// This file contains the public interface for the database module. 
// A database stores structs of dragons (see dragons.h). [database.c]
// The file contains functions on creating,loading,saving and increasing the capacity for a database

#ifndef _DATABASE_H
#define _DATABASE_H
#define INITIAL_CAPACITY 10 //A database capacity starts with being able to hold 10 dragon structs 
#define GROWTH_FACTOR 2 //Everytime the capacity needs to be expanded it's multiplied by the growth factor
#define MAX_FILENAME 20

typedef struct Dragon Dragon;

typedef struct Database {
    Dragon* dragons; //A pointer to a collection(array) of dragon structs (see dragons.h)
    unsigned int capacity; //The capacity on how many structs of dragons the database can hold
    unsigned int size; //How many structs of dragons the database is holding
    unsigned int nextId; //The next available unique id number a dragon gets when added
} Database;

// This function has no input parameters
// Creates a empty database with INITIAL_CAPACITY and allocates it to the heap
// Returns a pointer to the newly created database
Database* createDatabase(void);

// This function takes a pointer to a string(filename) and a pointer to a database
// Loads a database from a txt file based on the filename from the first input parameter
// If the file doesn't exist already create a new one with the filename and don't load in any data
void loadDatabase(char* filename, Database* dbPtr);

// This function takes a pointer to a string(filename) and a pointer to a database
// Save the database by writing it to a txt file in the same directory
void saveDatabase(char* filename, Database* dbPtr);

// This function takes a pointer to a database
// Destroys the database and frees up memory
void destroyDatabase(Database* dbPtr);

// This function takes a pointer to a database as its first parameter and
// as it's second parameter an integer
// This function sorts the database in ASCENDING order based by
// id(1) or name(0)
void sortDatabase(Database* dbPtr, int choice);

// This function only takes a pointer to a database
// Reallocating and increases the capacity for the database by multiplying by the GROWTH_FACTOR
int increaseCapacity(Database* dbPtr);
#endif
