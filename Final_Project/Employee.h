#pragma once

#ifndef EMPLOYEE
#define EMPLOYEE
#include "GeneralFunctions.h"
#include "FileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { eWorker, eManager, eNumOfPositions } ePosition;
static const char* ePositionStr[eNumOfPositions] = { "Worker", "Manager" };


typedef struct Employee {
	int id;
	char* name;
	ePosition position;
	int salary;
} Employee;

void printEmployee(const Employee* employee);

int getSalary();

void printPositions();

ePosition getPosition();

void freeEmployee(Employee* employee);

int saveEmployeeToTextFile(const Employee* employee, FILE* file);

int loadEmployeeFromTextFile(Employee* employee, FILE* file);

int saveEmployeeToBinaryFile(const Employee* employee, FILE* file);

int loadEmployeeFromBinaryFile(Employee* employee, FILE* file);

#endif // !EMPLOYEE
