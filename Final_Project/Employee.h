#pragma once

#ifndef EMPLOYEE
#define EMPLOYEE
#include <stdio.h>

typedef enum { eWorker, eManager, eNumOfPositions } ePosition;
static const char* ePositionStr[eNumOfPositions] = { "Worker", "Manager" };


typedef struct Employee {
	int id;
	char* name;
	ePosition position;
	int salary;
} Employee;

void initEmployee(Employee* employee, int id, const char* name, ePosition position, int salary);

void printEmployee(const Employee* employee);

int getSalary(const Employee* employee);

void printPositions(const Employee* employee);

ePosition getPosition(const Employee* employee);
#endif // !EMPLOYEE
