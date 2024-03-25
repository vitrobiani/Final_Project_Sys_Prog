#pragma once

#ifndef STORE
#define STORE
#include "Employee.h"
#include "Department.h"
#include "list.h"


typedef struct Store {
	int storeID;
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

void addEmployee(Store* store, Employee* employee);

void removeEmployee(Store* store, int employeeID);

Employee* getEmployee(Store* store, int employeeID);

void addDepartment(Store* store, Department* department);

void removeDepartment(Store* store);

Department* getDepartment(Store* store);


#endif // !1