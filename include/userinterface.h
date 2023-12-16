// File: userinterface.h 
// Author(s): Henrik Eriksson, Johan Sollenius
// Description: 
// This file contains the public interface for the userinterface module. 
// Holds functions regarding displaying information and retrieving&validating input for user [userinterface.c]

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

//************* DISPLAYING INFORMATION************

// This function has only a database pointer as its only input parameter
// Displays a breifed overview of IDs & Names of all the dragons currently in the database
void briefOverview(Database* dbPtr);

// This function has only a database pointer as its only input parameter
// Displays detailed information on all dragons in the database
// Besides just ID&Name this includes showing attributes such as Volant,Fierceness,#Colours and Colors
void detailedOverview(Database* dbPtr);

// This function has as its first parameter a database pointer and as second parameter a pointer to a string (the search query)
// Displays detailed information for one specific dragon (or more dragons if search result on name is similiar to others)
void specificOverview(Database* dbPtr, char* query);

// This function has only a database pointer as its only input parameter
// Displays statistics/information of the database, Such as size, (Min/Max)Fierceness, #Volant, #NonVolant
void databaseOverview(Database* dbPtr);

//*************************************************

//*************RETRIEVING&VALIDATING INPUT*********

// This function has only one parameter, a pointer to a string(filename)
// asks the user to input a name for the filename
// It will validate the filename,
// Asks the user to re-enter if invalid
void getDatabaseFilename(char* filename); 

// This function has only one parameter, a pointer to a string(query)
// asks the user to input a search query,
// It will validate the query,
// Asks the user to re-enter if invalid
void getQuery(char* query); 

// This function has no parameters
// The function allocates a string on the heap for the name
// and asks the user to input a name for a dragon
// It will validate the name, make sure only non-numeric letters is present, If not,
// Asks the user to re-enter the name
// The function returns the pointer to the string where the name is stored
char* getName(void);

// This function has no parameters
// asks user to input volant attribute
// The function validates the volant, and makes it uppercase if lowercase, If not valid,
// Asks the user to re-enter the volant
// The funcion returns a char (volant)
char getVolant(void);

// This function has no parameters
// asks user to input fierceness attribute
// The function validates the fierceness attribute, If not valid,
// Asks the user to re-enter the fiercness
// The function returns the fierceness as a int
int getFierceness(void);

// This function has no parameters
// asks user to input either 0 or 1
// The function validates the input, If not valid,
// Asks the user to re-enter the sort choice
// The function returns the choosed number as a int
int getSort(void);

//**************************************************
#endif