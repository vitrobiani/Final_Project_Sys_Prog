#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '#'

void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter Purchase Date dd%c%cmm%c%cyyyy  (Year must be between %d - %d)\t",
			SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, MIN_YEAR, MAX_YEAR);
		myGets(date, MAX_STR_LEN);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 12)
		return 0;
	if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
		|| (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
		return 0;
	sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR || year > MAX_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d", pDate->day, pDate->month, pDate->year);
}

int saveDateToBinaryFileCompressed(const Date* pDate, FILE* file)
{
	BYTE data[3];
	data[0] = pDate->year  >> 7;
	data[1] = (pDate->year << 1) | (pDate->month >> 3);
	data[2] = (pDate->month << 5) | pDate->day;
	if (fwrite(data, sizeof(BYTE), 3, file) != 3) {
		puts("Error writing date to file");
		return 0;
	}
	return 1;
}

int loadDateFromBinaryFileCompressed(Date* pDate, FILE* file)
{
	BYTE data[3];
	if (fread(data, sizeof(BYTE), 3, file) != 3) {
		puts("Error reading date from file");
		return 0;
	}
	pDate->year = ((data[0] & 0x7F) << 7) | (data[1] >> 1);
	pDate->month = ((data[1] & 0x1) << 3) | (data[2] >> 5);
	pDate->day = data[2] & 0x1F;
	return 1;
}




