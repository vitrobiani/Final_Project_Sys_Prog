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

void addEmployee(Store* store, Employee* employee);

Employee* getEmployee(Store* store, int employeeID);

Employee* getEmployeeTUI(Store* store);

int checkIfThereAreProductsInStore(Store* store);

int countAvailableProductsInStore(Store* store);

int getNumOfProducts(int availableProducts);

int insertNewInvoiceToList(LIST* pList, Invoice* pInvoice);

Department* chooseDepartment(Store* store);

Product* chooseProduct(Department* department);

int chooseQuantity(Product* product);

Department* getDepartmentTUI(Store* store);

Department* getDepartment(Store* store, int id);

void addProductToDepartment(Store* store);

int generateInvoiceID(Store* store);

int compareStoreByID(const void* store1, const void* store2);

int compareStoreByRent(const void* store1, const void* store2);

int compareStoreByLocation(const void* store1, const void* store2);

void printAllInvoices(const Store* store);

void printAllEmployees(const Store* store);

void printAllDepartments(const Store* store);

void printAllProductsInStore(const Store* store);

void printStoreReduced(const Store* store);

void printStore(const Store* store);

void printStoreFull(const Store* store);

void freeStore(Store* store);

Employee* getBestSalesMan(const Store* store, int* saleAmount, int* bestProfit, int year, int month);

void findBestSalesMan(const Store* store);

Product* getBestSellerProduct(const Store* store, int* quantity, int year, int mouth);

void findBestSellerProduct(const Store* store);

int getYear();

int getMonth();

int saveStoreToTextFile(const Store* store, FILE* file);

int loadStoreFromTextFile(Store* store, FILE* file);

int saveStoreToBinaryFile(const Store* store, FILE* file);

int createEmployeeArr(Store* store);

int loadEmployeeArrFromBinaryFile(Store* store, FILE* file);

int loadDepartmentArrFromBinaryFile(Store* store, FILE* file);

int loadInvoiceListFromBinaryFile(Store* store, FILE* file);

int loadStoreFromBinaryFile(Store* store, FILE* file);

#endif // !1