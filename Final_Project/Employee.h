#pragma once

#ifndef EMPLOYEE
#define EMPLOYEE
#include "GeneralFunctions.h"
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

void initEmployee(Employee* employee);

void printEmployee(const Employee* employee);

int getSalary();

void printPositions();

int getEmployeeID();

ePosition getPosition();
#endif // !EMPLOYEE
