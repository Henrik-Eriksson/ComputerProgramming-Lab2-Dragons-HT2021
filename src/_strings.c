#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "_strings.h"

//If the strings start with matching letters, regardless upper- or lowercase
int equalStrings(char* str1, char* str2)
{
    while (*str1 != NULL && *str2 != NULL)
    {
        if (*str1 != *str2)
        {
            if (((*str1 >= 97 && *str1 <= 122) && (*str2 >= 65 && *str2 <= 90))) //If the first is lowercase and the second uppercase
            {
                //Make the second lowercase
                if ((*str2 + 32) != *str1) //If they're not equal now then they're not the same
                {
                    return 0;
                }
            }
            else if (((*str2 >= 97 && *str2 <= 122) && (*str1 >= 65 && *str1 <= 90))) //Same but reverse
            {

                if ((*str1 + 32) != *str2)
                {
                    return 0;
                }
            }
            else //They're either both upper case or lower case, Hence clearly not equal
            {
                return 0;
            }
        }

        str2++;
        str1++;
    }
    //removed
    //if (*str1 != *str2) return 0; //Incase they don't both end with the null terminator, THen they're not the same length and hence not equal
    return 1;

}

int isAlphabetic(char* str)
{
    
    while (*str != NULL)
    {

        if ((!((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122))) && *str != 10)
        {
            //printf("%d", *str);
            return 0;
        }


        str++;
    }
    return 1;
}

void toUpperCase(char* str)
{
    while (*str != NULL)
    {
        if (*str >= 97 && *str <= 122) //If lowercase
        {
            *str = *str - 32; //To uppercase
        }
        str++;
    }
}
