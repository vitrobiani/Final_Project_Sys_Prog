#pragma once
#ifndef GENERALFUNCTIONS
#define GENERALFUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));

#endif // !GENERALFUNCTIONS