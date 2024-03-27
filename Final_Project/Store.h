#pragma once

#ifndef STORE
#define STORE
#include "Employee.h"
#include "Invoice.h"
#include "DepartmentType.h"
#include "Department.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Store {
	int storeID;
	char* location;
	Employee* employees;
	int noOfEmployees;
	Department* departments;
	int noOfDepartments;
	LIST invoiceList;
	int rent;
} Store;

int createStore(Store* store);

int initStore(Store* store);

int createStoreID();

void addEmployee(Store* store);

void removeEmployee(Store* store, int employeeID);

Employee* getEmployee(Store* store, int employeeID);

void addDepartment(Store* store, DepartmentType* type);

void removeDepartment(Store* store);

Department* getDepartment(Store* store);

void printAllDepartments(const Store* store);

void printStoreReduced(const Store* store);

void printStore(const Store* store);

#endif // !1