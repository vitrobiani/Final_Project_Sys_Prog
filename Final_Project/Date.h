#ifndef __MYDATE__
#define __MYDATE__
#include "GeneralFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MIN_YEAR 2023

typedef struct
{
	int	day;
	int	month;
	int	year;
}Date;

void getCorrectDate(Date* pDate);

int	checkDate(char* date, Date* pDate);

void printDate(const Date* pDate);

#endif
