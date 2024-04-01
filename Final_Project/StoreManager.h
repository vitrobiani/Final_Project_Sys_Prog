#pragma once

#ifndef STOREMANAGER
#define STOREMANAGER
#include "Store.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { eNone, eID, eProfit, eRent, eLocation, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = { "NotSorted", "ID", "Profit", "Rent", "Location" };

typedef enum { eLoadFromTextFile, eLoadFromBinaryFile, eLoadNewSystem, eNoOfLoadOptions} eLoadOptions;
static const char* loadOptionsStr[eNoOfLoadOptions] = { "Load From Text File", "Load From Binary File", "Load New System" };

typedef struct StoreManager {
	Store** stores;
	int noOfStores;
	eSortOption storeSortOpt;
} StoreManager;

void initStoreManager(StoreManager* storeManager);

void loadSystem(StoreManager* storeManager);

void generateHQ(StoreManager* storeManager);

int generateStoreID(const StoreManager* storeManager);

void addStore(StoreManager* storeManager);

Store* getStore(StoreManager* storeManager, int storeID);

void addProductToDepartmentType(StoreManager* storeManager);

void addProductToMainStore(StoreManager* storeManager, int departmentID ,Product* product);

void updateAllStoreDepartments(StoreManager* storeManager);

int checkIfProductCodeExists(const StoreManager* storeManager, const char* productCode);

Store* enterStore(StoreManager* storeManager);

void calculateTotalProfit(const StoreManager* storeManager);

void sortAllStoresBy(StoreManager* storeManager);

eSortOption showSortMenu();

void findStore(const StoreManager* storeManager);

void printAllStores(const StoreManager* storeManager);

void freeStoreManager(StoreManager* storeManager);

void saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName);

void loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName);

#endif // !1