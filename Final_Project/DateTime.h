#pragma once

#ifndef DATE_TIME
#define DATE_TIME
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	unsigned hour;
	unsigned min;
	unsigned sec;
}Time;

typedef struct
{
	unsigned day;
	unsigned month;
	unsigned year;
	Time theTime;
} Date;

int initCurrentDateTime(Date* date);

void printDateTime(const Date* date);

#endif // !1