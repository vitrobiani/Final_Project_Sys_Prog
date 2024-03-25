#include "DateTime.h"

int initDateTime(Date* dateTime, int day, int month, int year, int hour, int minute) {
	if (dateTime == NULL) {
		return 0;
	}
	dateTime->day = day;
	dateTime->month = month;
	dateTime->year = year;
	dateTime->theTime.hour = hour;
	dateTime->theTime.min = minute;
	return 1;
}

void printDateTime(const Date* dateTime) {
	if (dateTime == NULL) {
		printf("Date is NULL\n");
		return;
	}
	printf("%d/%d/%d %d:%d\n", dateTime->day, dateTime->month, dateTime->year, dateTime->theTime.hour, dateTime->theTime.min);
}