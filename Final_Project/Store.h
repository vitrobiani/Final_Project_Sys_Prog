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
	int noOfInvoices;
	int rent;
} Store;

int createStore(Store* store, int id);

int initStore(Store* store, int id);

void addEmployee(Store* store);

Employee* getEmployee(Store* store, int employeeID);

Employee* getEmployeeTUI(Store* store);

void makeSale(Store* store);

Department* getDepartmentTUI(Store* store);

void addDepartment(Store* store, DepartmentType* type);

Department* getDepartment(Store* store, int id);

void addProductToDepartment(Store* store);

int generateInvoiceID(Store* store);

int calculateStoreProfit(Store* store);

int compareStoreByID(const void* store1, const void* store2);

int compareStoreByProfit(const void* store1, const void* store2);

int compareStoreByRent(const void* store1, const void* store2);

int compareStoreByLocation(const void* store1, const void* store2);

void printAllInvoices(const Store* store);

void printAllEmployees(const Store* store);

void printAllDepartments(const Store* store);

void printStoreReduced(const Store* store);

void printStore(const Store* store);

void freeStore(Store* store);

void saveStoreToTextFile(const Store* store, FILE* file);

void loadStoreFromTextFile(Store* store, FILE* file);

#endif // !1