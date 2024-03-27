#pragma once

#ifndef STOREMANAGER
#define STOREMANAGER
#include "Store.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StoreManager {
	Store** stores;
	int noOfStores;
	DepartmentType* departments;
	int noOfDepartmentTypes;
} StoreManager;

void initStoreManager(StoreManager* storeManager);

void addStore(StoreManager* storeManager);

void removeStore(StoreManager* storeManager, int storeID);

Store* getStore(StoreManager* storeManager, int storeID);

void addDepartmentType(StoreManager* storeManager);

int generateDepartmentTypeID(const StoreManager* storeManager);

DepartmentType* getDepartmentTypeByID(StoreManager* storeManager);

DepartmentType* getDepartmentType(StoreManager* storeManager, int departmentTypeID);

void addProductToDepartment(StoreManager* storeManager);

void updateAllStoreDepartments(StoreManager* storeManager, DepartmentType* type);

Store* enterStore(StoreManager* storeManager);

void printAllStores(const StoreManager* storeManager);

void printAllDepartmentTypes(const StoreManager* storeManager);

void printAllDepartmentTypesFull(const StoreManager* storeManager);

#endif // !1