#pragma once

#ifndef STOREMANAGER
#define STOREMANAGER
#include "Store.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { eNone, eID, eProfit, eRent, eLocation, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = { "NotSorted", "ID", "Profit", "Rent", "Location" };

typedef struct StoreManager {
	Store** stores;
	int noOfStores;
	DepartmentType* departments;
	int noOfDepartmentTypes;
	eSortOption storeSortOpt;
} StoreManager;

void initStoreManager(StoreManager* storeManager);

int generateStoreID(const StoreManager* storeManager);

void addStore(StoreManager* storeManager);

void removeStore(StoreManager* storeManager, int storeID);

Store* getStore(StoreManager* storeManager, int storeID);

void addDepartmentType(StoreManager* storeManager);

int generateDepartmentTypeID(const StoreManager* storeManager);

DepartmentType* getDepartmentTypeByID(StoreManager* storeManager);

DepartmentType* getDepartmentType(StoreManager* storeManager, int departmentTypeID);

void addProductToDepartmentType(StoreManager* storeManager);

void updateAllStoreDepartments(StoreManager* storeManager, DepartmentType* type);

Store* enterStore(StoreManager* storeManager);

void calculateTotalProfit(const StoreManager* storeManager);

void sortAllStoresBy(StoreManager* storeManager);

eSortOption showSortMenu();

void findStore(const StoreManager* storeManager);

void printAllStores(const StoreManager* storeManager);

void printAllDepartmentTypes(const StoreManager* storeManager);

void printAllDepartmentTypesFull(const StoreManager* storeManager);

void freeStoreManager(StoreManager* storeManager);

void saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName);

void loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName);

void fixLoadedStoreManager(StoreManager* storeManager);

#endif // !1