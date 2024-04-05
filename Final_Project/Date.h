#ifndef __MYDATE__
#define __MYDATE__
#include "GeneralFunctions.h"
#include "FileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_YEAR 2024
#define MAX_YEAR 9999

typedef unsigned char BYTE;

typedef struct
{
	int	day;  // 1-31
	int	month;// 1-12
	int	year; // 2024-9999
}Date;

void getCorrectDate(Date* pDate);

int	checkDate(char* date, Date* pDate);

void printDate(const Date* pDate);

int saveDateToBinaryFileCompressed(const Date* pDate, FILE* file);

int loadDateFromBinaryFileCompressed(Date* pDate, FILE* file);

#endif
