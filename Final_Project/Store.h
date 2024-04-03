#pragma once

#ifndef STORE
#define STORE
#include "Employee.h"
#include "Invoice.h"
#include "Department.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "Macros.h"

typedef struct Store {
	int storeID;
	char* location;
	int rent;
	int profit;
	Employee* employees;
	int noOfEmployees;
	Department departments[noOfDepartmentTypes];
	int noOfDepartments;
	LIST invoiceList;
	int noOfInvoices;
} Store;

int createStore(Store* store, int id);

int initStore(Store* store, int id);

void initDepartmentArray(Store* store);

void addEmployee(Store* store);

Employee* getEmployee(Store* store, int employeeID);

Employee* getEmployeeTUI(Store* store);

int checkIfThereAreProductsInStore(Store* store);

int countAvailableProductsInStore(Store* store);

void makeSale(Store* store);

Department* getDepartmentTUI(Store* store);

Department* getDepartment(Store* store, int id);

void addProductToDepartment(Store* store);

int generateInvoiceID(Store* store);

int calculateStoreProfit(Store* store);

int calculateStoreSpendings(Store* store);

int compareStoreByID(const void* store1, const void* store2);

int compareStoreByProfit(const void* store1, const void* store2);

int compareStoreByRent(const void* store1, const void* store2);

int compareStoreByLocation(const void* store1, const void* store2);

void printStoreProfit(const Store* store);

void printStoreSpendings(const Store* store);

void printAllInvoices(const Store* store);

void printAllEmployees(const Store* store);

void printAllDepartments(const Store* store);

void printAllProductsInStore(const Store* store);

void printStoreReduced(const Store* store);

void printStore(const Store* store);

void freeStore(Store* store);

void saveStoreToTextFile(const Store* store, FILE* file);

void loadStoreFromTextFile(Store* store, FILE* file);

int saveStoreToBinaryFile(const Store* store, FILE* file);

int createEmployeeArr(Store* store);

int loadStoreFromBinaryFile(Store* store, FILE* file);

#endif // !1